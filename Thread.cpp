/* 
 * File:   Thread.cpp
 * Author: odedex
 * 
 * Created on April 4, 2015, 11:37 AM
 */

#include "Thread.h"
#include <algorithm>
#include <list>


Thread::Thread(int id, Priority prio, void (*entry)(void)) : 
    _id(id), _totalQuantums(0), _prio(prio),_currState(Ready), _entry(entry) {
}

Thread::Thread(const Thread& orig) {
}

Thread::~Thread() {
    RemoveID(_id);
}

Priority Thread::getPriority() {
    return _prio;
}


void Thread::InitiateIDList() {
    for (int i = 0 ; i < MAX_THREAD_NUM ; i++)
    {
        idList.emplace_back(i);
    }
}

void Thread::RemoveID(int toRemove) {
    std::list<int>::iterator i = idList.begin();
    for ( ; i != idList.end() ; i++)
    {
        if (toRemove < *i)
        {
            idList.insert(i, toRemove);
            break;
        }
    }
    if (i == idList.end())
    {
        idList.push_back(toRemove);
    }
}
/**
 * Returns the lowest available ID.
 * @return lowest available ID. -1 if none is available.
 */
int Thread::NewID() {
    if (idList.size() == 0)
    {
        return -1;
    }
    int temp = idList.front();
    idList.erase(idList.begin());
    return temp;
}

void Thread::increaseTotalQuantums(int value){
    _totalQuantums+=value;
}

int Thread::getTotalQuantums() {
    return _totalQuantums;
}

int Thread::getID(){
    return _id;
}

void Thread::setState(State stateToSet){
    _currState = stateToSet;
}

State Thread::getState(){
    return _currState;
}
