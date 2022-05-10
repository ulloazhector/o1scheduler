
#include "Task.h"
#include <queue>

const int ARRAY_LENGHT = 14;     // 40

using namespace std;

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