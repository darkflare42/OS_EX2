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

enum STATE{
    Running = 0,
    Suspended = 1,
    Terminated = 2,
};

#define MAIN_THREAD_ID 0

#endif	/* THREADUTILS_H */
