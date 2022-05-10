#include "Task.h"

#include <iostream>
#include <algorithm>


const int MIN_PRIOR = 10;      // 100
const int MAX_PRIOR = 14;      // 140
const int BASE = 0;           // 120
const int INTERVAL_MS = 100;    // 100


int baseTimeSliceCalc(int SP){
    return SP < BASE ? (MAX_PRIOR - SP)*20 : (MAX_PRIOR - SP)*5;
}




Task::Task(string id, string status, int staticPriority, int timeLeft){
    this->id = id;
    this->status = status;
    this->staticPriority = staticPriority;
    this->baseTS = baseTimeSliceCalc(this->staticPriority);
    this->timeLeft = timeLeft;
}

string Task::getTaskStatus(){
    return this->status;
}

void Task::setTaskStatus(string status){
    this->status = status;
}

int Task::getStaticPriority(){
    return this->staticPriority;
}

void Task::showTask(){
    cout << 
        "{ id=" << this->id << 
        " ts=" << this->baseTS <<
        " tl=" << this->timeLeft << " } ";
}

void Task::updateTimeLeft(){
    this->timeLeft -= this->baseTS;
    if(this->timeLeft < 0)
        this->timeLeft = 0;
}
