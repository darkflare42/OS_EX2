/* 
 * File:   ThreadUtils.h
 * Author: odedex
 *
 * Created on April 4, 2015, 11:20 AM
 */

#ifndef THREADUTILS_H
#define	THREADUTILS_H

enum Priority
{
    // Lower number equivalent to a higher priority.
    RED = 0,
    ORANGE = 1,
    GREEN = 2,
    NOPRIORITY = 100, // default priority.
};


#endif	/* THREADUTILS_H */
