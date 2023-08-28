# 1.Structured binding declaration 

[结构化绑定](./StructuredBinding.cpp)

- C++ 17
- 返回多类型变量，可以结合 pair tuple 使用

```c++
//方式1 pair(仅限2个元素)
std::pair<std::string,int> CreatePerson_ByPair()
{
	return { "Moss",21 };
}
//方式2 tuple可以多个元素
std::tuple<std::string, int> CreatePerson_ByTuple()
{
	return { "Buddy",20 };
}
struct Person
{
	std::string name;
	int age;
};
//方式3 struct
Person CreatePerson_ByStruct()
{
	return { "Hoeny",22 };
}

int main()
{
	//pair
	std::cout << "------- 访问 parir  -------" << std::endl;
	std::pair<std::string, int> ret1 = CreatePerson_ByPair();
	std::cout << ret1.first << " " << ret1.second << std::endl;

	//tuple - get<>()
	std::tuple<std::string, int> t1 = CreatePerson_ByTuple();
	std::cout << "\n------- 访问 tuple get -------" << std::endl;
	std::string name = std::get<0>(t1);
	int age = std::get<1>(t1);
	std::cout << name << " " << age << std::endl;
	//tuple - tie()
	std::cout << "\n------- 访问 tuple tie -------" << std::endl;
	std::string nameT;
	int ageT;
	std::tie(nameT,ageT) = CreatePerson_ByTuple();
	std::cout << nameT << " " << ageT << std::endl;
	//tuple - 结构化绑定
	std::cout << "\n------- 访问 tuple 结构化绑定 -------" << std::endl;
	auto [nameB, ageB] = CreatePerson_ByTuple();//也可以 struct pair
	std::cout << nameB << " " << ageB << std::endl;

	//struct 
	std::cout << "\n------- 访问 struct  -------" << std::endl;
	Person ret3 = CreatePerson_ByStruct();
	std::cout << ret3.name << " " << ret3.age << std::endl;

	return 0;
}
```



# 2.Optional

处理可能存在也可能不存在的情况

## Introduction

`#include <optional>`

类模板 `std::optional` 管理一个*可选*的容纳值，既可以存在也可以不存在的值。

一种常见的 `optional` 使用情况是一个可能失败的函数的返回值。与其他手段，如 `std::pair<T,bool>` 相比， `optional` 良好地处理构造开销高昂的对象，并更加可读，因为它显式表达意图。

对象在下列条件下*不含值*：

- 对象被默认初始化。
- 对象被以 `std::nullopt_t` 类型值或*不含值*的 `optional` 对象初始化/赋值。
- 调用了成员函数 `reset()` 。

## functions

> | **operator bool has_value** | **检查对象是否含值 (公开成员函数)**                       |
> | --------------------------- | --------------------------------------------------------- |
> | **value**                   | **返回所含值 (公开成员函数)**                             |
> | **value_or**                | **若所含值可用则返回它，否则返回另一个值 (公开成员函数)** |

### Example

```c++
#include <optional>

struct Color
{
	unsigned r, g, b,a;
	void setAlpha(unsigned alpha) {
		a = alpha;
	}
	friend std::ostream& operator << (std::ostream& out, const Color& color) {
		out << "(" << color.r << "," << color.g << "," << color.b << ")" ;
		return out;
	}
};

std::optional<Color> getColor(unsigned r, unsigned g, unsigned b)
{
	if ((r > 255 || r < 0) || (g > 255 || g < 0) || (b > 255 || b < 0))
		return std::nullopt;//或 return {};
	return Color{ r, g, b };
}

int main()
{
	std::optional<Color> ret = getColor(255, 255, 255);
	if (ret) { // 或 ret.has_value
		std::cout << *ret << std::endl;
	}
	ret = getColor(123, -1, 123);
	if (ret == std::nullopt)
		std::cout << "Invalid Color: " << ret.value_or(Color{0,0,0}) << std::endl;
	return 0;
}
```



# 3.variant

**单一变量存放多种类型数据**，需要列出所有类型

​	类模板 `std::variant` 表示一个类型安全的联合体。 `std::variant` 的一个实例在任意时刻要么保有其一个可选类型之一的值，要么在错误情况下无值。

- 和联合体的大小计算不同**(所有数据不共享内存)**，会把所有类型全部计算到内

- 同联合体，一次只能访问其一个变量/类型的数据(可以有多个相同类型) **&&** 只能访问 index() 下的变量

- **始终有可用选项：**使用时必须初始化其一个选项，默认初始化**首个选项**（默认初始化：如果首个选项为class，必须有默认构造函数），也可以手动初始化

Example2:

```c++
//无默认构造函数
class Coco
{
public:
	Coco(std::string name) :m_name(name)
	{
		std::cout << "construction function -> " << name << std::endl;
	}
	friend std::ostream& operator << (std::ostream& out, const Coco& it) {
		out << it.m_name;
		return out;
	}
private:
	std::string m_name;
};

int main()
{
    std::variant<Coco, double> v{Coco("Moss")}; //index = 0

    v.emplace<1>(3.14);//index = 1 

    if (auto pV = std::get_if<Coco>(&v)) {//false 只能访问 index() 下的变量
        std::cout << *pV << std::endl;//nullptr
    }
    if (auto pV = std::get_if<1>(&v)) {
        std::cout << *pV << std::endl;
    }
}
```

Example3:

```c++
int main()
{
  	std::variant<Coco,double> v0{};	//编译期报错 Coco类无默认构造函数 variant无法初始化首个选项
    std::variant<Coco, double> v2{Coco("Moss")};//手动初始化 一个选项
	std::variant<double, Coco> v; 	//默认初始化第一个选项 (会自动初始化double) -> index = 0
	try {
		int curIndex = v.index();
		std::cout << "当前可用选项下标: " << curIndex << std::endl;
		if(curIndex == 0)
			std::cout << "Value of at 0 : " << std::get<0>(v) << std::endl;

		std::cout << std::get<Coco>(v) << std::endl; //throw exception 抛出异常
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
```



## Member funcitons

### index

- 查询当前设置可用选项的下标（从0开始）

```c++
constexpr std::size_t index() const noexcept;  (C++17 起) 
```

## Nonmember functions

### get

- 以给定索引或类型（若类型唯一）读取 `variant` 的值，错误时抛出异常 `std::bad_variant_access`

```c++
T& std:;get<size_t>(std::variant);
T& std:;get<T>(std::variant);
```

### emplace

  原位构造 variant 中的值

```c++
T& emplace<size_t index>(T);//指定下标 构造 对应的类型
T& emplace<T>(T);//多个相同类型不适用
```

Examle：

```c++
std::variant<double, double> v;
std::cout << v.emplace<double>(3.14) << std::endl;//error
```

### get_if

以给定**索引**或类型（若其唯一），获得指向被指向的 variant 的值的指针，错误时返回空指针

```c++
T* std:;get_if<size_t>(std::variant* );
T* std:;get_if<T>(std::variant* );
```



```c++
int main()
{
	std::variant<Coco, double> v{Coco("Moss")};

	if (auto pV = std::get_if<Coco>(&v)) {	//获取指向 Coco 的指针
		std::cout << *pV << std::endl;		//Moss
	}
	else {
		std::cout << (void*)pV << std::endl;
	}

	v = 3.14;//curEntry = double

	if (auto pV = std::get_if<Coco>(&v)) {	//false
		std::cout << *pV << std::endl;		
	}
	else {
		std::cout << (void*)pV << std::endl;//nullptr
	}

	return 0;
}
```



# 4.any

[【78】【Cherno C++】【中字】如何存储任意类型的数据_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1hT4y1C7Qc/?spm_id_from=333.788&vd_source=ba8c5cd2a5e568da8003b2d5b14b51cd)

```c++
int main()
{
	std::any a;
	
	a = 18;
	//取出数据 any_cast<T>(std::any)
	std::cout << a.type().name() << " " << std::any_cast<int>(a) << std::endl;

	try {
		a = 3.14;
		std::cout << a.type().name() << " " << std::any_cast<int>(a) << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	a = Coco("Moss");
	std::cout << a.type().name() << " " << std::any_cast<Coco>(a) << std::endl;

	return 0;
}
```



# 5.string_view

字符串视图

viual studio Debug

```c++
#include <iostream>
#include <string>

static int s_count;

void* operator new (size_t size)
{
	s_count++;
	std::cout << __FUNCTION__ << " size = " << size << std::endl;
	return malloc(size);
}

void PrintName(const std::string& str)
{
	std::cout << str << std::endl;
}

int main()
{
	std::string name = "hello";	//1
	PrintName("hello");			//2
   	std::string pre = name.substr(0, 5);//3
	std::cout << s_count << " times" << std::endl;
	return 0;
} 
/*
operator new size = 16
operator new size = 16
operator new size = 16
hello
3 times
*/
```

使用 string_view

```c++
#include <string_view>
static int s_count;
void* operator new (size_t size)
{
	s_count++;
	std::cout << __FUNCTION__ << " size = " << size << std::endl;
	return malloc(size);
}
void PrintName(const std::string_view& str)//string_view
{
	std::cout << str << std::endl;
}
int main()
{
	std::string name = "hello world";//1
	std::string_view view(name.c_str(), 5);
	PrintName(name.c_str());
	std::cout << s_count << " times" << std::endl;
	return 0;
} 
/*
operator new size = 16
hello world
1 times
*/
```

string SSO

> ​	string: <= 15 个字符不会在堆上分配空间(release)

[C++ folly库解读（一） Fbstring —— 一个完美替代std::string的库 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/348614098)



# 6.if/switch initialization

1.

```c++
// if 初始化
if (auto var = expr; var != nullptr) {
    // ...
}
// switch 初始化
switch (auto var = expr; var->type()) {
    case TokenType::Plus:
        // 处理加号
        break;
    case TokenType::Minus:
        // 处理减号
        break;
    default:
        // 非法类型
        break;
}
```

2.[if-statement`语法中也可以使用`structured bindings](./Init_statement_for_if.cpp)

```c++
if (auto [x, y] = std::make_tuple(1, 2); x + y > 1) {
    // 执行语句
}
```

