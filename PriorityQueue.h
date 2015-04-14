/**
* @file PriorityQueue.h
* @author Oded Abramas <odedab@cs.huji.ac.il>
* @version 1.0
* @date 14 Apr 2015
*
* @brief Priority Queue class implementing support for 3 different priorities: Green, Orange and Red.
*        The class wraps 3 standard library lists and provides a standard queue interface.
*
* @section LICENSE
* This program is not a free software.
*
* @section DESCRIPTION
* USAGE: None.
* Process: None.
* Output: None.
*/
#ifndef PRIORITYQUEUE_H
#define	PRIORITYQUEUE_H

#include "ThreadUtils.h"
#include "Thread.h"
#include <memory>
#include <list>

class PriorityQueue 
{
public:
    /**
    * Standard constructor.
    */
    PriorityQueue();
    
    /**
    * Standard destructor.
    */
    virtual ~PriorityQueue();
    
    /**
    * Remove the first Thread * available in the queue, according to the priority.
    * @return Pointer to the thread.
    */
    Thread * pop();
    
    /**
    * Remove a specific thread pointer from the queue.
    * If the pointe is not in the queue, it does nothing.
    * @param threadPtr a Thread pointer.
    * @return void
    */
    void pop(Thread * thread);
    
    /**
    * Push a thread pointer into the queue, according to its' priority.
    * @param threadPtr a Thread pointer.
    * @return void
    */
    void push(Thread * threadPtr);
    
    /**
    * Check if the queue is empty.
    * @return True iff the queue is empty.
    */
    bool empty();
    
    /**
    * Check the number of elements in the queue.
    * @return Number of elements.
    */
    int size();
    
private:
    std::list<Thread *> _redQ;
    std::list<Thread *> _orangeQ;
    std::list<Thread *> _greenQ;
    int _size;
};

#endif	/* PRIORITYQUEUE_H */
