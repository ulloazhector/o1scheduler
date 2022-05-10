#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

const int ARRAY_LENGHT = 14;     // 40
const int MIN_PRIOR = 10;      // 100
const int MAX_PRIOR = 14;      // 140
const int BASE = 0;           // 120
const int INTERVAL_MS = 100;    // 100

// helpers

int baseTimeSliceCalc(int SP){
    return SP < BASE ? (MAX_PRIOR - SP)*20 : (MAX_PRIOR - SP)*5;
}

//int bonusCalc(int avgSleepTime){
//    return avgSleepTime < 1000 ? avgSleepTime / INTERVAL_MS - 5 : 5;
//}

//int dynamicPriorityCalc(int SP, int avgST){
//    return max(
//        MIN_PRIOR, 
//        min(SP - bonusCalc(avgST), MAX_PRIOR - 1)
//        );
//}



/* * * * * * * * * * TASK * * * * * * * * * */

class Task {
    private:
        string id;
        string status;
        int staticPriority;
        int dynamicPriority;
        int baseTS;
        int timeLeft;
    public:
        Task(string id, string status, int staticPriority, int requiredTime);
        string getTaskStatus();
        void setTaskStatus(string status);
        int getStaticPriority();
        void updateTimeLeft();
        void showTask();
};

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




/* * * * * * * * * * PRIORITY_ARRAY * * * * * * * * * */

class PriorityArray {
    private:
        queue<Task> array[ARRAY_LENGHT];
    public:
        void showQueue(int entrie);
        void pushTask(Task task);
        Task popTask(int prior);
        void showArray();
        queue<Task> getQueue(int prior);
};

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




/* * * * * * * * * * RUNQUEUE * * * * * * * * * */

class Runqueue {
    private:
        PriorityArray act, exp;
        PriorityArray * active;
        PriorityArray * expired;
    public:
        Runqueue();
        void addTask(Task task);
        void swapPointers();
        void showArrays();
        void expireTask(Task task);
        void schedule();

};

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
    cout << "---------------------------------------------" << endl;
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










/* * * * * * * * * * MAIN * * * * * * * * * */

int main() {
    //          id      status      priority   time-req
    Task    t1("p1",    "active",   0,          100), 
            t2("p2",    "active",   0,          200), 
            t3("p3",    "active",   13,         200), 
            t4("p4",    "active",   10,         200);

    Runqueue rq;

    rq.addTask(t1);
    rq.addTask(t2);
    rq.addTask(t3);
    rq.addTask(t4);

    rq.showArrays();

    rq.schedule();
    rq.showArrays();

    rq.swapPointers();
    rq.showArrays();

    rq.schedule();
    rq.showArrays();



    cout << endl;
    return 0;
}
