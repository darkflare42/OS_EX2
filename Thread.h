/* 
 * File:   Thread.h
 * Author: odedex
 *
 * Created on April 4, 2015, 11:37 AM
 */

#ifndef THREAD_H
#define	THREAD_H
#include "ThreadUtils.h"
#include "uthreads.h"
#include <list>
using namespace std;

class Thread {
public:
    Thread();
    Thread(const Thread& orig);
    virtual ~Thread();
    Priority getPriority();
    
    int getTotalQuantums();
    int getID();
    State getState();
    void setState(State stateToSet);
    static int NewID();
private:
    static void RemoveID(int toRemove);
    
    int _id;
    int _totalQuantums;
    Priority _prio;
    State _currState;
};

static std::list<int> idList;
#endif	/* THREAD_H */

