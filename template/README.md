# 泛型编程

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



### 特化

函数模板(包括成员函数)**只有全特化**,没有局部特化.

类模板既有**全特化**也有**局部特化**.

**分类:**

- 全特化:`template<>`
- 局部特化
  - 特化参数个数
  - 特化参数修饰

**Example_1:** 类模板(全特化 + 特化参数修饰)

```c++
// 原始模板
template <class _Ty>
struct RemoveConstAndPtr { 
    using type = _Ty;
};
// 局部特化(特化参数修饰)
template <class _Ty>
struct RemoveConstAndPtr<const _Ty*> {
    using type = _Ty;
};
// 全特化
template<>
struct RemoveConstAndPtr<double> {
    void print() {
        std::cout << "Full Specialization\n";
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
int main() 
{
    Subway<Policeman> a; 
    a.print(); // 缺省原始模板
    Subway<Policeman,PoliceDog> policeman;
    policeman.print(); // 全特化 
    Subway<int,GuideGog> blind;
    blind.print(); // 局部特化
}
```



## type_traits

**`enable_if<bool,T>`**:

bool为false, 结构为空

bool为true, 结构中type为T类型

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





### 萃取

`_t`后缀**[C++14]**: 代表类型, 如`std::remove_reference_t<int&>`等价于`std::remove_reference<int&>::type`

`_v`后缀**[C++17]**: 代表值, 如`std::is_same_v<int,float>`等价于`std::is_same<int,float>::value`



**Example_1**: 自实现`std::remove_reference<T>`

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

**Example_2**: 自实现`std::is_void<T>`

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





# Note

1. 类模板实参推导**[C++17]**通过构造函数隐式实例化类模板

```c++
template<class T>
class Cat 
{
public:
    Cat(T a){};    
};
Cat a(1); // C++17
```

2. `template<>`

全特化,告诉编译器接下来的函数定义是一个函数模板的全特化实现。

3. `using remove_reference_t = typename remove_reference<_Ty>::type;` 中的`typename`作用

告诉编译器`remove_reference<_Ty>::type`类型,不是静态成员变量或者静态成员函数.

4. `std::remove_pointer_t`以`_t`为后缀**[C++14]**
5. `std::is_same_v`以`_v`为后缀**[C++17]**