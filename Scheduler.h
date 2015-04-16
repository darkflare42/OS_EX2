/**
* @file Scheduler.h
* @author Or Keren <or.keren1@cs.huji.ac.il>
* @version 1.0
* @date 14 Apr 2015
*
* @brief This class is the main scheduling class which the uthread library uses
*        it implements a 3-priority Round Robin algorithm for scheduling 
*        between different threads. Each thread is either running, ready ,
*        suspended, (or terminated). A running thread is run for an exact amount 
*        of given time quantums (unless it suspends or terminates earlier)
*        After the quantum finishes, the thread is moved to the priority queue
*        
* 
*
* @section LICENSE
* This program is not a free software.
*
* @section DESCRIPTION
* USAGE: See API
* Process: None.
* Output: The class prints errors to cerr when a library error occurs and when
*         a system error occurs 
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


#define USECS_TO_SEC 1000000 

//Special alarm signal to indicate to the scheduler that a scheduling decision
//should be made
#define SIG_SPEC_ALRM SIGVTALRM + 1


class Scheduler 
{
public: 

    /**
    * Default ctor
    */
    Scheduler();
    
    /**
     * Destructor
     */
    ~Scheduler();

    /**
    * Initializes the Scheduler class according to the given quantums
    * @param quantum: An integer representing the number of quantums for each
    *                 virtual timer cycle 
    * @return OK if Everything initiated correctly, FAIL otherwise
    */
    int init(int quantum);

    
    /**
    * Starts the virtual timer
    */
    void startTimer();
    
    /**
    * resets the timer
    */
    void resetTimer();
    
    /**
    * This function is called every "tick" of the virtual timer, it implements
    * the scheduling logic according to the priority-RR specs given
    * @param sig: The signal that the timer sent
    */
    void schedulerTick(int sig);
    
    /**
    * Moves a thread from its current queue to the new queue according to the
    * newState parameter     
    * @param thread: The thread to move queues
    * @param newState: An enum that identifies the new state for the thread 
    */
    void changeThreadQueue(Thread * thread, State newState);
    
    /**
    * Changes the current running thread: Moves the current running thread
    * to the ready queue, and makes the newThread the running thread 
    * @param newThread: The thread to make the new running thread
    */
    void changeRunningThread(Thread * newThread);
    
    /**
    * This function blocks the SIGVTALRM signal, so that there are no 
    * interruptions for some process. It saves the current blocked signals in
    * the mask member
    */
    void blockSignals();
    
    /**
    * This function unblocks the current blocked signals and reverts it to the
    * previous state
    */
    void unblockSignals();

    /**
    * Spawns a new thread: Creates a new instance of a thread in the priority
    * queue according to the given priority, after spawning the thread will
    * eventually run unless it is suspended or terminated before running  
    * @param f: A pointer to a function that the thread executes
    * @param pr: The priority for the thread
    * @return OK if Everything initiated correctly, FAIL otherwise
    */
    int spawnThread(void (*f)(void), Priority pr);
    
    /**
    * Resumes a thread from a suspending state. If the thread is not suspended
    * i.e running or ready, then the function does not do anything
    * if the thread is suspended, then the thread is moved from the suspended
    * queue to the ready queue
    * @param thread: The thread to resume
    * @return OK if Everything initiated correctly, FAIL otherwise
    */
    int resumeThread(Thread * thread);
    
    /**
    * Suspends a thread. If the thread is suspended i.e running or ready, 
    * then the function does not do anything
    * if the thread is running, then the timer is stopped, the thread is moved
    * to the suspended queue, and a new thread becomes the running thread
    * if the thread is ready, then it is moved to the suspended queue
    * @param thread: The thread to suspend
    * @return OK if Everything initiated correctly, FAIL otherwise
    */
    int suspendThread(Thread * thread);
    
    /**
    * Terminates the given thread. If the thread is running then a scheduling
    * decision is made, i.e the timer "restarts" 
    * @param thread: The thread to terminate
    * @return OK if Everything initiated correctly, FAIL otherwise
    */
    int terminateThread(Thread * thread);
    
    /**
    * This function checks if SIGVTALRM is in a pending state, meaning it was 
    * blocked by the blocked signal mask, however it was still "thrown" by
    * the virtual timer  
    * @return The value returned from sigismember for SIGVTALRM and the blocked
    *         signals 
    */
    int isAlrmPending();
    
    /**
    * Returns the id of the current running thread
    * @return The id of the current running thread
    */
    int getRunningThreadID();
    
    /**
    * Returns the total number of quantums used by the scheduler
    * @return the total number of quantums used by the scheduler
    */
    int getTotalQuantums();
    
    /**
    * Returns a pointer to the current running thread
    * @return A pointer to the running thread
    */
    Thread * getRunningThread();
    
    /**
    * Returns a pointer to a thread according to the tid
    * @return Returns a pointer to a thread according to the tid
    */
    Thread * getThread(int tid);
    
private:
    
    //The struct that saves the timer interval values
    struct itimerval _tv;
    
    PriorityQueue _readyQueue;
    PriorityQueue _suspendedQueue;
    int _runningThreadID;
    int _totalQuantums;
    
    //This dictates (after configuration) what happens when the SIGVTALRM signal
    //Is "thrown"
    struct sigaction _action;
    
    //This is used to save the blocked signals
    sigset_t _mask;

    //The map stores all the threads
    std::map<int, Thread*> _threadMap;

    /**
    * This function sets the timer intervals according to the quantums given
    * @return quantums: The qunatum_usecs to set the interval to
    */
    void setTimerIntervals(int quantums);
    
};

/**
* This function is called whenever the virtual timer finishes its interval
* It is outside the scope of scheduler because of limitations of the sigaction
* member and the setitimer system function
* @param sig: The signal that was "thrown" by the timer
*/
void timerTick(int sig);

#endif	/* SCHEDULER_H */

