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
#define USECS_TO_SEC 1000000 //TODO: Check if to remove
#define SIG_SPEC_ALRM SIGVTALRM + 1

class Scheduler 
{
    public: 
        Scheduler(int quantum);
        Scheduler();
       
        int init(int quantum);
 
        void startTimer();
        void resetTimer();
        void schedulerTick(int sig);
        void changeThreadQueue(Thread * thread, State newState);
        void changeRunningThread(Thread * newThread);
        void blockSignals();
        void unblockSignals();
        
        int spawnThread(void (*f)(void), Priority pr);
        int resumeThread(Thread * thread);
        int suspendThread(Thread * thread);
        int terminateThread(Thread * thread);
        int isAlrmPending();
        int allocateID();
        int getRunningThreadID();
        int getTotalQuantums();
        Thread * getRunningThread();
        Thread * getThread(int tid);
    private:
        struct itimerval _tv;
        PriorityQueue _readyQueue;
        PriorityQueue _suspendedQueue;
        int _runningThreadID;
        int _totalQuantums;
        struct sigaction _action;
        sigset_t _mask;
        
        std::map<int, Thread*> _threadMap;
        
        void setTimerIntervals(int quantums);
    
};

void timerTick(int sig);

#endif	/* SCHEDULER_H */

