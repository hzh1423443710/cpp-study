# numeric

数值库

## iota

从**起始值递增**填充一个范围**[first, last)**

复杂度:正好 `last - first` 次自增与赋值。

```c++
template<class ForwardIterator, class T>
constexpr // C++20 起
void iota(ForwardIterator first, ForwardIterator last, T value)
{
    while(first != last) {
        *first++ = value;
        ++value;
    }
}
```

**Example:**

```c++
std::vector<int> arr(10);   
std::iota(arr.begin(), arr.end(), -5);
for (auto& v : arr) 
    std::cout << v << " ";
// -5 -4 -3 -2 -1 0 1 2 3 4 
```



## accumulate

区间累加求和**[版本1]**

```c++
// 版本1 
template< class InputIt, class T >
T accumulate( InputIt first, InputIt last, T init ); // 求和
// 版本2
template< class InputIt, class T, class BinaryOperation >
T accumulate( InputIt first, InputIt last, T init, BinaryOperation op ); // 二元函数对象
// 版本1 <==>
accumulate(first, last, init, plus<>{});
```

Example:

```c++
std::vector<int> arr(5);   
std::iota(arr.begin(), arr.end(), 1);
auto dash_fold = [](std::string l, int r) {
    return std::move(l) + "-" + std::to_string(r);
};

std::string str = std::accumulate(std::next(arr.begin()), arr.end(), std::to_string(arr[0]), dash_fold);
std::cout << str << "\n"; // 1-2-3-4-5

str = std::accumulate(std::next(arr.rbegin()), arr.rend(), std::to_string(arr.back()), dash_fold);
std::cout << str << "\n"; // 5-4-3-2-1
```



## reduce(C++17)

**[C++17]**类似`std::accumulate`, 可指定执行策略, 如并行`std::execution::par` 

## transform_reduce(C++17)

先通过一个函数对象变化, 再reduce



## inner_product

2个区间求内积**[版本1]**

```c++
// 版本1 - 内积
template< class InputIt1, class InputIt2, class T >
constexpr T inner_product( InputIt1 first1, InputIt1 last1, // 区间1
                           InputIt2 first2, // 区间2
                           T init ); // 初值
// 版本2
template< class InputIt1, class InputIt2, class T, class _BinOp1, class _BinOp2 >
constexpr T inner_product( InputIt1 first1, InputIt1 last1,  // 区间1
                           InputIt2 first2, T init,			// 区间2
                           _BinOp1 op1,  				   // 归纳方式
                           _BinOp2 _Transform_op );			// 变换方式
// 版本1 <==> 相乘(变换) 再 相加(归纳)
inner_product(first1, last1, first2, init, plus<>{}, multiplies<>{});    
```

Example:

```c++
std::vector<int> arr(3);   // 1 2 3 
std::iota(arr.begin(), arr.end(), 1);
std::vector<int> arr2(arr);// 1 2 3

int ret = std::inner_product(arr.begin(), arr.end(), arr2.begin(), 0, 
                             std::plus<>{}, std::multiplies<>{});
std::cout << ret << '\n'; // 14
```



## adjacent_difference

相邻两项之差(后者与前者之差), 写入到输出迭代器**[版本1]**

```c++
// 版本1
template< class InputIt, class OutputIt >
constexpr OutputIt adjacent_difference( InputIt first, InputIt last, OutputIt d_first );
// 版本2
template< class InputIt, class OutputIt, class BinaryOperation >
OutputIt adjacent_difference( InputIt first, InputIt last, OutputIt d_first, BinaryOperation op );
// 版本1 <==>
adjacent_difference(first, last, d_fist, minus<>{});
```

Example:

```c++
std::vector<int> arr{1,2,4,7,0};
std::adjacent_difference(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, " "});
// (1-0) (2-1) (4-2) (7-4) (0-7)
// 1 1 2 3 -7 
```





## partial_sum

计算范围内元素的部分和, 输出每个部分的和到输出迭代器**[版本1]**

```c++
// 版本1
template< class InputIt, class OutputIt >
constexpr OutputIt partial_sum( InputIt first, InputIt last, OutputIt d_first );
// 版本2
template< class InputIt, class OutputIt, class BinaryOperation >
constexpr OutputIt partial_sum( InputIt first, InputIt last, OutputIt d_first, BinaryOperation op );
// 版本1 <==>
partial_sum(first, last, d_first, plus<>{});
```

Example:

```c++
std::vector<int> arr{1,2,3,4,5};
std::partial_sum(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, " "}, std::plus<>{});
// (1) (1+2) (1+2+3) (1+2+3+4) (1+2+3+4+5)
//  1    3      6       10          15 
```



## inclusive_scan

同partial_sum, 第 i 个和中**包含**第 i 个输入 (输出的第N个元素是N个元素的和)

## exclusive_scan

同partial_sum, 第 i 个和中**排除**第 i 个输入 (输出的第N个元素是N-1个元素的和)

```c++
// 等价于
std::inclusive_scan(__first, __last, __result, plus<>());
std::exclusive_scan(__first, __last, __result, 0, plus<>());
```

Example:

```c++
std::vector<int> arr{1,2,3,4,5};
std::inclusive_scan(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, " "});
// 1 3 6 10 15 包含最后一个元素 
std::exclusive_scan(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, " "}, 0);
// (0) (0+1) (0+1+2) (0+1+2+3) (0+1+2+3+4)
//  0    1      3        6          10  不包含最后一个元素
```



## transform_inclusive_scan(C++17)

## transform_exclusive_scan(C++17)

**[C++17]**先通过一个函数对象**变换**再扫描

```c++
std::vector<int> arr{1,2,3,4,5};
std::transform_inclusive_scan(arr.begin(), arr.end(),
                              std::ostream_iterator<int>{std::cout, " "}, std::plus<>{},
                              [](int x) {
                                  return x*10;
                              });
// 10 30 60 100 150 
```



## gcd(C++17) 

## lcm(C++17) 

gcd: 返回二个**整数最大公约数**的 `constexpr` 函数模板 (Greatest Common divisor)

lcm: 返回二个**整数最小公倍数**的 `constexpr` 函数模板 (Lowest Common Multiple)



