#include <iostream>
#include <string>
#include <memory>
using namespace std;

// 饿汉模式 程序加载前创建

class TaskQueue
{
public:
    TaskQueue(const TaskQueue &) = delete;
    TaskQueue &operator=(const TaskQueue &) = delete;
    ~TaskQueue() {
        cout << __PRETTY_FUNCTION__ << "\n";
    }
    static unique_ptr<TaskQueue>& getInstance() {
        return p_;
    }
    string className() const {
        return "TaskQueue";
    }

private:
    TaskQueue() {
        cout << __PRETTY_FUNCTION__ << "\n";
    }
    static unique_ptr<TaskQueue> p_;
};
unique_ptr<TaskQueue> TaskQueue::p_{new TaskQueue};

int main(int argc, char* argv[])
{
 
    cout << TaskQueue::getInstance()->className() << "\n";

    return 0;
}