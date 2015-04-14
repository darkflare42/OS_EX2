/* 
 * File:   main.cpp
 * Author: okeren
 *
 * Created on April 5, 2015, 7:38 AM
 */
/*
#include <cstdlib>
#include <iostream>
//#include "uthreads.h"

using namespace std;


 
 
int main(int argc, char** argv) {

    cout << "test";
    cout << "blat";
    //uthread_init(20000);
    //uthread_spawn(NULL, RED);
    //uthread_spawn(NULL, GREEN);
    //uthread_spawn(NULL, ORANGE);
    //uthread_suspend(1);
    //uthread_resume(1);
    //after cloning, let's see if it gets updated!
    //testas
    //test2
    return 0;
}
/*
/*
 * test1.cpp
 *
 *	test suspends and resume
 *
 *  Created on: Apr 6, 2015
 *      Author: roigreenberg
 */

/*
 * test4.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: roigreenberg
 */

/*
 * test1.cpp
 *
 *	test suspends and resume
 *
 *  Created on: Apr 6, 2015
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
	while(1)
	{
//		cout << "f" << endl;
		uthread_suspend(1);
	}
}

void g (void)
{
	while(1)
	{
//		cout << "g" << endl;
		uthread_suspend(2);
	}
}

void h (void)
{
	while(1)
	{
//		cout << "h" << endl;
		uthread_suspend(3);
	}
}

int main(void)
{
	if (uthread_init(100) == -1)
	{
		return 0;
	}

	uthread_spawn(f,RED);
	uthread_spawn(g,RED);
	uthread_spawn(h,RED);

	while(uthread_get_total_quantums() < 10)
	{
		uthread_resume(1);
		uthread_resume(2);
		uthread_resume(3);
	}

	cout << uthread_get_quantums(0) << " + " << endl;
	cout << uthread_get_quantums(1) << " + " << endl;
	cout << uthread_get_quantums(2) << " + " << endl;
	cout << uthread_get_quantums(3) << endl;
	cout << " = " << uthread_get_total_quantums() << endl;

	uthread_suspend(2);

	while(uthread_get_total_quantums() < 20)
		{
			uthread_resume(1);
			uthread_resume(3);
		}

	cout << uthread_get_quantums(0) << " + " << endl;
	cout << uthread_get_quantums(1) << " + " << endl;
	cout << uthread_get_quantums(2) << " + " << endl;
	cout << uthread_get_quantums(3) << endl;
	cout << " = " << uthread_get_total_quantums() << endl;

	uthread_resume(2);

	while(uthread_get_total_quantums() < 30)
	{
		uthread_resume(1);
		uthread_resume(2);
		uthread_resume(3);
	}

	cout << uthread_get_quantums(0) << " + " << endl;
	cout << uthread_get_quantums(1) << " + " << endl;
	cout << uthread_get_quantums(2) << " + " << endl;
	cout << uthread_get_quantums(3) << endl;
	cout << " = " << uthread_get_total_quantums() << endl;


	uthread_terminate(0);
	return 0;
}




