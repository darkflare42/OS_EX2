#include "uthreads.h"
#include "Scheduler.h"

Scheduler _sched;

using namespace std;


//Initializes the scheduler using the quantum usecs
int uthread_init(int quantum_usecs){
    return _sched.init(quantum_usecs);
}

int uthread_spawn(void (*f)(void), Priority pr){
    return _sched.spawnThread(f, pr);
    
}


int uthread_suspend(int tid){
    //TODO: validity check and stuff (not as simple as this)
    shared_ptr<Thread> thread = _sched.getThread(tid);
    if(thread == nullptr){
        return FAIL;
    }
    return _sched.suspendThread(thread);
}

int uthread_resume(int tid){
    shared_ptr<Thread> thread = _sched.getThread(tid);
    if(thread == nullptr){
        return FAIL;
    }
    return _sched.resumeThread(thread);
   
}

int uthread_terminate(int tid){
    //TODO: validity check and stuff
    shared_ptr<Thread> thread = _sched.getThread(tid);
    if(thread == nullptr){
        return FAIL;
    }
    return _sched.terminateThread(thread);
}

int uthread_get_tid(){
    return _sched.getRunningThreadID();
}

int uthread_get_total_quantums(){
    return _sched.getTotalQuantums();
}

int uthread_get_quantums(int tid){
    shared_ptr<Thread> thread = _sched.getThread(tid);
    if(thread == nullptr){
        return FAIL;
    }
    return thread->getTotalQuantums();
    
}