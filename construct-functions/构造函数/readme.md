### 构造函数--函数返回对象

**g++ -fno-elide-constructors**:去优化(关于临时对象构造函数)

```C++
A fun1()
{
    A* pa = new A(10);
    return *pa;
}

A fun2()
{
    A a(10);
    cout << "In fun2 &a = " << &a << endl;
    return a;
}
```

- test3() 不优化
```C++
$ g++ -fno-elide-constructors main.cpp  //去优化编译

A Have parameter construct funciton     //fun1()堆区创建对象a(10)
A copy construct function               //函数返回后将 a 拷贝给临时对象
A right reference costruct function     //临时对象赋值给obj1
obj.m_a = 10
------
A Have parameter construct funciton     //fun2()栈区创建对象a(10)  
In fun2 &a = 0x61fdac                   //打印fun2() 栈区对象的地址
A right reference costruct function     //函数返回后 将栈区的a拷贝给临时对象
A right reference costruct function     //临时对象赋值给obj2   
obj2.m_a = 10, &boj2 = 0x61fde0         //未优化 地址不一样
------
```

- test3() 优化
```c++
$ g++ main.cpp                          //优化编译
A Have parameter construct funciton     //fun1()堆区创建对象a(10)
A copy construct function               //拷贝构造赋值给obj1
obj.m_a = 10
------
A Have parameter construct funciton     //fun2()栈区创建对象a(10)
In fun2 &a = 0x61fde8                   //打印fun2() 栈区对象的地址
obj2.m_a = 10, &obj2 = 0x61fde8         //没有拷贝 obj2的地址就是fun2()中栈区a的地址
------
```

### 拷贝赋值函数

- **拷贝赋值函数与拷贝构造函数一样会有浅拷贝问题**

> **自定义深拷贝赋值函数**

```c++
T& operator=(const T& other)//const -> 可以接受左值和右值
{
    if(this != &other){//防止自引用
        //delete旧资源
        //分配新资源
        //拷贝新数据
	}
    return *this;//返回自引用 -> 可以作为左值,链式调用
}
```

> demo-String

```c++
//方法1
String& operator=(const String& other)
{
    if(this != &other){
        delete m_str;
        m_str = new char[strlen(other.m_str)+1];
        strcpy(m_str,other.m_str);
	}
}
//方法2
String& operator=(const String& other)
{
    if(this != &other){
		String temp(other);		//调用深拷贝构造
        swap(m_str,temp.m_str);	//交换内存
	}
}
```

