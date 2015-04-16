#include "uthreads.h"
#include "Scheduler.h"
#include "ThreadUtils.h"

extern Scheduler * gCurrSched;

using namespace std;


/**
 * This function prints a library exception
 * @param e: The exception that was thrown by the library
 */
void printLibError(const logic_error& e)
{
    cerr << e.what() << endl;
    
}

//Initializes the scheduler using the quantum usecs
int uthread_init(int quantum_usecs)
{
    try
    {
        return gCurrSched->init(quantum_usecs);
    }
    catch(const logic_error& e)
    {
        printLibError(e);
        return FAIL;
    }
    
}

int uthread_spawn(void (*f)(void), Priority pr)
{
    try
    {
        gCurrSched->blockSignals();
    
        int tID =  gCurrSched->spawnThread(f, pr);
    
        gCurrSched->unblockSignals();
        return tID;
    }
    catch(const logic_error& e)
    {
        printLibError(e);
        return FAIL;
    }
    
    
}

int uthread_suspend(int tid)
{   
    try
    {
        gCurrSched->blockSignals();

        //Cannot suspend the main Thread
        if(tid == 0)
        {
            cerr << THREADLIB_ERROR <<  " " << SUS_MAIN_ERROR << endl;
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
    catch(const logic_error& e)
    {
        printLibError(e);
        return FAIL;
    }
    
    
    
}

int uthread_resume(int tid)
{
    try
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
    catch(const logic_error& e)
    {
        printLibError(e);
        return FAIL;
    }
    
}

int uthread_terminate(int tid)
{
    
    try
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
    catch(const logic_error& e)
    {
        printLibError(e);
        return FAIL;
    }
    
    
}

int uthread_get_tid()
{
    try
    {
        return gCurrSched->getRunningThreadID();
    }
    catch(const logic_error& e)
    {
        printLibError(e);
        return FAIL;
    }
    
}

int uthread_get_total_quantums()
{
    try
    {
        return gCurrSched->getTotalQuantums();
    }
    catch(const logic_error& e)
    {
        printLibError(e);
        return FAIL;
    }
    
}

int uthread_get_quantums(int tid)
{
    try
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
    catch(const logic_error& e)
    {
        printLibError(e);
        return FAIL;
    }
    
}