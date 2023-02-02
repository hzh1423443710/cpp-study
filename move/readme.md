- 左值 左值引用

- 右值(实现移动语义) 右值引用

# 移动语义

​	指的就是以**移动**而**非深拷贝**的方式初始化**含有指针成员**的类对象。

## 移动构造

```c++
String(String&& other) noexcept :data(nullptr) {
    delete data;
    size = other.size;
    data = other.data;
    other.data = nullptr;
    other.size = 0;
    std::cout << "move construction" << std::endl;
}
```

Example:

```c++
//返回右值临时对象
String test(const char* str) {
	String s(str);
	std::cout << (void*)s.c_str() << std::endl;
	return s;
}
int main() {
    String str = test("hello");//返回时 调用 移动构造函数
	std::cout << (void*)str.c_str() << "  " << str << std::endl;
}
```

```sh
$ g++ -fno-elide-constructors .\main.cpp #取消返回值优化
construction			#test 中的 String s(str); 构造函数
move construction		#栈内存 -> 临时变量 (不调用拷贝构造) s 的资源 -> 临时变量
destruction				#test 中的 s 销毁
move construction		#临时变量 -> str(main)
destruction				#临时变量销毁
0x6d1760  hello			#成功 移动
destruction				#str(main) 销毁
```



## 移动赋值

```c++
String& operator = (String&& other) noexcept {
    if (this == &other)
        return *this;
    size = other.size;
    data = other.data;
    other.data = nullptr;
    other.size = 0;
    return *this;
    std::cout << "move assign construction" << std::endl;
}
```

Example:

```c++
int main() {
    String str;
	str = String("Hello Moss"); //调用 移动赋值函数
	std::cout << str << std::endl;
}
```

```sh
$ g++ main.cpp
construction					#构造 str(main)
construction					#构造临时对象
move assign construction		#临时对象资源 -> str
destruction						#销毁临时变量
Hello Moss						#成功移动
destruction						#销毁str
```

## std::move

​	将左值转换为右值

Example:

```c++
String str;
String str2("Hello Moss");		//拷贝赋值
str = str2;
std::cout << str << std::endl;
```

```c++
String str;
String str2("Hello Moss");		//移动赋值
str = std::move(str2);
std::cout << str << std::endl;
```



# 完美转发

​	指的是函数模板可以将自己的参数“完美”地转发给内部调用的其它函数。所谓完美，即不仅能准确地转发**参数的值**，还能保证被转发参数的**左、右值属性不变**。

​	参数在传递过程中左值或右值属性不会发生变化，如果左，右值属性发生变化，就不能进行正常的移动语义。

> - **万能引用(只出现再模板里)：**对于函数模板中使用右值引用语法定义的参数来说，既可以接收右值，也可以接收左值，
>
> ```c++
> //实现完美转发的函数模板
> template <typename T>
> void function(T&& t) {		//T&& 既可以接收右值，也可以接收左值，形参t是左值
>     otherdef(forward<T>(t));//将t转发为 t对应的实参的类型，function(type)
> }
> ```
>
> - **模板函数 `forword<T>()`：**转发参数，修饰被调用函数中需要维持左、右值属性的参数；如果 参数是一个右值，转发之后仍是右值引用；如果参数是一个左值，转发之后仍是左值引用。

Example:

```c++
void reference(int& s) {//接受左值
	std::cout << "left reference" << std::endl;
}

void reference(int&& s) {//接受右值
	std::cout << "right reference" << std::endl;
}

template<typename T>
void function(T&& arg) {
	reference(std::forward<T>(arg));
}

int main()
{
	int x = 200;
	int& rx = x;
	function(x);			//左值
	function(rx);			//左值引用
	function(std::move(x));	//右值
	function((int&&)x);		//右值引用
	return 0;
}
/*
left reference
left reference
right reference
right reference
*/
```



# 引用折叠

​	A为实参类型

- 当实参为**左值**或者**左值引用（A&）**时，函数模板中 T&& 将转变为 A&（A& && = A&）；
- 当实参为**右值**或者**右值引用（A&&）**时，函数模板中 T&& 将转变为 A&&（A&& && = A&&）。

转化规则:

T&  &  -> T&	左值引用的左值引用

T&& &  -> T&	右值引用的左值引用

T& &&  -> T&	左值引用的右值引用

T&& && -> T&	右值引用的右值引用

Example:

```c++
template <typename T>
void function(T&& t) {
    otherdef(forward<T>(t));
}
int n = 10;
int & num = n;
function(num); 	// A 为int& , T 为 int&
int && num2 = 11;
function(num2); // A 为int&&, T 为 int&&
```

传入左值:

```c++
void function(T&& t) {
    otherdef(forward<T>(t));
}
//传入左值 T展开为A& (T -> A&)
void function(A& && t) {
    otherdef(forward<T>(t));
}
//引用折叠
void function(A& t) {
    otherdef(forward<A&>(t));//t的类型:A&
}
//转发
template <class _Ty>
_Ty&& forward(_Ty& _Arg) { //_Ty 为 A&
    return static_cast<_Ty&&>(_Arg);
}
//引用折叠
template <class _Ty>
A& && forward(A& & _Arg) {
    return static_cast<A& &&>(_Arg);
}
A& forward(A& _Arg) {
    return static_cast<A&>(_Arg);
}
```

传入右值:

```c++
void function(T&& t) {
    otherdef(forward<T>(t));
}
//传入左值 T展开为A (T -> A)
void function(A&& t) {
    otherdef(forward<A&&>(t));//t的类型:A&&
}
//转发
template <class _Ty>
 _Ty&& forward(_Ty&& _Arg) {//_Ty 为 int&&
    return static_cast<_Ty&&>(_Arg);
}
//引用折叠
template <class int&&>
int&& && forward(int&& && _Arg) {
    return static_cast<int&& &&>(_Arg);
}
A&& forward(A&& _Arg) {
    return static_cast<A&&>(_Arg);
}
```

练习:

```c++
template<typename T>
void print(T& t) {
	std::cout << "lvalue" << std::endl;
}
template<typename T>
void print(T&& t) {
	std::cout << "rvalue" << std::endl;
}

template<typename T>
void TestForward(T&& v) {
	print(v);					//l:左值 print(T& t)
	print(std::forward<T>(v));	// :取决于 v 的实参是左值还是右值 static_cast<T&&>(_Arg);
	print(std::move(v));		//r:右值 print(T&& t)
}

void test() {
	int x = 1;
	TestForward(1);//实参为右值 lrr
	std::cout << "------" << std::endl;
	TestForward(x);//实参为左值 llr
	std::cout << "------" << std::endl;
	TestForward(std::forward<int>(x));//实参为右值 lrr ,static_cast<int&&>(_Arg);
	std::cout << "------" << std::endl;
	TestForward(std::forward<int&>(x));//实参为左值 llr ,static_cast<int& &&>(_Arg);
	std::cout << "------" << std::endl;
	TestForward(std::forward<int&&>(x));//实参为右值 lrr ,static_cast<int&& &&>(_Arg);
}
```



