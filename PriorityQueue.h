/* 
 * File:   PriorityQueue.h
 * Author: odedex
 *
 * Created on April 4, 2015, 11:31 AM
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
    PriorityQueue();
    PriorityQueue(const PriorityQueue& orig);
    virtual ~PriorityQueue();
    
    Thread * pop();
    void push(Thread * threadPtr);
    void pop(Thread * thread);
    
    bool empty();
    int size();
    
private:
    std::list<Thread *> _redQ;
    std::list<Thread *> _orangeQ;
    std::list<Thread *> _greenQ;
    int _size;
};

#endif	/* PRIORITYQUEUE_H */