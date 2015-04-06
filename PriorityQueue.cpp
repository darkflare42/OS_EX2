/* 
 * File:   PriorityQueue.cpp
 * Author: odedex
 * 
 * Created on April 4, 2015, 11:31 AM
 */

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {
}

PriorityQueue::PriorityQueue(const PriorityQueue& orig) {
}

PriorityQueue::~PriorityQueue() {
}

void PriorityQueue::Enqueue(std::shared_ptr<Thread> threadPtr) {
    switch(threadPtr->getPriority()) {
        case RED:
            redQ.push_back(threadPtr);
            break;
        case ORANGE:
            orangeQ.push_back(threadPtr);
            break;
        case GREEN:
            greenQ.push_back(threadPtr);
            break;
    }
}

std::shared_ptr<Thread> PriorityQueue::Dequeue(){
    std::shared_ptr<Thread> temp;
    if (redQ.size() > 0) {
        temp = redQ.front();
        redQ.pop_front();
    }
    else if (orangeQ.size() > 0) {
        temp = orangeQ.front();
        orangeQ.pop_front();
    }
    else if (greenQ.size() > 0) {
        temp = greenQ.front();
        greenQ.pop_front();
    }
    return temp;
}

/**
 * Remove a shared_ptr from a queue, if it is in the Priority queue,
 * otherwise does nothing.
 * @param thread
 * @return void
 */
void PriorityQueue::Dequeue(std::shared_ptr<Thread> thread){
    
    std::list<std::shared_ptr<Thread>> *trgtList;
    switch (thread->getPriority()) {
        case RED:
            trgtList = &redQ;
            break;
        case ORANGE:
            trgtList = &orangeQ;
            break;
        case GREEN:
            trgtList = &greenQ;
            break;
    }
    
    for (auto i = trgtList->begin() ; i != trgtList->end() ; i++)
    {
        if (thread == *i) {
            trgtList->erase(i);
            break;
        }
    }
}