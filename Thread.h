/* 
 * File:   Thread.h
 * Author: odedex
 *
 * Created on April 4, 2015, 11:37 AM
 */

#ifndef THREAD_H
#define	THREAD_H
#include "ThreadUtils.h"
#include <vector>
using namespace std;

class Thread {
public:
    Thread();
    Thread(const Thread& orig);
    virtual ~Thread();
    Priority getPriority();
    
    
private:
    static void RemoveID(int toRemove);
    static int NewID();
    
    static vector<int> idList;
    Priority prio;
    
    
};

#endif	/* THREAD_H */

