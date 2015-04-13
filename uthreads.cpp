#include "uthreads.h"
#include "Scheduler.h"

extern Scheduler * currSched;

using namespace std;


//Initializes the scheduler using the quantum usecs
int uthread_init(int quantum_usecs){
    return currSched->init(quantum_usecs);
}

int uthread_spawn(void (*f)(void), Priority pr){
    currSched->blockSignals();
    
    int tID =  currSched->spawnThread(f, pr);
    
    currSched->unblockSignals();
    return tID;
    
}


int uthread_suspend(int tid){
    //TODO: validity check and stuff (not as simple as this)
    
    currSched->blockSignals();
    
    //Cannot suspend the main Thread
    if(tid == 0){
        cout << "thread library error: cannot suspend main thread" << endl;
        currSched->unblockSignals();
        return FAIL;
    }
    
    shared_ptr<Thread> thread = currSched->getThread(tid);
    if(thread == nullptr || thread->getState() == Suspended){
        currSched->unblockSignals();
        return FAIL;
    }
    
    currSched->unblockSignals();
    int tempVal = sigsetjmp(currSched->getRunningThread()->env, 1);
    if(tempVal == 1){
        return OK;
    }
    
    int errCode = currSched->suspendThread(thread);
    siglongjmp(currSched->getRunningThread()->env, 1);
    currSched->unblockSignals();
    return errCode;
}

int uthread_resume(int tid){
    
    currSched->blockSignals();
    shared_ptr<Thread> thread = currSched->getThread(tid);
    if(thread == nullptr){
        return FAIL;
    }
    int errCode =  currSched->resumeThread(thread);
    currSched->unblockSignals();
    return errCode;
   
}

int uthread_terminate(int tid){
    //TODO: validity check and stuff
    
    currSched->blockSignals();
    
    
    shared_ptr<Thread> thread = currSched->getThread(tid);
    if(thread == nullptr){
        currSched->unblockSignals();
        return FAIL;
    }
    
    //We are terminating the main thread
    if(tid == 0){
        delete currSched; //TODO: add proper destructor for scheduler
        exit(0);
    }
    
    int errCode =  currSched->terminateThread(thread);
    currSched->unblockSignals();
    return errCode;
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