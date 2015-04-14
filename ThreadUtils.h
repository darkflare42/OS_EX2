/**
* @file ThreadUtils.h
* @author Or Keren <or.keren1@cs.huji.ac.il>
* @version 1.0
* @date 14 Apr 2015
*
* @brief This Class holds enums and consts that are used throughout the code
*        
* 
*
* @section LICENSE
* This program is not a free software.
*
* @section DESCRIPTION
* USAGE: See API
* Process: N/A
* Output: N/A
*/

#ifndef THREADUTILS_H
#define	THREADUTILS_H


/**
 * An enum that saves an error code, it is used throughout the scheduler class
 * to indicate whether an operation succeeded or not
 */
enum ERRCODE
{
    OK = 0,
    FAIL = -1,           
};


/**
 * An enum that states the different states that a thread can have
 */
enum State
{
    Running = 0,
    Ready = 1,
    Suspended = 2,
};

/*
#define EMPTYSET_ERROR "Error creating empty signal set";
#define ADDSET_ERROR "Error adding a signal to a set";
#define ACTION_ERROR "Error creating action for a signal";
#define SETTIMER_ERROR "Error setting virtual timer";
#define WAIT_ERROR "Error waiting for signal using sigwait";
#define PENDING_ERROR "Error retrieving pending signals";
#define PROC_ERROR "Error changing the signal mask";
#define ISMEMBER_ERROR "Error checking signal is a member of set";
#define THREADLIB_ERROR "thread library error:";
#define SUS_MAIN_ERROR "cannot suspend main thread";
#define USECS_ERROR "non-positive quantum usecs";
#define NO_THREAD_ERROR "no such thread";
#define MAX_THREADS_ERROR "maximum threads";
*/

const std::string EMPTYSET_ERROR = "Error creating empty signal set";
const std::string ADDSET_ERROR = "Error adding a signal to a set";
const std::string ACTION_ERROR = "Error creating action for a signal";
const std::string SETTIMER_ERROR = "Error setting virtual timer";
const std::string WAIT_ERROR = "Error waiting for signal using sigwait";
const std::string PENDING_ERROR = "Error retrieving pending signals";
const std::string PROC_ERROR = "Error changing the signal mask";
const std::string ISMEMBER_ERROR = "Error checking signal is a member of set";
const std::string THREADLIB_ERROR = "thread library error:";
const std::string SUS_MAIN_ERROR = "cannot suspend main thread";
const std::string USECS_ERROR =  "non-positive quantum usecs";
const std::string NO_THREAD_ERROR = "no such thread";
const std::string MAX_THREADS_ERROR = "maximum threads";

//Default Main thread ID
#define MAIN_THREAD_ID 0

#endif	/* THREADUTILS_H */
