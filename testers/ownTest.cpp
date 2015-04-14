/*
 * test4.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: roigreenberg
 */

#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <deque>
#include <list>
#include <assert.h>
#include "uthreads.h"
//#include "libuthread.a"
#include <iostream>

using namespace std;

void f (void)
{
	int i = 0;
	while(true)
	{
		cout << "f " << ++i << endl;
	}
}

void g (void)
{
	int i = 0;
	while(true)
	{
		cout << "g " << ++i << endl;
	}
}

void h (void)
{
	int i = 0;
	while(true)
	{
		cout << "h " << ++i << endl;
	}
}

int main(void)
{
	if (uthread_init(100) == -1)
	{
		return 0;
	}

	uthread_spawn(f,ORANGE);
	uthread_spawn(g,ORANGE);

	for (int i = 0 ; i < 100 ; i++)
	{
		cout << "main " << i << endl;
	}
	uthread_terminate(0);
}

