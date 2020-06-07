#if !defined(_OS_PROCESS_PROCESS_HH)
#define _OS_PROCESS_PROCESS_HH

namespace os {
namespace process {

class Process {
   public:
    virtual void init();
    virtual void runIteration(unsigned long dt);
    virtual bool isFinished() { return true; }
    virtual void end();
    int pid;
    bool initialized = false;
};

}  // namespace process
}  // namespace os

#endif  // _OS_PROCESS_PROCESS_HH
