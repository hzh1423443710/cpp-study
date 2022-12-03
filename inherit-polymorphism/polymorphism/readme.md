### 重写虚函数的条件

- 类的成员函数 (**全局函数,静态成员函数,构造函数不行**)
- 基类中要加virtual
- 重写版本**函数名 参数表 常属性**要一致
- 返回**相同的数据类型**
- 如果基类虚函数返回类类型的指针`T*`或引用`T&`,允许子类中的重写版本返回其子类类型的`T*`或引用`T&`,

### dynamic_cast static_cast
> 向下转换要加static_cast

      A
     / \
    B   C 
```C++
B b;
A* pa = &b;						//多态 子类指针给父类
B* pb = static_cast<B*>(pa);    //合理  向下转换
C* pc = static_cast<C*>(pa);    //能转换但不合理 间接的向下转:B->A->C
//C* pc = dynamic_cast<C*>(pa); //报错 dynamic_cast 可以检测不合理的转换
```

