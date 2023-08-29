#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <atomic>
using namespace std;

// 懒汉模式- 多线程
// -- 1. mutex+atomic
#if 1
class TaskQueue
{
public:
    TaskQueue(const TaskQueue& ) = delete;
    TaskQueue& operator=(const TaskQueue& ) = delete;
    ~TaskQueue() {
        cout << __PRETTY_FUNCTION__ << "\n";
    }
    /*
    static unique_ptr<TaskQueue>& getInstance() {
        if (p_ == nullptr) { // 双重检查
            lock_guard<mutex> lock(mtx_);
            if (p_ == nullptr) 
                p_.reset(new TaskQueue);
            // new TaskQueue 不是原子操作 AND 机器指令可能会被重新排序 (可能先开辟栈指针,再申请堆空间赋值给栈指针)
            // 如果 先开辟栈指针,还未申请堆空间, 此时再来一个线程p_不为nullptr !!!
        }
        return p_;
    }
    */
    static TaskQueue* getInstance() {
        TaskQueue* queue = p_.load(); // 防止指令重排
        if (queue == nullptr) {
            lock_guard<mutex> lock(mtx_); // 创建时同步
            queue = p_.load();
            if (queue == nullptr) 
                p_.store(new TaskQueue);
        }
        return queue;
    }

    string className() const {
        return "TaskQueue";
    }

private:
    TaskQueue() {
        cout << __PRETTY_FUNCTION__ << "\n";
    }
    static atomic<TaskQueue*> p_;
    static mutex mtx_;
};
atomic<TaskQueue*> TaskQueue::p_;
mutex TaskQueue::mtx_;

#else

// 2. 局部静态变量
class TaskQueue
{
public:
    TaskQueue(const TaskQueue &) = delete;
    TaskQueue &operator=(const TaskQueue &) = delete;
    ~TaskQueue() {
        cout << __PRETTY_FUNCTION__ << "\n";
    }
    static TaskQueue* getInstance() {
        static TaskQueue queue;
        return &queue;
    }
    string className() const {
        return "TaskQueue";
    }

private:
    TaskQueue() {
        cout << __PRETTY_FUNCTION__ << "\n";
    }
};

#endif


void work()
{
    cout << this_thread::get_id() << " " << TaskQueue::getInstance()->className() << "\n";
}

int main(int argc, char* argv[])
{
    cout << "Program Starting\n";
    thread ts[10];
    for (auto& x : ts)
        x = thread(work);

    cout << "-- " << TaskQueue::getInstance()->className() << "\n";
    
    for (auto& x : ts)
        x.join();
    return 0;
}