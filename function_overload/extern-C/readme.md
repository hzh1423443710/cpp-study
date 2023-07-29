### C/C++混合编程

> C++有名称修饰
> `extern "C"` C++语法 函数声明必须写 函数实现可以不写

```C++
void fun();					//C++ 方式编译
extern "C" void fun(int);	//C 语言方式编译

int main()
{
	fun();
	fun(1);
	
	return 0;
}

void fun()
{
	std::cout << "C++" << std::endl;
}
extern "C" void fun(int)
{
	std::cout << "C" << std::endl;
}
```