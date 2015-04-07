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
        _threadMap.insert({0, shared_ptr<Thread>(new Thread())});
        _threadMap[0]->setState(Running);
        //startTimer
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
    //TODO: start timer
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

int Scheduler::spawnThread(void(*f)()){
    int newID = Thread::NewID();
    if(newID == FAIL){
        return FAIL;
    }
    _threadMap.insert({newID, shared_ptr<Thread>(new Thread())});
    _readyQueue.push(_threadMap[newID]);
}

int Scheduler::resumeThread(shared_ptr<Thread> thread){
    
    //Can resume a thread only if it is suspended
    if(thread->getState() == Suspended)
    {
        
        changeThreadQueue(thread, Ready);
    }
    return OK;
}

int Scheduler::suspendThread(shared_ptr<Thread> thread){
    //Sanity check
    if(thread->getState() == Suspended){
        return OK;
    }
    
    changeThreadQueue(thread, Suspended);
    
    //TODO: Check what is needed to happen if a thread suspends itself!
    
    
    return OK;
}

int Scheduler::terminateThread(shared_ptr<Thread> thread){
    
    //TODO: add stuff
    _threadMap.erase(thread->getID());
    
    return OK;
}

void Scheduler::changeThreadQueue(shared_ptr<Thread> thread, State newState){
    //TODO: debug.
    //Assumes relocation of thread is always successful and updates the correct state.
    switch(thread->getState()) {
        case Running:
            break;
        case Ready:
            _readyQueue.pop(thread);
            break;
        case Suspended:
            _suspendedQueue.pop(thread);
            break;
    }
    
    switch (newState) {
        case Running:
            break;
        case Ready:
            _readyQueue.push(thread);
            break;
        case Suspended:
            _suspendedQueue.push(thread);
            break;
    }
    
    thread->setState(newState);
}

int Scheduler::getRunningThreadID(){
    return _runningThread->getID();
}

int Scheduler::getTotalQuantums(){
    return _totalQuantums;
}

void Scheduler::setTimerIntervals(int quantums){
    _tv.it_value.tv_sec = quantums / 100;
    _tv.it_value.tv_usec = quantums % 100;
    _tv.it_interval.tv_sec = 0;
    _tv.it_interval.tv_usec = 0;
    
}