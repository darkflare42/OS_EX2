/* 
 * File:   Scheduler.h
 * Author: okeren
 *
 * Created on April 6, 2015, 12:18 AM
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include <sys/time.h>
#include <signal.h>
#include <memory>
#include <iostream>
#include "Thread.h"
#include "ThreadUtils.h"
#include "PriorityQueue.h"
#include <map>

#define DEFAULT_QUANTUM 2
#define USECS_TO_SEC 1000000

class Scheduler {
    public: 
        Scheduler(int quantum);
        Scheduler();
        
        int init(int quantum);
        std::shared_ptr<Thread> getThread(int tid);
        
        //Maybe all these need to be references (& after the shared_ptr)
        int spawnThread(void (*f)(void), Priority pr);
        int resumeThread(shared_ptr<Thread> thread);
        int suspendThread(shared_ptr<Thread> thread);
        int terminateThread(shared_ptr<Thread> thread);
        
        void startTimer();
        void resetTimer();
        void schedulerTick(int sig);
        void changeThreadQueue(shared_ptr<Thread> thread, State newState);
        void changeRunningThread(shared_ptr<Thread> newThread);
        
        int allocateID();
        int getRunningThreadID();
        int getTotalQuantums();
    private:
        struct itimerval _tv;
        PriorityQueue _readyQueue;
        PriorityQueue _suspendedQueue;
        std::shared_ptr<Thread> _runningThread; //TODO can be deleted?
        int _runningThreadID;
        int _totalQuantums;
        
        std::map<int, shared_ptr<Thread>> _threadMap;
        
        void setTimerIntervals(int quantums);
    
};

void timerTick(int sig);

#endif	/* SCHEDULER_H */

