#include <iostream>
#include <string>
#include <memory>
using namespace std;

// 懒汉模式
class TaskQueue
{
public:
    TaskQueue(const TaskQueue &) = delete;
    TaskQueue &operator=(const TaskQueue &) = delete;
    ~TaskQueue() {
        cout << __PRETTY_FUNCTION__ << "\n";
    }
    static unique_ptr<TaskQueue>& getInstance() {
        if (p_)
            return p_;
        p_.reset(new TaskQueue);
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
unique_ptr<TaskQueue> TaskQueue::p_;

int main(int argc, char* argv[])
{
    cout << "Program Starting\n";
    cout << TaskQueue::getInstance()->className() << "\n";
    
    return 0;
}