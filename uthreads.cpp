#include "uthreads.h"
#include "Scheduler.h"

extern Scheduler * currSched;

using namespace std;


//Initializes the scheduler using the quantum usecs
int uthread_init(int quantum_usecs){
    return currSched->init(quantum_usecs);
}

int uthread_spawn(void (*f)(void), Priority pr){
    return currSched->spawnThread(f, pr);
    
}


int uthread_suspend(int tid){
    //TODO: validity check and stuff (not as simple as this)
    shared_ptr<Thread> thread = currSched->getThread(tid);
    if(thread == nullptr){
        return FAIL;
    }
    return currSched->suspendThread(thread);
}

int uthread_resume(int tid){
    shared_ptr<Thread> thread = currSched->getThread(tid);
    if(thread == nullptr){
        return FAIL;
    }
    return currSched->resumeThread(thread);
   
}

int uthread_terminate(int tid){
    //TODO: validity check and stuff
    shared_ptr<Thread> thread = currSched->getThread(tid);
    if(thread == nullptr){
        return FAIL;
    }
    return currSched->terminateThread(thread);
}

int uthread_get_tid(){
    return currSched->getRunningThreadID();
}

int uthread_get_total_quantums(){
    return currSched->getTotalQuantums();
}

int uthread_get_quantums(int tid){
    shared_ptr<Thread> thread = currSched->getThread(tid);
    if(thread == nullptr){
        return FAIL;
    }
    return thread->getTotalQuantums();
    
}