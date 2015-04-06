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
#include "Thread.h"
#include "PriorityQueue.h"

#define DEFAULT_QUANTUM 2;

class Scheduler {
    public: 
        
        Scheduler();
        Scheduler(int quantum);
        
        int allocateID();
    private:
        struct itimerval _tv;
        PriorityQueue _readyQueue;
        PriorityQueue _suspendedQueue;
        PriorityQueue _sleepingQueue;
    
};


#endif	/* SCHEDULER_H */

