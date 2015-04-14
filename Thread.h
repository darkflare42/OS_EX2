/* 
 * File:   Thread.h
 * Author: odedex
 *
 * Created on April 4, 2015, 11:37 AM
 */

#ifndef THREAD_H
#define	THREAD_H
#include <setjmp.h>
#include <signal.h>
#include <memory>
#include <stack>
#include "ThreadUtils.h"
#include "uthreads.h"
#include <list>

#define SECOND 1000000
#define STACK_SIZE 4096

class Thread 
{
public:
    Thread(int id, Priority prio, void (*entry)(void));
    Thread(const Thread& orig);
    ~Thread();
    
    Priority getPriority();
    
    int getTotalQuantums();
    int getID();
    State getState();
    void setState(State stateToSet);
    void increaseTotalQuantums(int value);
    
    static void InitiateIDList();
    static int NewID();
    static void RemoveID(int toRemove);
    
    
    //Public members for thread (as instructed)
    char * _stack;
    sigjmp_buf _env;
    
private:
    
    int _id;
    int _totalQuantums;
    Priority _prio;
    State _currState;
    void (*_entry)(void);
    
};

static std::list<int> gIdList;
#endif	/* THREAD_H */

