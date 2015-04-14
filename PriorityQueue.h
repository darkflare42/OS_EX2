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
     * Copy constructor.
     */
    PriorityQueue(const PriorityQueue& orig);
    
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
