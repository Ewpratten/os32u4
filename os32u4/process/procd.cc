#include <os32u4/process/procd.hh>
#include <vendor/millis/millis.hh>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>

// Info for keeping track of process execution
typedef struct ProcInfo {
    os::process::Process* proc;
    unsigned long lastCallTime;
    bool frozen;
    bool finished;
};

// Array of all processes
ProcInfo processes[MAX_PROCESS_COUNT];
int EOP = 0;  // End of process list

namespace os {
namespace process {
namespace scheduler {

void runIteration() {
    // Loop through every process
    for (int i = 0; i < MAX_PROCESS_COUNT; i++) {
        // printf("%d\n", i);
        // If the process is allowed to run
        if (!processes[i].finished && !processes[i].frozen && i < EOP) {

            // If this is the first run, init the process
            if (!(bool)processes[i].proc->initialized) {
                processes[i].proc->initialized = true;
                processes[i].proc->init();
            }


            // Handle starting the timer service if the user forgets
            if(millis_get() == 0.0){
                millis_init();
            }
            // puts("Read millis");

            // Calculate time since last run
            millis_t now = millis_get() * 2; // Timing is a little odd
            unsigned long dt = now - processes[i].lastCallTime;
            processes[i].lastCallTime = now;
            // puts("Calculated DT");

            // Run an iteration of the process
            processes[i].proc->runIteration(dt);
            // puts("Ran iteration");

            // Check if the process has finished
            processes[i].finished = processes[i].proc->isFinished();

            // If finished, end the proc
            if (processes[i].finished) {
                processes[i].proc->end();
            }
        }
    }
}

int start(process::Process* proc) {
    // Find a suitable process "slot" to fill
    int slot = -1;
    if (EOP < MAX_PROCESS_COUNT) {
        slot = EOP;
        EOP++;
    } else {
        // Find if any processes are finished
        for (int i = 0; i < MAX_PROCESS_COUNT; i++) {
            if (processes[i].finished) {
                slot = i;
            }
        }
    }

    // If the slot is -1, we can't start this process
    if (slot == -1) {
        return -1;
    }

    // If this is the first process, we need to wipe the entire process array
    if(slot == 0){
        memset(processes, 0, sizeof(struct ProcInfo));
    }

    // Set the process slot
    ProcInfo pi;
    pi.proc = proc;
    pi.finished = false;
    pi.frozen = false;
    pi.lastCallTime = 0l;
    pi.proc->initialized = false;
    processes[slot] = pi;

    // Give the process a pid
    processes[slot].proc->pid = slot;

    // Return the process ID
    return slot;
}

void end(int pid) {
    // Set the finished flag on the process
    processes[pid].finished = true;
}

void freeze(int pid) {
    // Set the frozen flag on the process
    processes[pid].frozen = true;
}

void thaw(int pid) {
    // Unset the frozen flag on the process
    processes[pid].frozen = false;
}

process::Process* getProc(int pid) { return processes[pid].proc; }

}  // namespace scheduler
}  // namespace process
}  // namespace os