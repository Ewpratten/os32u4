#if !defined(_OS_PROCESS_PROCD_HH)
#define _OS_PROCESS_PROCD_HH

// Max number of processes we can run
#define MAX_PROCESS_COUNT 10

#include <os32u4/process/process.hh>

namespace os {
namespace process {
namespace scheduler {

void runIteration();

int start(process::Process* proc);
void end(int pid);

void freeze(int pid);
void thaw(int pid);

process::Process* getProc(int pid);

}  // namespace scheduler
}  // namespace process
}  // namespace os

#endif  // _OS_PROCESS_PROCD_HH
