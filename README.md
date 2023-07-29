# 杂项Sundry

## 原始字面量

```c++
const char* str = R"(Hello \n\0 World!)";
const char* str = R"delimiter(Hello \n\0 World!)delimiter"; // 前后delimiter必须一致
```



## 左值右值

一块存储内存, 可以解释为不同的值类别,类型. 

`int&`: int关键字代表4字节的内存被解释为int类型, &限定符代表可以引用这块内存,一个&代表左值引用

`int&&`: int关键字代表4字节的内存被解释为int类型, &限定符代表可以引用这块内存, 两个&代表右值引用

右值引用的出现多出了一种类型, 通过函数传参与`T&`区别开, 如移动语义高效管理资源, 完美转发不丢失值类别传递参数



- 左值: 可以出现在等号左边(可以寻址)
- 右值: 只能出现在等号右边

**左值右值说的是值类别, 和值类型无关, 所以:**

- 有名变量都是左值, 字面量,常量表达式,临时变量...都为右值
- 字符串字面量是左值

**Example:**

```c++
int a = 1; 					// a是左值 1是右值
int b = a+a; 				// b是左值 a是左值 (a+a)是右值
((char*)"Hello")[0] = '1';   // 字符串字面量是左值
```

 

## 引用限定符

```c++
struct Arg
{
int i = 1;
int  get() && { 
	std::cout << "right value\n";
    return i; 
} // 此重载的调用为右值
int& get() &  {
	std::cout << "left value\n";
    return i; 
} // 此重载的调用为左值
};

Arg arg; 
arg.get();  // 调用左值版本     
Arg{}.get(); // 调用右值版本
```



## 引用折叠

右值引用的右值引用折叠成右值引用，所有其他组合均折叠成左值引用：

```c++
using lref = int&;
using rref = int&&;
std::cout << std::is_same_v<lref& , int&> << "\n";	// true
std::cout << std::is_same_v<lref&&, int&> << "\n";  // true
std::cout << std::is_same_v<rref& , int&> << "\n";  // true
std::cout << std::is_same_v<rref&&, int&&> << "\n"; // true
```



## std::move

修改值类别为右值

```c++
static_cast<std::remove_reference_t<T>&&>()
```

## std::forward

等价于, 强转+引用折叠

```c++
static_cast<T&&>();
```

```c++
int b = 10;
int&& rrb = std::forward<int>(b); // 将b转发为右值
rrb = std::forward<int&&>(b);// 将b转发为右值
int& rb = std::forward<int&>(b);  // 将b转发为左值
```



## 万能引用

**万能:** 左值右值都可以接收

1. 当传递一个左值时，将`template<class T>`中的T推导为左值引用
2. 当传递一个右值时，将`template<class T>`中的T推导为非引用类型

**前提:**一定在函数模板, 一定发生类型推导(手动显式实例化不算万能引用)



**万能引用的推导:** 也可以通过cppinsight网站查看

```c++
template<class T>	  // 1.万能引用根据实参对T推导
void wrapper(T&& t) { // 2.形参t始终是左值[推导完后引用折叠]
    if (std::is_same_v<T, int>)
        puts("T -> int");
    if (std::is_same_v<T, int&>)
        puts("T -> int&");

    if (std::is_same_v<decltype(t), int&>)
        puts("void wrapper(int& t)");
    if (std::is_same_v<decltype(t), int&&>)
        puts("void wrapper(int&& t)");
}

int a = 10;
wrapper(1);
// T -> int
// void wrapper(int&& t)
wrapper(a); 
// T -> int&
// void wrapper(int& t)
```

**Example:** 万能引用+引用折叠+forward实现**完美转发**, 将左值形转为实参的值类别

**完美转发:** 不改动值类别转发参数(函数形参都为左值). 而是根据根据实参的值类别实现静态多态

```c++
template<class T>
void fun(T&) {
    std::cout << "Actual Parameter is L value\n";
}
template<class T>
void fun(T&&) {
    std::cout << "Actual Parameter is R value\n";
}
template<class T>
void wrapper(T&& t) { 
	fun(std::forward<T>(t)); // 转发为左值或右值[wrapper的实参类型T]
}

int main() {
    int a = 10;
    // 万能引用
    wrapper(10);
    wrapper(a);
    // 非万能引用(显式实例化模板)
    wrapper<int>(10); // 右值引用
    wrapper<int>(a);  // 报错, 右值引用无法接受左值
    wrapper<int>(std::move(a)); // √
    // 完美转发
    wrapper(1); // 实参为右值, 调用fun(int&&)
    wrapper(a);	// 实参为左值, 调用fun(int&)
}
```
