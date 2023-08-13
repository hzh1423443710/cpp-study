#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <cstring>

class MM
{
public:
    MM(int size, int init = 0)
        : size_(size), arr_(std::make_unique<int[]>(size_))
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        for (int i = 0; i < size_; ++i) {
            arr_[i] = init;
        }
    }
    MM(const MM & other)
        : size_(other.size_), arr_(std::make_unique<int[]>(size_))
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        memcpy(arr_.get(), other.arr_.get(), sizeof(int)*size_);
    }
    MM(MM && other)
        : size_(other.size_), arr_(std::move(other.arr_))
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        other.size_ = 0;
    }
    ~MM()
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }
public:
    std::size_t size_;
    std::unique_ptr<int[]> arr_;
};

// Prefect Forwarding
template<class T, class... Args>
auto factory(Args&&... args)
{
    return T(std::forward<Args>(args)...);
}
// Non-Prefect Forwarding
template<class T, class... Args>
auto factory2(Args&&... args)
{
    return T(args...);
}

int main(int argc, char *argv[])
{
    MM m(5,1);
    std::cout << m.arr_.get() << "\n";

	MM m2 = factory<MM>(std::move(m)); // move
//	MM m2 = factory2<MM>(std::move(m)); // no-move
    std::cout << m.arr_.get() << "\n";
    std::cout << m2.arr_.get() << "\n";

    return 0;
}
