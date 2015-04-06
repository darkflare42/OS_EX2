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
    void Enqueue(std::shared_ptr<Thread> threadPtr);
    std::shared_ptr<Thread> Dequeue();
    void Dequeue(std::shared_ptr<Thread> thread);
    
private:
    std::list<std::shared_ptr<Thread>> redQ;
    std::list<std::shared_ptr<Thread>> orangeQ;
    std::list<std::shared_ptr<Thread>> greenQ;
};

#endif	/* PRIORITYQUEUE_H */