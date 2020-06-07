#include <os32u4/process/procd.hh>
#include <vendor/millis/millis.hh>

// Info for keeping track of process execution
struct ProcInfo {
    os::process::Process* proc;
    double lastCallTimeSecs;
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
        // If the process is allowed to run
        if (!processes[i].finished && !processes[i].frozen) {
            // If this is the first run, init the process
            if (processes[i].lastCallTimeSecs == 0.0) {
                processes[i].proc->init();
            }

            // Calculate time since last run
            double secsNow = millis_get() / 1000;
            double dt = processes[i].lastCallTimeSecs - secsNow;
            processes[i].lastCallTimeSecs = secsNow;

            // Run an iteration of the process
            processes[i].proc->runIteration(dt);

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

    // Set the process slot
    ProcInfo pi;
    pi.proc = proc;
    pi.finished = false;
    pi.frozen = false;
    pi.lastCallTimeSecs = 0.0;
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