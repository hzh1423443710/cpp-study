# 类型推导

Item1 - Item6

## 模板类型推导

```c++
template<typename T>
void f(ParamType param);
f(expr); // 调用
```

编译期, 会进行两个推导, 一个是针对`T`的, 另一个是针对 `ParaType` 的

T的推导取决于 `Parameter` 和 `expr`, 分3种情况

1. `ParaType` 是指针或左值引用
2. `paraType` 是万能引用
3. `ParaType` 既不是指针也不是引用

**情景一:** `ParaType` 是指针或左值引用

`ParaType` 中如果有`&` `const` `*`, T会忽略expr中的`&` `const` `*`

```c++
template<typename T>
void f(T& param);               // param是一个引用

int x=27;                       // int
const int cx=x;                 // const int
const int& rx=x;                // cosnt int&

f(x);                           // T == int
f(cx);                          // T == const int
f(rx);                          // T == const int
```

```c++
template<typename T>
void f(const T& param);         // param现在是reference-to-const

int x = 27;                     // int 
const int cx = x;               // const int
const int& rx = x;              // const int&

f(x);                           // T == int
f(cx);                          // T == int		
f(rx);                          // T == int
```

```c++
template<typename T>
void f(T* param);               // param现在是指针

int x = 27;                     // int
const int *px = &x;             // const int*

f(&x);                          // T == int
f(px);                          // T == const int
```

**情景二: `paraType` 是万能引用**

expr为左值, T <==> 左值引用

expr为右值, T <==> expr的原始类型



**情景三: **`ParaType` 既不是指针也不是引用

拷贝一份完整的对象 同`auto t = expr;`

- 去掉cv 和 &
- expr为指针 只去除修饰指向的const, 保留修饰值的const



## 退化->数组,函数签名和指针

在模板类型推导时，数组名或者函数名实参会退化为指针，除非它们被用于初始化引用

数组(实参)会退化为指针(形参)

函数签名(实参)会退化为函数指针(形参)



## auto类型推导

与模板推导基本相同



## decltype类型推导

decltype(auto)

decltype((x)) == int&