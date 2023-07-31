#include <iostream>
#include <type_traits>
#include <tuple>

// 变参模板继承

template<class... ArgT>
struct MM
{
    MM() {}
    void print() const {}
    void assignment() {}
    using type = void;
};

template<class T, class... ArgT>
struct MM<T,ArgT...> : private MM<ArgT...>
{
    using type = T;
    MM(T t, ArgT... args) : MM<ArgT...>(args...), t(t), argn(sizeof...(ArgT)) {

    }
    void assignment(T t, ArgT... args) {
        MM<T,ArgT...>::t = t;
        MM<ArgT...>::assignment(args...);
    }
    void print() const
    {
        std::cout << MM<T,ArgT...>::t << " ";
        MM<ArgT...>::print();
    }
    T t;
    size_t size() const {
        return argn + 1;
    }
    T get() const {
        return t;
    }
private:
    int argn;
};

int main(int argc, char *argv[])
{
    MM<int,float,const char*> m(1,2.1f, "Hello");
    m.print();
    m.assignment(20, 88.88f, "hzh");
    std::cout << "\n";
    m.print();

    return 0;
}
