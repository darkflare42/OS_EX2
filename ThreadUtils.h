/* 
 * File:   ThreadUtils.h
 * Author: odedex
 *
 * Created on April 4, 2015, 11:20 AM
 */

#ifndef THREADUTILS_H
#define	THREADUTILS_H


enum ERRCODE{
    OK = 0,
    FAIL = -1,
           
};

enum State{
    Running = 0,
    Ready = 1,
    Suspended = 2,
    Terminated = 3, //Maybe unnecessary
};

#define MAIN_THREAD_ID 0

#endif	/* THREADUTILS_H */
