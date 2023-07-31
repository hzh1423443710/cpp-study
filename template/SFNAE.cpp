#include <iostream>
#include <type_traits>
#include <array>
#include <functional>
#include <numeric>

template<class T>
struct Square
{
    using result_type = T;
    T operator()(T& it)
    {
        return it *= 2;
    }
};

// 多个 T 类型参数累加
// 因为该模板会优先匹配lambda 用std::enable_if禁用匹配lambda的模板实例
template<class T,class... ArgT>
auto accumulate(ArgT... args) -> std::enable_if_t<std::conjunction_v< std::is_same<T,ArgT>... >,T>
{
   return (... + args);
}
// 接受lambda
template<class T, class... ArgT>
T accumulate(std::function<T(T&)> pfun, ArgT... args)
{
    std::array<T, sizeof...(ArgT)> arr = {args...};
    T sum{};
    for (auto& v : arr)
        sum += pfun(v);

    return sum;
}
// 接收一元仿函数(拥有result_type类型别名)
template<class Pre, class... ArgT>
auto accumulate(Pre pre, ArgT... args) -> typename Pre::result_type
{
    using type = typename Pre::result_type;
    using value_type = std::enable_if_t<std::conjunction_v< std::is_convertible<ArgT, type>...>, type>;

    std::array<value_type, sizeof...(args)> arr = {args...};
    type sum{};
    for (auto& it : arr)
        sum += pre(it);

    return sum;
}

int main()
{
    std::cout << accumulate(Square<int>{},1,2,3,4,5) << "\n";
    std::cout << accumulate(std::negate<int>{},1,2,3,4,5) << "\n";
    std::cout << accumulate<int>([](int& it){ return it = (it % 2 == 0)?it:0;}, 1,2,3,4,5) << "\n";

    return 0;
}