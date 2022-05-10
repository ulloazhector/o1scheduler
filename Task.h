
#include <string>

using namespace std;

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