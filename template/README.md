# 泛型编程

## Lambda

lambda+auto 等于 模板lambda

lambda 作为函数参数: 通常用[&]存储引用, 用`template<class Func>`然后`const Func&` 做类型

lambda 作为返回值: 总是用[=]存储值, 用auto返回



## 模板

### 分类

**分类1:**

- 函数模板
- 类模板
- 成员函数模板

**分类2:**

- 带有缺省参数的模板

**分类3:**

- 非类型模板参数(**传值**)

```c++
template<int N1, int N2 = 10> 
```

- 类型模板参数(**传类型**)

```c++
template<class T, class T2 = int>
```

- 非类型模板参数 + 类型模板参数(**组合**)

```c++
template<class T, int N>
```

**其他:**

- 类型参数引用

```c++
template<class T1, class T2 = T1*> // T2引用T1
```



显示实例化声明

```c++
template void swap<int>(int &a,int &b); 
```



### 特化

函数模板(包括成员函数)**只有全特化**,没有局部特化.

类模板既有**全特化**也有**局部特化**.

**分类:**

- 全特化:`template<>`
- 局部特化
  - 特化参数个数, 类型参数只能往小的特化, 非类型参数可多可少
  - 特化参数修饰, 如`[], const, *, &`

**Example_1:** 类模板(全特化 + 特化参数修饰)

```c++
// 原始模板
template <class _Ty>
struct RemoveConstAndPtr { 
    using type = _Ty;
};
// 特化参数修饰
template <class _Ty>
struct RemoveConstAndPtr<const _Ty*> {
    using type = _Ty;
};
// 全特化
template<>
struct RemoveConstAndPtr<double> {
    void print() {
        std::cout << "This is Full Specialization\n";
    }
};
```

**Example_2:** 类模板(全特化 + 特化参数个数)

```c++
struct Policeman{}; // 警察
struct PoliceDog{}; // 警犬
struct GuideGog{};  // 导盲犬

// 原始模板
template<class Person_t, class Dog_t = void>
struct Subway {
    void print() {
        std::cout << "Primitive Template\n";
    }
};
// 局部特化(特化参数个数)
template<class Person_t>
struct Subway<Person_t,GuideGog> {
    void print() {
        std::cout << "Partial Specialization, GuideGog\n";
    }
};
// 全特化
template<>
struct Subway<Policeman,PoliceDog> {
    void print() {
        std::cout << "Full Specialization, Policeman + PoliceDog\n";
    }
};

Subway<Policeman> a; 
a.print(); // 缺省原始模板
Subway<Policeman,PoliceDog> policeman;
policeman.print(); // 全特化 
Subway<int,GuideGog> blind;
blind.print(); // 局部特化
```

**Example_3:** 判断一个类型是不是数组

```c++
// 原始模板
template<class T1>
struct Is_Array {
    static constexpr bool value = false;
};
// 特化参数修饰
template<class T1>
struct Is_Array<T1[]> {
    static constexpr bool value = true;
};
// 特化参数修饰 + 个数(非类型修饰)
template<class T1, size_t size>
struct Is_Array<T1[size]> {
    static constexpr bool value = true;
};

std::cout << Is_Array<int>::value;		//  false
std::cout << Is_Array<int[]>::value;     // true
std::cout << Is_Array<int[2][3]>::value; // true
```



## 变参模板

```c++
template<class... T>
void varfun(T... args) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

template<class T, class... ArgT>
void varfun(T t, ArgT... args) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

// 优先调用 template<class T, class... ArgT>
varfun(1);			// void varfun(T, ArgT ...) [with T = int; ArgT = {}]
varfun(1, 2.0, 3.0f);// void varfun(T, ArgT ...) [with T = int; ArgT = {double, float}]
```

**Example:** 打印所有参数

```c++
#ifdef RECURSIVE_EXIT
// 递归出口
void print()
{
    std::cout << "\n----出口-------\n";
}
#endif

template<class T, class... ArgT>
void print(T t0, ArgT... t)
{
    std::cout << t0 << " ";
#ifndef RECURSIVE_EXIT
    // 编译期if
    if constexpr(sizeof...(ArgT) > 0)
#endif
        print(t...);
}
```

### 折叠表达式

一元左折叠: **( 形参包 运算符 ... )**

```c++
展开:( ((E1 op E2) op E3) op E4 )
```

一元右折叠: **( ... 运算符 形参包 )**

```c++
展开:( E1 op (E2 op ((E3 op E4))) )
```

二元左折叠: **( 初值 运算符 ... 运算符 形参包 )**

```c++
展开: ( (((V0 op E1) op E2)) op E3 )
```

二元右折叠:**( 形参包 运算符 ... 运算符 初值 )**  

```c++
展开: ( (E1 op (E2 op (V0 op E3))) )
```



**Example_1:**

```c++
template<class... ArgT>
void test(ArgT... args)
{
    std::cout << (args - ...) << "\n"; // (((1 - 2) - 3) - 4) = -2
    std::cout << (... - args) << "\n"; // (1 - (2 - (3 - 4))) = -8
}
test(1,2,3,4);
```



## 类型推导

### auto

- 去除`cv` `&`限定符(const,volatile, reference) 指针除外

```c++
int 		 i = 1;
int &		ri = i;
int const&	cri = i;
auto x =   i; // int
auto y =  ri; // int
auto z = cri; // int
```

- 添加const和&

```c++
int i = 1;
auto const	ci = i;	// int const
auto &	   	ri = i;	// int &
auto const&	cri = i;// int cont&
```

- 对于指针, 保留外层const和指针

```c++
int* p1;
const int* p2;
int* const p3{};
const int* const p4{};
auto x1 = p1;  // int*
auto x2 = p2;  // const int*
auto x3 = p3;  // int*
auto x4 = p4;  // const int*
```

- auto返回类型推导(值返回)



### decltype

保留`cv` `&` 限定符(const,volatile, reference)

```c++
int		     i = 1;
int &       ri = i;
int const& cri = i;
using T1 = decltype(i);   // int
using T2 = decltype(ri);  // int &
using T3 = decltype(cri); // int const&
decltype(cri) y = i; // int const&
// 保留cv和&
decltype(auto) x = i;	// int
decltype(auto) y = ri;	// int &
decltype(auto) z = cri;	// int const &
```

- decltype(auto) 返回类型推导 (保留const reference)
- 尾置返回类型



### 类模板参数推导

- **(<=C++14)**, types must be given explicitly
- **(> C++14)**, Class Template Parameter Deduction

```c++
std::pair<int,int> p{1,1}; // C++ <= 14 显式地提供模板参数
std::pair p{1,1}; // C++ > 14
```

- Template Parameter Deduction Guides

让编译器自动推导模板参数，而无需显式地指定模板参数, 从构造函数参数推导

```c++
std::pair p(2, 4.5);     // 推导出 std::pair<int, double> p(2, 4.5);
std::tuple t(4, 3, 2.5); // 同 auto t = std::make_tuple(4, 3, 2.5);
```

> 类模板不支持聚合初始化(必须要有相应的构造函数)

- [C++17 显式推导指引](./typeDeduction/explicit_TDguide.cpp)



## type_traits

- `std::enable_if<bool,T>`: bool为false**禁用特定的模板实例化**(SFINAE)

```c++
template <bool _Test, class _Ty = void>
struct enable_if {}; // no member "type" when !_Test

template <class _Ty>
struct enable_if<true, _Ty> { // type is _Ty for _Test
    using type = _Ty;
};

template <bool _Test, class _Ty = void>
using enable_if_t = typename enable_if<_Test, _Ty>::type;
```

**Example_1:** bool为true

```c++
// -- 编译期判断一个数是不是偶数
template<class T>
typename std::enable_if<std::is_integral<int>::value,bool>::type
isEven(T t) {
    return t % 2 == 0;
}
std::cout << std::is_same_v<void, std::enable_if_t<true>> << "\n";    // true
std::cout << std::is_same_v<int, std::enable_if_t<true,int>> << "\n"; // true
std::cout << isEven(3) << "\n"; // false
```

**Example_2:** bool为false禁用特定的模板实例化

[构造函数为万能引用时, 如何做到不接受自己类型](./SFINAE/enable_if.cpp)

```c++
// 自实现
template<bool a>
struct enable_int_if  {
    using type = int;
};

template<>
struct enable_int_if<false> {};

template<bool a>
using enable_int_if_t = typename enable_int_if<a>::type;

enable_int_if_t<false>;  // 编译失败
enable_int_if_t<true> a; // 编译成功
```

**移除:**

- `std::remove_all_extents_t` : 移除数组的所有[]
- `std::remove_extent_t` : 移除一层[]
- `...`

**常量:**

- `std::integral_constant<class Ty, Ty Val>` : 整型常量

  - ```c++
    // 自实现
    template<class T, T constant_value>
    struct int_constant
    {
        using value_type = T;
        static constexpr value_type value = constant_value;
        operator value_type() const { return constant_value; }
        value_type operator()() const { return constant_value; }
    };
    ```


- `bool_constant<bool Val>` :布尔常量

  - ```c++
    template<bool __v>
    using bool_constant = integral_constant<bool, __v>;
    ```

- `std::true_type` `std::false_type`

  - ```c++
    typedef integral_constant<bool, true>     true_type;
    typedef integral_constant<bool, false>    false_type;
    ```

**其他:**

- `std::conditional<bool,T1,T2>` : 编译期间根据条件选择类型

- `std::conjunction<class... ArgsT>` : 模板参数包都为真, 其value成员为true

  - `ArgsT` : type_traits模板, is_*
  - **Example**

  ```c++
  // 如果参数包都可以转为T,则value为true
  template<class T, class... Args>
  std::enable_if_t<std::conjunction_v<std::is_convertible<T, Args>...>, T>
  sum(Args... args) {
  	return (args + ...);
  }
  std::cout << sum<int>(1,2,3,4,5) << "\n";
  // 判断类型
  if (std::conjunction_v<std::is_integral<int>, std::is_signed<int>>)
  	std::cout << "integral + signed\n";
  else
  	std::cout << "non integral + signed\n";
  ```
  
- `std::decay<T>` : 衰退

  - 1. **先去除引用**
    2. 如果是函数签名, 将函数签名转化为函数指针
    3. 如果是数组(有`[]`), 去除`[]`转化为指针
    4. 如果T有`const` 或`volatile`限定, 去除
    
  - **Example**
  
    ```c++
    using A = std::decay_t<int (&)[3][4][5]>;// int(*)[4][5]
    using B = std::decay_t<const int*>; // const int* 
    
    // 函数签名 -> 函数指针
    using C = std::decay_t<int(int)>; // int(*)(int)
    std::cout << std::is_same_v<decltype(pfun), void(int,int)> << "\n"; // true
    std::cout << std::is_same_v<decltype(&pfun), void(*)(int,int)> << "\n"; // true
    ```
  
  - 模拟MSVC实现
  
    ```c++
    template<bool>
    struct Select {
        template<class T1,class>
        using Apply = T1;
    };
    
    template<>
    struct Select<false>{
        template<class,class T2>
        using Apply = T2;
    };
    
    template<class T>
    struct Decay {
        using T1 = std::remove_reference_t<T>;
        using T2 = typename Select< std::is_function_v<T1> >::template 
        	Apply< std::add_pointer_t<T1>, std::remove_cv_t<T1> >;
        using type = typename Select< std::is_array_v<T1> >::template 
    		Apply< std::add_pointer_t<std::remove_extent_t<T1>>, T2 >;
    };
    
    template<class T>
    using Decay_t = typename Decay<T>::type;
    ```
  

### **练习:**

**Example_1:** 自实现`std::conditional<bool,T1,T2>`

```c++
template<bool cond, class T1, class T2>
struct Conditional {
    using type = T1;
};

template<class T1, class T2>
struct Conditional<false,T1,T2> {
    using type = T2;
};

template<bool cond, class T1, class T2>
using Conditional_t = typename Conditional<cond, T1, T2>::type;

constexpr int n = 100;
Conditional_t<(n > UCHAR_MAX), int, unsigned char> t; // unsigned char
```

**Example_2**: 自实现`std::remove_reference<T>`

```c++
template<class T>
struct RemoveRef {
    using type = T;
};

template<class T>
struct RemoveRef<T&> {
    using type = T;
};

template<class T>
struct RemoveRef<T&&> {
    using type = T;
};

template<class T>
using RemoveRef_t = typename RemoveRef<T>::type;
```

**Example_3**: 自实现`std::is_void<T>`

```c++
template<class T>
struct Is_Void {
    using value_type = bool;
    static constexpr value_type value = false;
};

template<>
struct Is_Void<void> {
    using value_type = bool;
    static constexpr value_type value = true;
};

template<class T>
constexpr bool Is_Void_v = Is_Void<T>::value;
```

**Example_4:** 自实现`std::is_same`

```c++
template<class T1, class T2>
struct my_is_same
{
    static constexpr bool value = false;
};

template<class T>
struct my_is_same<T,T>
{
    static constexpr bool value = true;
};

template<class T1, class T2>
constexpr bool my_is_same_v = my_is_same<T1,T2>::value;
```





## 萃取

一种编程思想, 对编译期的编程操作 is_

**值萃取:** 从一个类型萃取出一个值

**类型萃取:** 

[Example_1](./traits.cpp): 固定萃取, 使accumulate不溢出



## 模板元编程

编译期计算

[Modern C++模板元编程 (netcan.github.io)](https://netcan.github.io/presentation/metaprogramming/#/)



# Note

1. 类模板实参推导**[C++17]**通过构造函数隐式实例化类模板

2. `template<>`

全特化,告诉编译器接下来的函数定义是一个函数模板的全特化实现。

3. `using remove_reference_t = typename remove_reference<_Ty>::type;` 中的`typename`作用

告诉编译器`remove_reference<_Ty>::type`类型,不是静态成员变量或者静态成员函数.

4. `_t`后缀**[C++14]**: 代表类型, 如`std::remove_reference_t<int&>`等价于`std::remove_reference<int&>::type`

   `_v`后缀**[C++17]**: 代表值, 如`std::is_same_v<int,float>`等价于`std::is_same<int,float>::value`

5. `SFINAE`: [替换失败不是错误](./SFINAE/SFINAE.cpp)

   使用某些特定模板参数实例化模板失败不会导致错误，而**只是丢弃**该实例化

   ```c++
   template <class T, class Enable = void>
   class foo;
   
   template <class T> // 替换 const char* 失败 丢弃
   class foo<T, std::enable_if_t<!std::is_same_v<std::decay_t<T>, const char*>>> {
   public:
       T val;
       foo(const T&& val) : val(val) {}
   };
   
   
   template <class T> // 替换 const char* 成功
   class foo<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, const char*>>> {
   public:
       const char* val;
       foo(const char* str) : val(str) {}
   };
   
   template<class T>
   foo(T) -> foo<T,void>;
   ```









