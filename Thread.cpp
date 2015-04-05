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

static void Thread::RemoveID(int toRemove) {
    unsigned int i;
    for (i = 0 ; i < idList.size() ; i++)
    {
        if (toRemove < idList[i])
        {
            idList.insert(i, toRemove);
            break;
        }
    }
    if (i == idList.size())
    {
        idList.push_back(toRemove);
    }
}

static int Thread::NewID() {
    int temp = idList[0];
    idList.erase(0);
    return temp;
}

