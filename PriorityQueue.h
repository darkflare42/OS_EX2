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
#include <queue>
using namespace std;

class PriorityQueue {
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue& orig);
    virtual ~PriorityQueue();
    void Enqueue(Thread thread); // TODO maybe const reference?
    Thread Dequeue();
    
private:
    queue<Thread> redQ;
    queue<Thread> orangeQ;
    queue<Thread> greenQ;
};

#endif	/* PRIORITYQUEUE_H */
