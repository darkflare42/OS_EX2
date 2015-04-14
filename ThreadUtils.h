/* 
 * File:   ThreadUtils.h
 * Author: odedex
 *
 * Created on April 4, 2015, 11:20 AM
 */

#ifndef THREADUTILS_H
#define	THREADUTILS_H



enum ERRCODE
{
    OK = 0,
    FAIL = -1,           
};

enum State
{
    Running = 0,
    Ready = 1,
    Suspended = 2,
};

const std::string EMPTYSET_ERROR = "Error creating empty signal set";
const std::string ADDSET_ERROR = "Error adding a signal to a set";
const std::string ACTION_ERROR = "Error creating action for a signal";
const std::string SETTIMER_ERROR = "Error setting virtual timer";
const std::string WAIT_ERROR = "Error waiting for signal using sigwait";
const std::string PENDING_ERROR = "Error retrieving pending signals";
const std::string PROC_ERROR = "Error changing the signal mask";
const std::string ISMEMBER_ERROR = "Error checking signal is a member of set";


#define MAIN_THREAD_ID 0

#endif	/* THREADUTILS_H */
