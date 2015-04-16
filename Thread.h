/**
* @file Thread.h
* @author Oded Abramas <odedab@cs.huji.ac.il>
* @version 1.0
* @date 14 Apr 2015
*
* @brief Thread class to support a user controlled thread. Each instance of the class holds
*        all relevant data for a thread: thread id, total amount of quantums, priority,
*        current state (running, blocked or ready) and a pointer to a start fucntion.
*
* @section LICENSE
* This program is not a free software.
*
* @section DESCRIPTION
* USAGE: None.
* Process: None.
* Output: None.
*/
#ifndef THREAD_H
#define	THREAD_H
#include <setjmp.h>
#include <signal.h>
#include <memory>
#include <stack>
#include "ThreadUtils.h"
#include "uthreads.h"
#include <list>

#define SECOND 1000000
#define STACK_SIZE 4096

class Thread 
{
public:
    /**
    * Standard constructor.
    */
    Thread(int id, Priority prio, void (*entry)(void));
    
    /**
    * Copy constructor.
    */
    Thread(const Thread& orig);
    
    /**
    * Standard destructor.
    */
    ~Thread();
    
    /**
    * Get the priority of the thread (RED, GREEN or ORANGE).
    * @return enum Priority.
    */
    Priority getPriority();
    
    /**
    * Get the total amount of quantums the thread had recieved.
    * @return Number of quantums.
    */
    int getTotalQuantums();
    
    /**
    * Get the ID of the thread.
    * @return Thread ID.
    */
    int getID();
    
    /**
    * Get the state of the thread (Running, Ready or Suspended).
    * @return enum State.
    */
    State getState();
    
    /**
    * Set the state of the thread.
    * @param stateToSet State enum to set.
    * @return void.
    */
    void setState(State stateToSet);
    
    /**
    * Incrase the number of quantums the thread had recieved by a given number.
    * @param value Number of quantums to incrase by.
    * @return void.
    */
    void increaseTotalQuantums(int value);
    
    /**
    * Static function to initiate the IDList. Number of IDs in the list is determined
    * by a global value.
    * @throws logic_exception if the the function is called more than once.
    * @return void.
    */
    static void InitiateIDList();
    
    /**
    * Static function to fetch the lowest available ID. Removes that ID from
    * the available IDs.
    * @return int of the new ID. -1 if the list is empty.
    */
    static int NewID();
    
    /**
    * Static function to return an ID to the available ID list.
    * Assumes that the handler properly deleted the thread to avoid
    * having 2 or more threads with the same ID.
    * @return void.
    */
    static void RemoveID(int toRemove);
    
    
    //Public members for thread (as instructed).
    char * _stack;
    sigjmp_buf _env;
    
private:
    
    int _id;
    int _threadQuantums;
    Priority _prio;
    State _currState;
    void (*_entry)(void);
    
};

// List of available IDs.
static std::list<int> gIdList;
#endif	/* THREAD_H */

