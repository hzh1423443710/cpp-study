#include <iostream>
#include <atomic>

int main(int argc, char* argv[])
{
    // std::atomic<int> x(100);
    std::atomic_int x(100);
    int a = 100;
    if (x.compare_exchange_strong(a, 30)) {
        std::cout << "equal, x = " << x << "\n";
    }
    else {
        std::cout << "not equal, a = " << a << "\n";
    }
    time_t t = time(nullptr);
    std::cout << t << "\n";
    
    
    return 0;
}