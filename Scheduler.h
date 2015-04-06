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
#include "Thread.h"
#include "ThreadUtils.h"
#include "PriorityQueue.h"
#include <map>

#define DEFAULT_QUANTUM 2

class Scheduler {
    public: 
        Scheduler(int quantum);
        Scheduler();
        
        int init(int quantum);
        std::shared_ptr<Thread> getThread(int tid);
        
        //Maybe all these need to be references (& after the shared_ptr)
        int resumeThread(shared_ptr<Thread> thread);
        int suspendThread(shared_ptr<Thread> thread);
        int terminateThread(shared_ptr<Thread> thread);
        
        void startTimer();
        
        int allocateID();
        int getRunningThreadID();
        int getTotalQuantums();
    private:
        struct itimerval _tv;
        PriorityQueue _readyQueue;
        PriorityQueue _suspendedQueue;
        PriorityQueue _sleepingQueue;
        std::shared_ptr<Thread> _runningThread;
        int _totalQuantums;
        
        std::map<int, Thread> _threadMap;
        
        void setTimerIntervals(int quantums);
    
};


#endif	/* SCHEDULER_H */

