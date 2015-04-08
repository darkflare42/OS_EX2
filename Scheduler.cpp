#include "Scheduler.h"


using namespace std;


Scheduler::Scheduler(int quantum){
    
}

Scheduler::Scheduler()
    :Scheduler(DEFAULT_QUANTUM){
}

int Scheduler::init(int quantum){
    
    try{
        
        setTimerIntervals(quantum);
        Thread::InitiateIDList(); // TODO requires a debug.
        _runningThreadID = Thread::NewID(); //Set the running ID Thread to 0
        _threadMap.insert({0, shared_ptr<Thread>(new Thread(0, ORANGE, NULL))});
        _threadMap[0]->setState(Running);
        
        //TODO: Maybe the mask needs to be set to SIGVTALRM
        sigemptyset(&_mask); //empty the signal mask
        startTimer();
    }
    catch(...){
        return FAIL;
    }
    
    return OK;
}

int Scheduler::allocateID(){
    //return NewID();
    return Thread::NewID();
}

void Scheduler::startTimer(){
    //The function timerTick will be called whenever there will be a timer tick
    signal(SIGVTALRM, timerTick);
    
    //Note: _tv is initiated in the init function, therefore we can use it 
    //in the call to setitimer
    if(setitimer(ITIMER_VIRTUAL, &_tv, NULL)){
        //TODO: Error
    }

}

//This function will be called by ther timerTick function
void Scheduler::schedulerTick(int sig){
    _totalQuantums++; //TODO: Maybe += quantum value?
    
    //We have threads that need to run, if this is empty then the running
    //thread is exclusive, and runs until another queue enters the readyqueue
    if(!_readyQueue.empty()){
        changeThreadQueue(_readyQueue.pop(), Running);
    }
    
    //This will be called when there is a special instance (a thread suspending
    //itself) or when the timer has expired
    if(sig != SIGVTALRM){
        resetTimer();
    }
    
}

void Scheduler::resetTimer(){
    
    //Forcefully stop the timer
    if(setitimer(ITIMER_VIRTUAL, NULL, NULL)){
        //TODO: Error handling
    }
    
    //If the alarm signal is pending
    if(isAlrmPending()){
        int signal;
        sigset_t pendingSet;
        
        
        //Empty the set
        if(sigemptyset(&pendingSet)){
            //TODO: error handling
        }
        
        //Insert SIGVTALRM
        if(sigaddset(&pendingSet, SIGVTALRM)){
            //TODO: Error handling
        }
        
        //Wait for the signal to "jump", i.e remove it from pending
        if(sigwait(&pendingSet, &signal)){
            //TODO: Error handling
        }
        
    }
    
    //Start the timer again
    if(setitimer(ITIMER_VIRTUAL, &_tv, NULL)){
        //TODO: Error handling
    }
    
    return OK;
}

//This function returns true if the ALRM signal is pending
int Scheduler::isAlrmPending(){
    sigset_t set;
    
    //Get the pending signals set
    if(sigpending(&set)){
        //TODO: error handling
    }
    
    //This checks if SIGVTALRM is in the pending set
    int sigAlrmPending = sigismember(&set, SIGVTALRM);
    //This occurs if there was an error with sigismember
    if(sigAlrmPending == -1){
        //TODO: error handling
    }
    
    return sigAlrmPending;
    
}

//This function blocks the SIGVTALRM signal
void Scheduler::blockSignals(){
    
    sigset_t tempMask;
    
    //Empty the mask
    if(sigemptyset(&tempMask)){
        //TODO: Error Handling
    }
    
    //Add the SIGVTALRM to the set
    if(sigaddset(&tempMask, SIGVTALRM)){
        //TODO: Error handling
    }
    
    //Block the mask, and save the old blocked signals in _mask
    if(sigprocmask(SIG_SETMASK, &tempMask, &_mask)){
        //TODO: Error Handling
    }
}

//This function unblocks the current signals and reverts to the previous
//blocked signals that were saved in _mask
void Scheduler::unblockSignals(){
    if(sigprocmask(SIG_SETMASK, &_mask, NULL)){
        //TODO: Error Handling
    }
}


Scheduler *currSched = new Scheduler();


//This is declared outside the scope of the Scheduler because of the 
//signal function constraints
void timerTick(int sig){
    
    //TODO: Check if we can move env into private and a function that returns it
    int tempVal = sigsetjmp(currSched->getRunningThread()->env, 1);
    if(tempVal == 1){
        return;
    }
    
    //Call the scheduler tick function in the scheduler
    currSched->schedulerTick(sig);
    currSched->startTimer(); //We reset the timer each tick so as not to have
                             //timing issues
    siglongjmp(currSched->getRunningThread()->env, 1);
}

shared_ptr<Thread> Scheduler::getThread(int tid){
    shared_ptr<Thread> thread = nullptr;
    try{
        thread = _threadMap[tid];
        //TODO: Check if throws exception when it's not there
    }
    catch(...){
        return nullptr;
    }
    return thread;
    //std::shared_ptr<Thread> temp = make_shared<Thread>(_threadMap[tid]);
    //return temp;
}

int Scheduler::spawnThread(void(*f)(), Priority pr){
    int newID = Thread::NewID();
    if(newID == FAIL){
        return FAIL;
    }
    _threadMap.insert({newID, shared_ptr<Thread>(new Thread(newID, pr, f))});
    _readyQueue.push(_threadMap[newID]);
}

//Probably finished
int Scheduler::resumeThread(shared_ptr<Thread> thread){
    
    //Can resume a thread only if it is suspended
    if(thread->getState() == Suspended)
    {
        changeThreadQueue(thread, Ready);
    }
    return OK;
}

//Probably finished
int Scheduler::suspendThread(shared_ptr<Thread> thread){
    //Sanity check, maybe redundant 
    if(thread->getState() == Suspended){
        return OK;
    }
    
    //Save the current thread environment
    int tempVal = sigsetjmp(thread->env, 1);
    if(tempVal == 1){
        return OK;
    }
    
    //Change the queue
    bool isRunning = (thread->getState()== Running);
    changeThreadQueue(thread, Suspended);
    
    //If the thread suspended was running, the timer needs to be reset and a new
    //thread should be pushed to Running with full quantums
    if(isRunning){
        schedulerTick(SIG_SPEC_ALRM); //Manually call the scheduler tick
    }
    
    siglongjmp(thread->env, 1);
    
    return OK;
}



int Scheduler::terminateThread(shared_ptr<Thread> thread){
    
    //TODO: removeid is also in destructor of Thread, check what happens, maybe
    //delete thread (deleting the actual thread and all shared ptrs) ??
    bool isRunning = (thread->getState() == Running);
    Thread::RemoveID(thread->getID());
    _threadMap.erase(thread->getID());
    if(isRunning){
        schedulerTick(SIG_SPEC_ALRM); //Manually call the scheduler tick
        siglongjmp(getRunningThread()->env, 1);
    }
    return OK;
}

void Scheduler::changeThreadQueue(shared_ptr<Thread> thread, State newState){
    //TODO: debug.
    //Assumes relocation of thread is always successful and updates the correct state.
    switch(thread->getState()) {
        case Running:
            _runningThread = 0; //Nullify the running thread
            break;
        case Ready:
            _readyQueue.pop(thread);
            break;
        case Suspended:
            _suspendedQueue.pop(thread);
            break;
    }
    
    thread->setState(newState);
    switch (newState) {
        case Running:
            changeRunningThread(thread);
            break;
        case Ready:
            _readyQueue.push(thread);
            break;
        case Suspended:
            _suspendedQueue.push(thread);
            break;
    }
    
    
}

void Scheduler::changeRunningThread(shared_ptr<Thread> newThread){
    //Move the current running thread to ready queue
    changeThreadQueue(_threadMap[_runningThreadID], Ready);
    
    //Move the new thread into the running state
    _runningThreadID = newThread->getID();
    newThread->increaseTotalQuantums(1); //Check if need += quantum value
}

int Scheduler::getRunningThreadID(){
    return _runningThread->getID();
}

int Scheduler::getTotalQuantums(){
    return _totalQuantums;
}

shared_ptr<Thread> Scheduler::getRunningThread(){
    return getThread(_runningThreadID);
}

void Scheduler::setTimerIntervals(int quantums){
    _tv.it_value.tv_sec = quantums / USECS_TO_SEC;
    _tv.it_value.tv_usec = quantums % USECS_TO_SEC;
    _tv.it_interval.tv_sec = 0;
    _tv.it_interval.tv_usec = 0;
    
}