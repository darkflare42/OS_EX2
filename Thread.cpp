/* 
 * File:   Thread.cpp
 * Author: odedex
 * 
 * Created on April 4, 2015, 11:37 AM
 */

#include "Thread.h"
#include <algorithm>
#include <list>
#include <cstring>
#include <stdexcept>


#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
		"rol    $0x11,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5 

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
		"rol    $0x9,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}

#endif



Thread::Thread(int id, Priority prio, void (*entry)(void)) : 
    _stack(new char[STACK_SIZE]()), _id(id), _totalQuantums(0), 
        _prio(prio),_currState(Ready), _entry(entry) 
{
    
    //Main thread creation
    if(id == MAIN_THREAD_ID)
    {
        _totalQuantums = 1;
        return;
    }
    
    address_t sp, pc;
    sp = (address_t)_stack + STACK_SIZE - sizeof(address_t);
    pc = (address_t)entry;
    
    
    if(sigsetjmp(_env, 1))
    {
        //TODO: Error handling
    }
    
    _env->__jmpbuf[JB_SP] = translate_address(sp);
    _env->__jmpbuf[JB_PC] = translate_address(pc);
    
    if(sigemptyset(&_env->__saved_mask))
    {
        //TODO: Error handling
    }
}

Thread::Thread(const Thread& orig):
    _stack(orig._stack), _id(orig._id), _totalQuantums(orig._totalQuantums),
    _prio(orig._prio), _currState(orig._currState)
{
    	memcpy(_env, orig._env, sizeof(sigjmp_buf));
}

Thread::~Thread() 
{
    delete _stack;
}

Priority Thread::getPriority() 
{
    return _prio;
}


void Thread::InitiateIDList() 
{
    if (gIdList.size() != 0) 
    {
        throw std::logic_error("ID list already initialized!");
    }
    for (int i = 0 ; i < MAX_THREAD_NUM ; i++)
    {
        gIdList.emplace_back(i);
    }
}

void Thread::RemoveID(int toRemove) 
{
    std::list<int>::iterator i = gIdList.begin();
    for ( ; i != gIdList.end() ; i++)
    {
        if (toRemove < *i)
        {
            gIdList.insert(i, toRemove);
            break;
        }
    }
    if (i == gIdList.end())
    {
        gIdList.push_back(toRemove);
    }
}
/**
 * Returns the lowest available ID.
 * @return lowest available ID. -1 if none is available.
 */
int Thread::NewID() 
{
    if (gIdList.size() == 0)
    {
        return -1;
    }
    int temp = gIdList.front();
    gIdList.erase(gIdList.begin());
    return temp;
}

void Thread::increaseTotalQuantums(int value)
{
    _totalQuantums+=value;
}

int Thread::getTotalQuantums() 
{
    return _totalQuantums;
}

int Thread::getID()
{
    return _id;
}

void Thread::setState(State stateToSet)
{
    _currState = stateToSet;
}

State Thread::getState()
{
    return _currState;
}
