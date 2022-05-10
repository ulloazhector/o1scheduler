#include "Runqueue.h"
#include <iostream>

using namespace std;

Runqueue::Runqueue(){
    this->active = &this->act;
    this->expired = &this->exp;
}

void Runqueue::addTask(Task task){
    if(task.getTaskStatus() == "active")
        this->active->pushTask(task);
}

void Runqueue::swapPointers(){
    PriorityArray * aux;
    aux = this->active;
    this->active = this->expired;
    this->expired = aux;
}

void Runqueue::showArrays(){
    cout << "Active processes" << endl;
    this->active->showArray();
    cout << "Expired processes" << endl; 
    this->expired->showArray();
}

void Runqueue::expireTask(Task task){
    Task updatedTask = this->active->popTask(task.getStaticPriority());
    updatedTask.setTaskStatus("expired");
    updatedTask.updateTimeLeft();
    this->expired->pushTask(updatedTask);    
}

void Runqueue::schedule(){
    for(int i = 0; i < ARRAY_LENGHT; i++){
        queue<Task> q = this->active->getQueue(i);
        while(! q.empty()){
            Task t = q.front();
            q.pop();
            expireTask(t);
        }
    }
}