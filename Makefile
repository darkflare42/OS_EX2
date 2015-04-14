all: libuthreads.a

libuthreads.a: ThreadUtils.h PriorityQueue.o Thread.o Scheduler.o uthreads.o
	ar rcs libuthreads.a ThreadUtils.h PriorityQueue.o Thread.o Scheduler.o uthreads.o

PriorityQueue.o: PriorityQueue.h PriorityQueue.cpp Thread.h ThreadUtils.h
	g++ -Wall -Wextra -Wvla -std=c++11 -c PriorityQueue.cpp

Thread.o: Thread.h Thread.cpp ThreadUtils.h uthreads.h
	g++ -Wall -Wextra -Wvla -std=c++11 -c Thread.cpp 

Scheduler.o: Scheduler.h Scheduler.cpp Thread.h ThreadUtils.h PriorityQueue.h
	g++ -Wall -Wextra -Wvla -std=c++11 -c Scheduler.cpp

uthreads.o: uthreads.h uthreads.cpp ThreadUtils.h Scheduler.h
	g++ -Wall -Wextra -Wvla -std=c++11 -c uthreads.cpp 

tar:
	tar -cvf ex2.tar PriorityQueue.h PriorityQueue.cpp Scheduler.h Scheduler.cpp Thread.h Thread.cpp ThreadUtils.h uthreads.h uthreads.cpp README Makefile

clean:
	rm -f PriorityQueue.o Thread.o Scheduler.o uthreads.o libuthreads.o libuthreads.a

.PHONY: clean tar
