/* 
 * File:   PriorityQueue.cpp
 * Author: odedex
 * 
 * Created on April 4, 2015, 11:31 AM
 */

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() : _size(0) {
}

PriorityQueue::PriorityQueue(const PriorityQueue& orig) {
}

PriorityQueue::~PriorityQueue() {
}

bool PriorityQueue::empty () {
    return (_size == 0);
}

int PriorityQueue::size () {
    return _size;
}

void PriorityQueue::push(Thread * threadPtr) {
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
    _size++;
}

Thread * PriorityQueue::pop(){
    Thread * temp = nullptr;
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
    if (temp != nullptr) {
        _size--;
    }
    return temp;
}

/**
 * Remove a shared_ptr from a queue, if it is in the Priority queue,
 * otherwise does nothing.
 * @param thread
 * @return void
 */
void PriorityQueue::pop(Thread * thread){
    
    std::list<Thread *> *trgtList;
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
            _size--;
            break;
        }
    }
}