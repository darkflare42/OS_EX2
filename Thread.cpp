/* 
 * File:   Thread.cpp
 * Author: odedex
 * 
 * Created on April 4, 2015, 11:37 AM
 */

#include "Thread.h"
#include <algorithm>
#include <list>


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
    _id(id), _totalQuantums(0), _prio(prio),_currState(Ready), _entry(entry) {
    
    //Main thread creation
    if(entry == NULL){
        return;
    }
    
    address_t sp, pc;
    sp = (address_t)_stack + STACK_SIZE - sizeof(address_t);
    pc = (address_t)entry;
    
    
    if(sigsetjmp(env, 1)){
        //TODO: Error handling
    }
    
    env->__jmpbuf[JB_SP] = translate_address(sp);
    env->__jmpbuf[JB_PC] = translate_address(pc);
    
    if(sigemptyset(&env->__saved_mask)){
        //TODO: Error handling
    }
    
    
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
