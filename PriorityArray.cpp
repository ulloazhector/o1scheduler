#include "PriorityArray.h"

#include <iostream>
#include <queue>



const int ARRAY_LENGHT = 14;

using namespace std;

void PriorityArray::showQueue(int entrie){
    queue<Task> copy = this->array[entrie];
    while (!copy.empty() ){
        copy.front().showTask();
        copy.pop();
    }
}

void PriorityArray::pushTask(Task task){
    this->array[task.getStaticPriority()].push(task);
}

Task PriorityArray::popTask(int prior){
    Task popedTask = this->array[prior].front();
    this->array[prior].pop();
    return popedTask;
}

void PriorityArray::showArray(){
    for(int i = 0; i < ARRAY_LENGHT; i++){
        cout << "[" << i << "]: ";
        this->showQueue(i);
        cout << endl;
    }
    cout << endl;
}

queue<Task> PriorityArray::getQueue(int prior){
    return this->array[prior];
}

