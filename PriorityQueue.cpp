/* 
 * File:   PriorityQueue.cpp
 * Author: odedex
 * 
 * Created on April 4, 2015, 11:31 AM
 */

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() : _size(0) 
{
    
}

PriorityQueue::~PriorityQueue() 
{
}

bool PriorityQueue::empty () 
{
    return (_size == 0);
}

int PriorityQueue::size () 
{
    return _size;
}

void PriorityQueue::push(Thread * threadPtr) 
{
    switch(threadPtr->getPriority()) {
        case RED:
            _redQ.push_back(threadPtr);
            break;
        case ORANGE:
            _orangeQ.push_back(threadPtr);
            break;
        case GREEN:
            _greenQ.push_back(threadPtr);
            break;
    }
    _size++;
}

Thread * PriorityQueue::pop()
{
    Thread * temp = nullptr;
    if (_redQ.size() > 0) 
    {
        temp = _redQ.front();
        _redQ.pop_front();
    }
    else if (_orangeQ.size() > 0) 
    {
        temp = _orangeQ.front();
        _orangeQ.pop_front();
    }
    else if (_greenQ.size() > 0) 
    {
        temp = _greenQ.front();
        _greenQ.pop_front();
    }
    if (temp != nullptr) 
    {
        _size--;
    }
    return temp;
}

void PriorityQueue::pop(Thread * thread)
{
    
    std::list<Thread *> *trgtList;
    switch (thread->getPriority()) 
    {
        case RED:
            trgtList = &_redQ;
            break;
        case ORANGE:
            trgtList = &_orangeQ;
            break;
        case GREEN:
            trgtList = &_greenQ;
            break;
    }
    
    for (auto i = trgtList->begin() ; i != trgtList->end() ; i++)
    {
        if (thread == *i) 
        {
            trgtList->erase(i);
            _size--;
            break;
        }
    }
}