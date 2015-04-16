#include "uthreads.h"
#include "Scheduler.h"
#include "ThreadUtils.h"

extern Scheduler * gCurrSched;

using namespace std;


//Initializes the scheduler using the quantum usecs
int uthread_init(int quantum_usecs)
{
    return gCurrSched->init(quantum_usecs);
}

int uthread_spawn(void (*f)(void), Priority pr)
{
    gCurrSched->blockSignals();
    
    int tID =  gCurrSched->spawnThread(f, pr);
    
    gCurrSched->unblockSignals();
    return tID;
    
}

int uthread_suspend(int tid)
{
    gCurrSched->blockSignals();
    
    //Cannot suspend the main Thread
    if(tid == 0)
    {
        cerr << THREADLIB_ERROR << SUS_MAIN_ERROR << endl;
        gCurrSched->unblockSignals();
        return FAIL;
    }
    
    Thread * thread = gCurrSched->getThread(tid);
    if(thread == nullptr)
    {
        gCurrSched->unblockSignals();
        thread = nullptr;
        return FAIL;
    }
    
    if(thread->getState() == Suspended)
    {
        gCurrSched->unblockSignals();
        thread = nullptr;
        return OK;
    }
    else
    {
        gCurrSched->unblockSignals();
        gCurrSched->suspendThread(thread);
        thread = nullptr;
        return OK;
    }
    //unblocking signals just in case
    gCurrSched->unblockSignals();
    thread = nullptr;
    return OK;
}

int uthread_resume(int tid)
{
    Thread * thread = gCurrSched->getThread(tid);
    if(thread == nullptr)
    {
        return FAIL;
    }
    int errCode =  gCurrSched->resumeThread(thread);
    thread = nullptr;
    return errCode;
}

int uthread_terminate(int tid)
{
    gCurrSched->blockSignals();
    Thread * thread = gCurrSched->getThread(tid);
    if(thread == nullptr)
    {
        gCurrSched->unblockSignals();
        return FAIL;
    }
    
    //We are terminating the main thread
    if(tid == 0)
    {
        thread = nullptr;
        delete gCurrSched; //TODO: add proper destructor for scheduler
        exit(0);
    }
    
    int errCode =  gCurrSched->terminateThread(thread);
    gCurrSched->unblockSignals();
    thread = nullptr;
    return errCode;
}

int uthread_get_tid()
{
    return gCurrSched->getRunningThreadID();
}

int uthread_get_total_quantums()
{
    return gCurrSched->getTotalQuantums();
}

int uthread_get_quantums(int tid)
{
    Thread * thread = gCurrSched->getThread(tid);
    if(thread == nullptr)
    {
        return FAIL;
    }
    int quantums = thread->getTotalQuantums();
    thread = nullptr;
    return quantums;
}