/* 
 * File:   main.cpp
 * Author: okeren
 *
 * Created on April 5, 2015, 7:38 AM
 */

#include <cstdlib>
#include <iostream>
#include "uthreads.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    cout << "test";
    cout << "blat";
    uthread_init(2000000);
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

