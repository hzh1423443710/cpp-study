#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
using namespace std;

class TaskQueue
{
public:
    TaskQueue(const TaskQueue &) = delete;
    TaskQueue &operator=(const TaskQueue &) = delete;
    static TaskQueue* getInstance() {
        return &task_;
    }

    void addTask(int task) {
        lock_guard<mutex> lock(mtx_);
        queue_.push(task);
    }

    bool isEmpty() {
        lock_guard<mutex> lock(mtx_);
        return queue_.empty();
    }

    bool popTask() {
        lock_guard<mutex> lock(mtx_);
        if (queue_.empty())
            return false;
        queue_.pop();
        return true;
    }

    int takeTask() {
        lock_guard<mutex> lock(mtx_);
        return queue_.front();
    }

private:
    TaskQueue() = default;
    static TaskQueue task_;
    queue<int> queue_;
    mutex mtx_;
};
TaskQueue TaskQueue::task_;

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    thread producer, consumer;

    producer = thread([](){
        for (int i = 0; i < 100; ++i) {
            int task = 100 + i;
            TaskQueue::getInstance()->addTask(task);
            cout << "add task [" << task << "] - " << this_thread::get_id() << "\n";
            this_thread::sleep_for(chrono::milliseconds{ 20 + rand() % 30 });
        }
    });

    consumer = thread([](){
        TaskQueue* pIns = TaskQueue::getInstance();
        while (!pIns->isEmpty()) {
            int task = pIns->takeTask();
            pIns->popTask();
            cout << "\t\t\tpop task [" << task << "] - " << this_thread::get_id() << "\n";
            this_thread::sleep_for(chrono::milliseconds{ 50 + rand() % 30 });
        }
    });

    producer.join();
    consumer.join();
    return 0;
}