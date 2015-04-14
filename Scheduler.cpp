#include "Scheduler.h"
#include <iostream>

using namespace std;


Scheduler::Scheduler(int quantum) : _totalQuantums(0){
    
}

Scheduler::Scheduler()
    :_totalQuantums(0){
}

int Scheduler::init(int quantum){
    
    if(quantum <= 0){
        cout << "thread library error: non-positive quantum usecs" << endl;
        return FAIL;
    }
    
    try{
        
        setTimerIntervals(quantum);
        Thread::InitiateIDList(); // TODO requires a debug.
        _runningThreadID = Thread::NewID(); //Set the running ID Thread to 0
        _threadMap.insert({0, (new Thread(0, ORANGE, NULL))});
        //_threadMap.insert({0, make_shared<Thread>(Thread(0, ORANGE, NULL))});
        _threadMap[0]->setState(Running);
        
        //TODO: Maybe the mask needs to be set to SIGVTALRM
        sigemptyset(&_mask); //empty the signal mask
        sigaddset(&_mask, SIGVTALRM);
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
    //signal(SIGVTALRM, timerTick);
    
    //cerr << "Starting timer" << endl;
    
    action.sa_handler = timerTick;
    
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask, SIGVTALRM);
    sigaction(SIGVTALRM, &action, NULL);
    //Note: _tv is initiated in the init function, therefore we can use it 
    //in the call to setitimer
    if(setitimer(ITIMER_VIRTUAL, &_tv, NULL)){
        //TODO: Error
    }

}

//This function will be called by the timerTick function
void Scheduler::schedulerTick(int sig){
    //cerr << "Entered schedulerTick, signal:" << sig << endl;
    _totalQuantums++; //TODO: Maybe += quantum value?
    
    //We have threads that need to run, if this is empty then the running
    //thread is exclusive, and runs until another queue enters the readyqueue
    if(!_readyQueue.empty())
    {
        changeThreadQueue(_readyQueue.pop(), Running);
    }
    else //The main thread is the ONLY current running thread, update quantas
    { 
        getThread(_runningThreadID)->increaseTotalQuantums(1);
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
    
    //return OK; //TODO Or, you tried to return a value from void.
}

//This function returns true if the ALRM signal is pending
//That means that the SIGVTALRM was "thrown" while we blocked signals
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

Thread * Scheduler::getThread(int tid){
    Thread * thread = nullptr;
    if (_threadMap.find(tid) != _threadMap.end()) {
        thread = _threadMap.at(tid);//_threadMap[tid];
    }
    else {
        cout << "thread library error: no such thread" << std::endl;
        thread = nullptr;
    }
    return thread;
    
}

int Scheduler::spawnThread(void(*f)(), Priority pr){
    
    
    int newID = Thread::NewID();
    if(newID == FAIL){
        cout << "thread library error: maximum threads" << endl;
        return FAIL;
    }
    _threadMap.insert({newID, (new Thread(newID, pr, f))});
    _readyQueue.push(_threadMap[newID]);
    return newID;
}

//Probably finished
int Scheduler::resumeThread(Thread * thread){
    //Can resume a thread only if it is suspended
    if(thread->getState() == Suspended)
    {
        changeThreadQueue(thread, Ready);
    }
    
    return OK;
}

//Probably finished
int Scheduler::suspendThread(Thread * thread){
    //Sanity check, maybe redundant 
    //cerr << "suspending thread, ID:" << thread->getID() << endl;
    if(thread->getState() == Suspended){
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
    
    
    return OK;
}



int Scheduler::terminateThread(Thread * thread){
    
    bool isRunning = (thread->getState() == Running);
    Thread::RemoveID(thread->getID());
    _threadMap.erase(thread->getID());
    if(isRunning){
        schedulerTick(SIG_SPEC_ALRM); //Manually call the scheduler tick
        siglongjmp(getRunningThread()->env, 1);
    }
    return OK;
}

void Scheduler::changeThreadQueue(Thread * thread, State newState){
    //Assumes relocation of thread is always successful and updates the correct state.
    // Remove from old state.
    switch(thread->getState()) {
        case Running:
            _runningThreadID = -1; //Nullify the running thread
            break;
        case Ready:
            _readyQueue.pop(thread);
            break;
        case Suspended:
            _suspendedQueue.pop(thread);
            break;
    }
    
    // Update new state.
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

void Scheduler::changeRunningThread(Thread * newThread){
    //Move the current running thread to ready queue
    if(_threadMap.find(_runningThreadID) != _threadMap.end())
    {
        changeThreadQueue(_threadMap[_runningThreadID], Ready);
    }
    //Move the new thread into the running state
    _runningThreadID = newThread->getID();
    newThread->increaseTotalQuantums(1); //Check if need += quantum value
}

int Scheduler::getRunningThreadID(){
    return _runningThreadID;
}

int Scheduler::getTotalQuantums(){
    return _totalQuantums;
}

Thread * Scheduler::getRunningThread(){
    return getThread(_runningThreadID);
}

void Scheduler::setTimerIntervals(int quantums){
    _tv.it_value.tv_sec = 0;//quantums / USECS_TO_SEC;
    _tv.it_value.tv_usec = quantums;// % USECS_TO_SEC;
    _tv.it_interval.tv_sec = 0;//quantums / USECS_TO_SEC;
    _tv.it_interval.tv_usec = 0;
    
}
