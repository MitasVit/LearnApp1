#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

class Timer{
public:

    clock_t start, end;
    void Start(){
        start = clock();
    }

    void End(){
        end = clock();
    }
    double GetTime2(){
        return (((double) end - start));
    }
    double GetTime(){
        return ((((double) clock() - start) / CLOCKS_PER_SEC)* 10.00);
    }
};

#endif