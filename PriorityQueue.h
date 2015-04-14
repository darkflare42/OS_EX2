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

class PriorityQueue {
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue& orig);
    virtual ~PriorityQueue();
    bool empty();
    int size();
    void push(Thread * threadPtr);
    Thread * pop();
    void pop(Thread * thread);
    
private:
    std::list<Thread *> redQ;
    std::list<Thread *> orangeQ;
    std::list<Thread *> greenQ;
    int _size;
};

#endif	/* PRIORITYQUEUE_H */