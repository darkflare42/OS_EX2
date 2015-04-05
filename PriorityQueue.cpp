/* 
 * File:   PriorityQueue.cpp
 * Author: odedex
 * 
 * Created on April 4, 2015, 11:31 AM
 */

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {
}

PriorityQueue::PriorityQueue(const PriorityQueue& orig) {
}

PriorityQueue::~PriorityQueue() {
}

void PriorityQueue::Enqueue(Thread thread) {
    switch(thread.getPriority()) {
        case RED: redQ.push(thread);
        break;
        case ORANGE: orangeQ.push(thread);
        break;
        case GREEN: greenQ.push(thread);
        break;
    }
}

Thread PriorityQueue::Dequeue(){
    Thread temp;
    if (redQ.size() > 0) {
        temp = redQ.front();
        redQ.pop();
    }
    else if (orangeQ.size() > 0) {
        temp = orangeQ.front();
        orangeQ.pop();
    }
    else if (greenQ.size() > 0) {
        temp = greenQ.front();
        greenQ.pop();
    }
    return temp;
}
