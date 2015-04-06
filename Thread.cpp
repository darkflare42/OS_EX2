/* 
 * File:   Thread.cpp
 * Author: odedex
 * 
 * Created on April 4, 2015, 11:37 AM
 */

#include "Thread.h"
#include <algorithm>


Thread::Thread() {
}

Thread::Thread(const Thread& orig) {
}

Thread::~Thread() {
}

Priority Thread::getPriority() {
    return prio;
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

int Thread::NewID() {
    int temp = idList.front();
    idList.erase(idList.begin());
    return temp;
}


int Thread::getTotalQuantums() {
    return _totalQuantums;
}


int Thread::getID(){
    return _id;
}

