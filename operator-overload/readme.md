# 操作符重载
### +运算符

- **三个const**
```c++
/*
 *  第一个const:1.支持链式 2.不允许这种操作:(c1+c2) = c3; 
 *  第二个const:接受左值引用,常引用,右值引用
 *  第三个const:可供常对象使用
 *
 */
const Cat operator+(const Cat &other) const
{
    Cat temp(m_num + other.m_num);
    return temp;
}
```

### new和delete 操作符

> ```c++
>static void* operator new(size_t size){...}
>static void operator delete(void* p){...}
> ```

> 对象的创建和销毁过程
- new创建对象时,先调用`operator new`分配内存,再调用构造函数
- delete销毁对象时,先调用析构函数,再调用`operator delete`释放内存