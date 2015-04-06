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
        _runningThreadID = 0; //Set the running ID Thread to 0
        _threadMap.insert({0, shared_ptr<Thread>(new Thread())});
        //startTimer
    }
    catch(...){
        return FAIL;
    }
    
    return OK;
}

int Scheduler::allocateID(){
    return Thread.getID();
}

void Scheduler::startTimer(){
    //TODO: start timer
}

shared_ptr<Thread> Scheduler::getThread(int tid){
    return _threadMap[tid];
    //std::shared_ptr<Thread> temp = make_shared<Thread>(_threadMap[tid]);
    //return temp;
}


int Scheduler::resumeThread(shared_ptr<Thread> thread){
    return OK;
}

int Scheduler::suspendThread(shared_ptr<Thread> thread){
    return OK;
}

int Scheduler::terminateThread(shared_ptr<Thread> thread){
    return OK;
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