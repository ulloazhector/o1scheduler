//#include "Task.h"
#include "PriorityArray.h"

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