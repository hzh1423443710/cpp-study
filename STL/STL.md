# STL

[STL教程：C++ STL快速入门（非常详细） (cdsy.xyz)](https://www.cdsy.xyz/computer/programme/stl/20210307/cd161510803212091.html)

| STL的组成  | 含义                                                         |
| :--------- | ------------------------------------------------------------ |
| 容器       | 一些封装[数据结构](http://www.cdsy.xyz/computer/programme/algorithm/)的模板类，例如 vector 向量容器、list 列表容器等。 |
| 算法       | STL 提供了非常多（大约 100 个）的数据结构算法，它们都被设计成一个个的模板函数，这些算法在 std 命名空间中定义，其中大部分算法都包含在头文件 <algorithm> 中，少部分位于头文件 <numeric> 中。 |
| 迭代器     | 在 [C++](http://www.cdsy.xyz/computer/programme/vc/) STL 中，对容器中数据的读和写，是通过迭代器完成的，扮演着容器和算法之间的胶合剂。 |
| 函数对象   | 如果一个类将 () 运算符重载为成员函数，这个类就称为函数对象类，这个类的对象就是函数对象（又称仿函数）。 |
| 适配器     | 可以使一个类的接口（模板的参数）适配成用户指定的形式，从而让原本不能在一起工作的两个类工作在一起。值得一提的是，容器、迭代器和函数都有适配器。 |
| 内存分配器 | 为容器类模板提供自定义的内存申请和释放功能，由于往往只有高级用户才有改变内存分配策略的需求，因此内存分配器对于一般用户来说，并不常用。 |

1. 序列式容器：array、vector、deque、list 和 forward_list；
2. 关联式容器：map、multimap、set 和 multiset；
3. 无序关联式容器：unordered_map、unordered_multimap、unordered_set 和 unordered_multiset；
4. 容器适配器：stack、queue 和 priority_queue。

# 1.迭代器

1) **前向迭代器（forward iterator）**假设 p 是一个前向迭代器，则 p 支持 ++p，p++，*p 操作，还可以被复制或赋值，可以用 == 和 != 运算符进行比较。此外，两个正向迭代器可以互相赋值。

2) **双向迭代器（bidirectional iterator）**双向迭代器具有正向迭代器的全部功能，除此之外，假设 p 是一个双向迭代器，则还可以进行 --p 或者 p-- 操作（即一次向后移动一个位置）。

3) **随机访问迭代器（random access iterator）**随机访问迭代器具有双向迭代器的全部功能。除此之外，假设 p 是一个随机访问迭代器，i 是一个整型变量或常量，则 p 还支持以下操作：


- p+=i：使得 p 往后移动 i 个元素。
- p-=i：使得 p 往前移动 i 个元素。
- p+i：返回 p 后面第 i 个元素的迭代器。
- p-i：返回 p 前面第 i 个元素的迭代器。
- p[i]：返回 p 后面第 i 个元素的引用。

​	此外，两个随机访问迭代器 p1、p2 还可以用 <、>、<=、>= 运算符进行比较。另外，表达式 p2-p1 也是有定义的，其返回值表示 p2 所指向元素和 p1 所指向元素的序号之差（也可以说是 p2 和 p1 之间的元素个数减一）。

| 容器                               | 对应的迭代器类型   |
| ---------------------------------- | ------------------ |
| array                              | **随机访问**迭代器 |
| vector                             | **随机访问**迭代器 |
| deque                              | **随机访问**迭代器 |
| list                               | **双向**迭代器     |
| set / multiset                     | **双向**迭代器     |
| map / multimap                     | **双向**迭代器     |
| forward_list                       | **前向**迭代器     |
| unordered_map / unordered_multimap | **前向**迭代器     |
| unordered_set / unordered_multiset | **前向**迭代器     |
| stack                              | **不支持**迭代器   |
| queue                              | **不支持**迭代器   |



# 2.序列式容器

## array	

- 如果操作对象是普通数组，则 begin() 函数返回的是指向数组第一个元素的指针，同样 end() 返回指向数组中最后一个元素之后一个位置的指针（注意不是最后一个元素）。
- 在 `<array>` 头文件中还重载了 **get() 全局函数**，该重载函数的功能是访问容器中指定的元素，并返回该元素的**引用**,必须使用常量表达式。
- **swap()** 函数可以轻松实现两个相同数组**（类型相同，大小相同）**中元素的互换。
- 当两个 array 容器满足**大小相同并且保存元素的类型相同**时，两个 array 容器可以直接直接做赋值操作，即将一个容器中的元素赋值给另一个容器



## Vector

- `values.reserve(20);`如果 vector 的容量在执行此语句之前，已经大于或等于 20 个元素，那么这条语**句什么也不做**；

- 如果调用 reserve() 来增加容器容量，之前创建好的任何迭代器（例如开始迭代器和结束迭代器）都**可能会失效**，这是因为，为了增加容器的容量，vector<T> 容器的元素**可能已经被复制或移到了新的内存地址。**

- 可以用**一对指针或者迭代器**来指定初始值的范围

- 对于空的 vector 容器来说，begin() 和 end() 成员函数返回的迭代器是相等的，即它们指向的是同一个位置。

- emplace_back 和 push_back

- emplace 和 inset

- **remove** 删除容器中所有和指定元素值相等的元素，并返回指向最后一个元素下一个位置的迭代器**不会改变容器的大小和容量。**

- swap 减小容量至大小 `vector<T>(v).swap(v)` vector 模板类中的**拷贝构造函数只会为拷贝的元素分配存储空间**。

- swap 可以清空容器 `vector<T>().swap(v)`

- `vector<bool>` 不完全满足 C++ 标准中对容器的要求，尽量避免在实际场景中使用它！**存的是比特**

  

> - 仅通过 reserve() 成员函数增加 value 容器的容量，其大小并没有改变；但通过 resize() 成员函数改变 value 容器的大小，它的容量可能会发生改变。另外需要注意的是，通过 resize() 成员函数减少容器的大小（多余的元素会直接被删除），不会影响容器的容量。
>
> 

```c++
//_Alloc 表示内存分配器，此参数几乎不需要我们关心
template <class _Ty, class _Alloc = allocator<_Ty>>
class vector{
    ...
protected:
    pointer _Myfirst;
    pointer _Mylast;
    pointer _Myend;
};
template <class _Ty, class _Alloc = allocator<_Ty>>
class vector{
public：
    iterator begin() {return _Myfirst;}
    iterator end() {return _Mylast;}
    size_type size() const {return size_type(end() - begin());}
    size_type capacity() const {return size_type(_Myend - begin());}
    bool empty() const {return begin() == end();}
    reference operator[] (size_type n) {return *(begin() + n);}
    reference front() { return *begin();}
    reference back() {return *(end()-1);}
    ...
};
```

![img](https://www.cdsy.xyz/d/file/computer/programme/stl/2021-04-21/811905ff32c754daf06c20716a843bc2.gif)

- _Myfirst 和 _Mylast 可以用来表示 vector 容器中目前已被使用的内存空间；
- _Mylast 和 _Myend 可以用来表示 vector 容器目前空闲的内存空间；
- _Myfirst 和 _Myend 可以用表示 vector 容器的容量。

> 对于空的 vector 容器，由于没有任何元素的空间分配，因此 _Myfirst、_Mylast 和 _Myend 均为 null。	

### resize

> ​	强制 vector 容器必须存储 n 个元素，注意，如果 n 比 size() 的返回值小，则容器尾部多出的元素将会被析构（删除）；如果 n 比 size() 大，则 vector 会借助默认构造函数创建出更多的默认值元素，并将它们存储到容器末尾；如果 n 比 capacity() 的返回值还要大，则 vector 会先扩增，在添加一些默认值元素。

### remove

> ​	注意，在对容器执行完 remove() 函数之后，由于该函数并没有改变容器原来的大小和容量，因此无法使用之前的方法遍历容器，而是需要向程序中那样，借助 remove() 返回的迭代器完成正确的遍历。
>
> ​	remove() 的实现原理是，在遍历容器中的元素时，一旦遇到目标元素，就做上标记，然后继续遍历，直到找到一个非目标元素，即用此元素将最先做标记的位置覆盖掉，同时将此非目标元素所在的位置也做上标记，等待找到新的非目标元素将其覆盖
>
> ​	remove()用于删除容器中指定元素时，常和 erase() 成员函数搭配使用。

### remove 和 erase

vector/string 中的remove的作用是将等于value的元素放到vector的尾部，但并不减少vector的size

vector/string 中erase的作用是删除掉某个位置position或一段区域（begin, end)中的元素，减少其size

```c++
obj.erase(remove(begin(obj),end(obj),val),end(obj));//将其删除
```



### **shrink_to_fit** 

> 将当前 vector 容器的容量缩减至和实际存储元素的个数相等

### vector< bool >

​	可以选择使用 `deque<bool>` 或者 bitset 来替代 `vector<bool>`。

​	deque 容器几乎具有 vecotr 容器全部的功能（拥有的成员方法也仅差 reserve() 和 capacity()），而且更重要的是，**deque 容器可以正常存储 bool 类型元素。**

​	还可以考虑用 **bitset** 代替 `vector<bool>`，其本质是一个模板类，可以看做是一种类似数组的存储结构。和后者一样，bitset 只能用来存储 bool 类型值，且底层存储机制也采用的是用一个比特位来存储一个 bool 值。和 vector 容器不同的是，bitset 的大小在一开始就确定了，因此不支持插入和删除元素；另外 bitset 不是容器，所以不支持使用迭代器。



## deque

- deque 容器也擅长在序列尾部添加或删除元素（时间复杂度为O(1)），而不擅长在序列中间添加或删除元素。
- deque 容器也可以根据需要修改自身的容量和大小。
- 通过拷贝其他类型容器中**指定区域**内的元素（也可以是普通数组），可以创建一个新容器

​	和 vector 不同的是，deque **还擅长在序列头部添加或删除元素**，所耗费的时间复杂度也为常数阶O(1)。并且更重要的一点是，deque 容器中存储元素并**不能保证所有元素都存储到连续的内存空间**中。

### 底层实现

​	[深度剖析deque容器底层实现原理 (cdsy.xyz)](https://www.cdsy.xyz/computer/programme/stl/20210307/cd161510779711978.html)



## list

- list 容器在进行插入（insert()）、接合（splice()）等操作时，都不会造成原有的 list 迭代器失效，甚至进行删除操作，而只有指向被删除元素的迭代器失效，其他迭代器不受任何影响。(不需要重新开内存拷贝,释放原来内存)
- remove 根据值删除 erase 根据位置删除

### splice

​	insert是拷贝,splice是摘除 拼接

​	splice() 成员方法移动元素的方式是，将存储该元素的节点从 list 容器底层的链表中摘除，然后再链接到当前 list 容器底层的链表中。这意味着，当使用 splice() 成员方法将 x 容器中的元素添加到当前容器的同时，该元素会从 x 容器中删除。

### unique

​	删除容器中**相邻的重复**元素，只保留一份。



## 判断为空 empty size

​	选用 empty() 判断容器是否为空，效率总是最高的

> ​	无论是哪种容器，只要其模板类中提供了 empty() 成员方法，使用此方法都可以保证在 O(1) 时间复杂度内完成对“容器是否为空”的判断；但对于 list 容器来说，使用 size() 成员方法判断“容器是否为空”，可能要消耗 O(n) 的时间复杂度。

## forward_list

​	效率高

- 没有size函数

### distance

​	获取大小

### advance

### merge

​	合并两个事先已排好序的 forward_list 容器，并且合并之后的 forward_list 容器依然是有序的.



# 3.关联式容器

| 关联式容器名称 |                       特点(底层红黑树)                       |
| -------------- | :----------------------------------------------------------: |
| map            | 其各个元素的键必须是唯一的（即不能重复），该容器会根据各元素键的大小，默认进行升序排序（调用 std::less<T>）。 |
| set            | 各个元素键和值完全相同，且各个元素的值不能重复（保证了各元素键的唯一性）。该容器会自动根据各个元素的键（其实也就是元素值）的大小进行升序排序（调用 std::less<T>）。 |
| multimap       | 和 map 容器唯一的不同在于，multimap 容器中存储元素的键可以重复。 |
| multiset       | 和 set 容器唯一的不同在于，multiset 容器中存储元素的值可以重复（一旦值重复，则意味着键也是重复的）。 |

> ​	C++ 11 还新增了 4 种哈希容器，即 unordered_map、unordered_multimap 以及 unordered_set、unordered_multiset。严格来说，它们也属于关联式容器，但由于哈希容器底层采用的是**哈希表**，而不是红黑树，



## pair

`#include <utility>`

​	make_pair() 函数的返回值（是一个临时对象）作为参数传递给 pair() 构造函数时，其**调用的是移动构造函数**，而不是拷贝构造函数。

​	`<utility>`头文件中除了提供创建 pair 对象的方法之外，还为 pair 对象重载了 <、<=、>、>=、==、!= 这 6 的运算符，其运算规则是：对于进行比较的 2 个 pair 对象，先比较 pair.first 元素的大小，如果相等则继续比较 pair.second 元素的大小。



## map

```c++
template < class Key,                                     // 指定键（key）的类型
           class T,                                       // 指定值（value）的类型
           class Compare = less<Key>,                     // 指定排序规则
           class Alloc = allocator<pair<const Key,T> >    // 指定分配器对象的类型
           > class map;
```

- **键的值既不能重复也不能被修改**，map 容器中存储的各个键值对不仅键的值独一无二，**键的类型也会用 const 修饰**，这意味着只要键值对被存储到 map 容器中，其键的值将不能再做任何修改。

### find(key)

​	在 map 容器中查找键为 key 的键值对，如果成功找到，则返回指向该键值对的双向迭代器；反之，则返回和 end() 方法一样的迭代器

### lower_bound(key)

​	返回一个指向当前 map 容器中**第一个大于或等于** key 的键值对的双向迭代器

### upper_bound(key)

​	返回一个指向当前 map 容器中**第一个大于** key 的键值对的迭代器

### equal_range(key)

​	该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower_bound() 方法的返回值等价，pair.second 和 upper_bound() 方法的返回值等价。

### operator[] at()

​	[]:获取 修改 **不存在会创建(即便在=右边)** e.g `int x = map["string";]`

​	at不存在会抛出异常

​	除了借助 [ ] 运算符获取 map 容器中指定键对应的值，还可以使用 at() 成员方法。和前一种方法相比，at() 成员方法也需要根据指定的键，才能从容器中找到该键对应的值；不同之处在于，如果在当前容器中查找失败，该方法**不会向容器中添加新的键值对，而是直接抛出 out_of_range 异常。**

### insert

:one: 无需指定插入位置，直接将键值对添加到 map 容器中。

```c++
//1、引用传递一个键值对
pair<iterator,bool> insert (const value_type& val);//左值
//2、以右值引用的方式传递键值对
template <class P>
pair<iterator,bool> insert (P&& val);//右值
```

​	其中，val 参数表示键值对变量，同时该方法会**返回一个 pair 对象**，其中 pair.first 表示一个迭代器，pair.second 为一个 bool 类型变量：

- 如果成功插入 val，则该迭代器指向新插入的 val，bool 值为 true；
- 如果插入 val 失败，则表明当前 map 容器中存有和 val 的键相同的键值对（用 p 表示），此时返回的迭代器指向 p，bool 值为 false。

:two:insert() 指定位置插入新键值对

```c++
//以普通引用的方式传递 val 参数
iterator insert (const_iterator position, const value_type& val);
//以右值引用的方式传递 val 键值对参数
template <class P>
iterator insert (const_iterator position, P&& val);
```

**返回的是迭代器**，而不再是 pair 对象：

- 如果插入成功，insert() 方法会返回一个指向 map 容器中已插入键值对的迭代器；
- 如果插入失败，insert() 方法同样会返回一个迭代器，该迭代器指向 map 容器中和 val 具有相同键的那个键值对。

> ​	即便指定了新键值对的插入位置，**map 容器仍会对存储的键值对进行排序**。也可以说，决定新插入键值对位于 map 容器中位置的，不是 insert() 方法中传入的迭代器，而是新键值对中键的值。

:three:向当前 map 容器中插入其它 map 容器指定区域内的所有键值对

​	拷贝

```c++
template <class InputIterator>
void insert (InputIterator first, InputIterator last);
```

:four:一次向 map 容器中插入多个键值对

```c++
void insert ({val1, val2, ...});
```

### operator[] 和 insert

- **添加元素**

​	insert 效率更高

**[]**

```c++
mymap["STL教程"] = "http://www.cdsy.xyz/computer/programme/java/";
					等价于
typedef map<string, string> mstr;
//1.创建要添加的默认键值对元素
pair<mstr::iterator, bool>res = mymap.insert(mstr::value_type("STL教程", string()));
//2.将新键值对的值赋值为指定的值
res.first->second = "http://www.cdsy.xyz/computer/programme/java/";
```

**insert**

```c++
mymap.insert(mstr::value_type("STL教程", "http://www.cdsy.xyz/computer/programme/java/"));
```

省略了创建临时 string 对象的过程以及析构该对象的过程，同时还省略了调用 string 类重载的赋值运算符

#### emplace 

```c++
template <class... Args>
  pair<iterator,bool> emplace (Args&&... args);
```

**返回值也是一个 pair 对象**，其中 pair.first 为一个迭代器，pair.second 为一个 bool 类型变量：

- 当该方法将键值对成功插入到 map 容器中时，其返回的迭代器指向该新插入的键值对，同时 bool 变量的值为 true；
- 当插入失败时，则表明 map 容器中存在具有相同键的键值对，此时返回的迭代器指向此具有相同键的键值对，同时 bool 变量的值为 false。

#### emplace_hint

```c++
template <class... Args>
  iterator emplace_hint (const_iterator position, Args&&... args);
```

1. 需要**传入一个迭代器作为第一个参数**，指明要插入的位置（新键值对键会插入到该迭代器指向的键值对的前面）；
2. **返回值是一个迭代器**，而不再是 pair 对象。当成功插入新键值对时，返回的迭代器指向新插入的键值对；反之，如果插入失败，则表明 map 容器中存有相同键的键值对，返回的迭代器就指向这个键值对。

### erase clear

```c++
//删除 set 容器中值为 val 的元素
size_type erase (const value_type& val);//返回成功删除的元素个数
//删除 position 迭代器指向的元素
iterator  erase (const_iterator position);//返回值删除元素之后的第一个元素的迭代器
//删除 [first,last) 区间内的所有元素
iterator  erase (const_iterator first, const_iterator last);//返回值删除元素之后的第一个元素的迭代器
```



### 效率

emplace 比 insert 效率高

- 使用 insert() 向 map 容器中插入键值对的过程是，先**创建该键值对**，然后再将该键值对**复制或者移动**到 map 容器中的指定位置；
- 使用 emplace() 或 emplace_hint() 插入键值对的过程是，**直接在 map 容器中的指定位置构造该键值对**。

```c++
class testDemo
{
public:
    testDemo(int num) :num(num) {
        std::cout << "调用构造函数" << endl;
    }
    testDemo(const testDemo& other) :num(other.num) {
        std::cout << "调用拷贝构造函数" << endl;
    }
    testDemo(testDemo&& other) :num(other.num) {
        std::cout << "调用移动构造函数" << endl;
    }
private:
    int num;
};

int main()
{
    //创建空 map 容器
    std::map<std::string, testDemo>mymap;

    cout << "insert():" << endl;//一次构造 2次移动 testDomo -> pair -> map
    mymap.insert({ "http://www.cdsy.xyz/computer/programme/stl/", testDemo(1) });
   
    cout << "emplace():" << endl;
    mymap.emplace( "http://www.cdsy.xyz/computer/programme/stl/:", 1);//一次构造

    cout << "emplace_hint():" << endl;
    mymap.emplace_hint(mymap.begin(), "http://www.cdsy.xyz/computer/programme/stl/", 1);//一次构造
    return 0;
}
```



## multimap

​	**未提供 at() 成员方法，也没有重载 [] 运算符**。

> ​	由于 multimap 容器可存储多个**具有相同键的键值对**，lower_bound()、upper_bound()、equal_range() 以及 count() 成员方法会经常用到。



## set

使用 set 容器存储的各个键值对，要求**键 key 和值 value 必须相等。**

```c++
template< class T,                        // 键 key 和值 value 的类型
          class Compare = less<T>,        // 指定 set 容器内部的排序规则
          class Alloc = allocator<T>      // 指定分配器对象的类型
		> class set;
```

- **自动排序**
- **元素不可修改**
- **元素必须互不相等**

- **未提供 at() 成员函数**，**也未对 [] 运算符进行重载**
- 只能借助 set 容器的迭代器**(双向)**访问 set 容器中存储的元素。



### 自定义类型

​	**全局函数**的形式实现对 < 运算符的重载，还可以使用**成员函数**或者**友元函数**的形式实现。其中，当以成员函数的方式重载 < 运算符时，该**成员函数必须声明为 const 类型**，且**参数也必须为 const 类型**：

```c++
bool operator <(const myString & tempStr) const {
    //以字符串的长度为标准比较大小
    return this->str.length() < tempStr.str.length();
}
```

> 至于参数的传值方式是采用按引用传递还是按值传递，都可以（建议采用按引用传递，效率更高）。

# 修改关联式容器键的值

## map 和 multimap

​	map 和 multimap 容器中元素的键是**无法直接修改**的，C++ STL 标准中明确规定，map 和 multimap 容器用于存储类型为 pair<const K, V> 的键值对。

​	只能**先删除，再添加**

## set 和 multiset

​	C++ STL 标准中并没有用 const 限定 set 和 multiset 容器中存储元素的类型，但也做了其它工作来限制用户修改容器的元素，operator* 返回 const T& ，operator-> 为const成员函数。

​	可以通过 **const_cast 去掉 const 限定** 来修改键的值中非用作排序的成员的值。（强转其实也可以需改😱。但破坏了规定）

```c++
struct Moss
{
    bool operator < (const Moss& other) const {
        return id < other.id;
    }
    int id;
    int height;
};
int main()
{
    std::set<Moss> s;
    s.emplace(1, 15);
    auto it = s.begin();
    //it->height = 200;     error
    //(*it).height = 200;   error
    std::cout << s.begin()->height << std::endl;    //15
    const_cast<Moss&>(*it).height = 200;
    std::cout << s.begin()->height << std::endl;    //200
    int* p = const_cast<int*>(&(it->height));
    *p = 300;
    std::cout << s.begin()->height << std::endl;    //300
    std::cout << "---------------" << std::endl;
    return 0;
}
```

​	再次强调，虽然使用 const_cast 能直接修改 set 或者 multiset 容器中的元素，**但一定不要修改元素的键**！如果要修改，只能采用“先删除，再添加”的方式。另外，不要试图以同样的方式修改 map 或者 multimap 容器中键值对的键，这违反了 C++ STL 标准的规定。

# 4.无序关联式容器

unordered_map、unordered_multimap、unordered_set 以及 unordered_multiset

- **关联式容器**的底层实现采用的树存储结构，更确切的说是**红黑树**结构；
- **无序容器**的底层实现采用的是**哈希表**的存储结构。

​	C++ STL 底层采用哈希表实现无序容器时，会将所有数据存储到一整块连续的内存空间中，并且当数据存储位置发生冲突时，解决方法选用的是“链地址法”（又称“开链法”）。

1. 无序容器内部存储的键值对是无序的，各键值对的存储位置取决于该键值对中的键，
2. 和关联式容器相比，无序容器擅**长通过指定键查找对应的值（平均时间复杂度为 O(1)）**；但对于使用**迭代器遍历**容器中存储的元素，无序容器的执行效率则**不如关联式容器。**

> ​	涉及大量遍历容器的操作，建议首选关联式容器；如果更多的操作是通过键获取对应的值，则应首选无序容器。

## unordered_map

​	unordered_map 容器和 map 容器一样，以键值对（pair类型）的形式存储数据，存储的**各个键值对的键互不相同且不允许被修改。**但由于 unordered_map 容器底层采用的是哈希表存储结构，该结构本身**不具有对数据的排序功能**，所以此容器内部不会自行对存储的键值对进行排序。

​	需包含头文件`#include <unordered_map>`

```c++
template < class Key,                        //键值对中键的类型
           class T,                          //键值对中值的类型
           class Hash = hash<Key>,           //容器内部存储键值对所用的哈希函数
           class Pred = equal_to<Key>,       //判断各个键值对键相同的规则
           class Alloc = allocator< pair<const Key,T> >  // 指定分配器对象的类型
           > class unordered_map;
```

> ​	默认哈希函数只适用于基本数据类型（包括 string 类型），而不适用于自定义的结构体或者类。

operator[] (key) at(key)

[]:访问 修改 不存在创建

at:不存在抛出异常

### 底层实现

[深度剖析C++无序容器的底层实现机制 (cdsy.xyz)](https://www.cdsy.xyz/computer/programme/stl/20210307/cd161510783312009.html)

- STL 标准库通常选用 **vector** 容器存储各个链表的头指针。

- 用“链地址法”（“开链法”）解决数据存储位置发生冲突的哈希表
- 正向迭代器 ++ ++ * == !=

![C++ STL 无序容器存储状态示意图](https://www.cdsy.xyz/d/file/computer/programme/stl/2021-04-23/471669e4007d7e512532448a578d478f.gif)

存储过程:

1. 将该键值对中键的值带入设计好的哈希函数，会得到一个哈希值（一个整数，用 H 表示）；
2. 将 H 和无序容器拥有桶的数量 n 做整除运算（即 H % n），该结果即表示应将此键值对存储到的桶的编号；
3. 建立一个新节点存储此键值对，同时将该节点链接到相应编号的桶上。

### 负载因子

负载因子（load factor） = 容器存储的总键值对 / 桶数

​	用于衡量容器存储键值对的空/满程序，即**负载因子越大，意味着容器越满**，即各链表中挂载着越多的键值对，这无疑会**降低容器查找目标键值对的效率**；反之，负载因子越小，容器肯定越空，但并不一定各个链表中挂载的键值对就越少。

> ​	举个例子，如果设计的哈希函数不合理，使得各个键值对的键带入该函数得到的哈希值始终相同（所有键值对始终存储在同一链表上）。这种情况下，即便增加桶数是的负载因子减小，该容器的查找效率依旧很差。

​	**默认情况下，无序容器的最大负载因子为 1.0。**如果操作无序容器过程中，使得最大复杂因子超过了默认值，则容器会**自动增加桶数，并重新进行哈希**，以此来减小负载因子的值。需要注意的是，此过程**会导致容器迭代器失效**，但指**向单个键值对的引用或者指针仍然有效。**

> ​	所谓迭代器失效，针对的是那些用于表示容器内某个范围的迭代器，由于重哈希会重新调整每个键值对的存储位置，所以容器重哈希之后，之前表示特定范围的迭代器很可能无法再正确表示该范围。但是，重哈希并**不会影响那些指向单个键值对元素的迭代器。**

​	注意的是，在操作 unordered_map 容器过程（尤其是向容器中添加新键值对）中，一旦当前容器的负载因子超过最大负载因子（默认值为 1.0），该容器就**会适当增加桶的数量（通常是翻一倍）**，并自动执行 **rehash()** 成员方法，**重新调整各个键值对的存储位置**（此过程又称“重哈希”），此过程很可能导致之前创建的迭代器失效。

| 成员方法           | 功能                                                         |
| :----------------- | :----------------------------------------------------------- |
| bucket_count()     | 返回当前容器底层存储键值对时，使用桶的数量。                 |
| max_bucket_count() | 返回当前系统中，unordered_map 容器底层最多可以使用多少个桶。 |
| bucket_size(n)     | 返回第 n 个桶中存储键值对的数量。                            |
| bucket(key)        | 返回以 key 为键的键值对所在桶的**编号**。                    |
| load_factor()      | 返回 unordered_map 容器中当前的负载因子。                    |
| max_load_factor()  | **返回或者设置**当前 unordered_map 容器的最大负载因子。      |
| rehash(n)          | 尝试重新调整桶的数量为等于或大于 n 的值。如果 n 大于当前容器使用的桶数，则该方法会是容器重新哈希，该容器新的桶数将等于或大于 n。反之，如果 n 的值小于当前容器使用的桶数，则调用此方法可能没有任何作用。 |
| reserve(n)         | 将容器使用的桶数（bucket_count() 方法的返回值）设置为**最适合存储 n 个元素的桶数**。 |
| hash_function()    | 返回当前容器使用的哈希函数对象。                             |

Example:

```c++
int main()
{
    std::unordered_map<std::string, int> w;
    std::cout << w.bucket_count() << std::endl;//8
    w.reserve(11);//桶数调整为可以存放11个元素
    std::cout << w.bucket_count() << std::endl;//16

    w.emplace("a", 1);
    w.emplace("b", 2);
    w.emplace("c", 3);
    w.emplace("d", 4);
    w.emplace("e", 5);
    w.emplace("f", 6);
    w.emplace("x", 7);
    w.emplace("u", 8);
    w.emplace("z", 9);
    w.emplace("i", 10);
    w.emplace("a",11);
    w.emplace("a",21);

    std::cout << "负载因子:" << w.load_factor() << std::endl;
    auto pfun = w.hash_function();
    std::cout << "key 为 i 的桶编号: " << pfun("i") % w.bucket_count() << std::endl;//手动计算
    std::cout << "key 为 i 的桶编号: " << w.bucket("i") << std::endl;

    for (int i = 0; i < w.bucket_count(); i++) {
        std::cout << "第 " << i << " 个桶的键值对数:  " << w.bucket_size(i) << std::endl;
    }
    std::cout << "---------------" << std::endl;
    return 0;
}
```

### operator[] at()

[]: 获取 修改 不存在添加

at: 获取 修改 不存在抛出异常

1. 当 [ ] 运算符位于赋值号（=）右侧时，则新添加键值对的键为 [ ] 运算符内的元素，其值为键值对要求的值类型的默认值（string 类型默认值为空字符串）；
2. 当 [ ] 运算符位于赋值号（=）左侧时，则新添加键值对的**键**为 [ ] 运算符内的元素，其**值**为赋值号右侧的元素。

### find

成功:返回值要查找的键值对的正向迭代器

失败:返回end()

### insert

同map

> ```c++
> //以普通方式传递 val 参数
> iterator insert ( const_iterator hint, const value_type& val );
> //以右值引用方法传递 val 参数
> template <class P>
>     iterator insert ( const_iterator hint, P&& val );
> ```
>
> ​	insert 指定位置插入（迭代器），即便hint参数指定了新键值对添加到容器中的位置，但该键值对**真正存储的位置**，并不是  参数说了算，最终的存储位置**仍取决于该键值对的键的值。**

### emplace emplace_hint 

同map

> - emplace_hint() 方法还需要传递一个迭代器作为第一个参数，该迭代器表明将新键值对添加到容器中的位置。需要注意的是，新键值对添加到容器中的位置，并不是此迭代器说了算，最终**仍取决于该键值对的键的值。**

### erase clear

```c++
iterator erase ( const_iterator position );//返回删除位置的下一个位置的迭代器
size_type erase ( const key_type& k );//返回成功删除的键值对的数量
iterator erase ( const_iterator first, const_iterator last );//返回被删除的最后一个键值对之后一个位置的迭代器
```

## 自定义类型

哈希函数:自定义一个哈希函数，创建函数对象，重载`operator()`

比较规则::one:使用默认的`less<key>`,重载自定义类型的`operator==`:two:创建函数对象，重载`operator()`

> ​	简单地理解哈希函数，它可以接收一个元素，并通过内部对该元素做再加工，最终会得出一个整形值并反馈回来。需要注意的是，哈希函数只是一个称谓，其本体并不是普通的函数形式，而是一个函数对象类。因此，如果我们想自定义个哈希函数，就需要自定义一个函数对象类。

### Example:

```c++
class Equal_to_Moss;//提前声明 如果只有声明 && 去用该类的成员 会报错

class Moss
{
	friend Equal_to_Moss;//友元类 友元函数 或者 共有方法
public:
	Moss(int id, std::string name) :id(id), name(name) {}

	int getId()const {
		return id;
	}
public:
	//类内重载 operator ==
	bool operator == (const Moss& other) const {
		return id == other.id;
	}
private:
	int id;
	std::string name;
};

//自定义比较规则
class Equal_to_Moss
{
public:
	bool operator()(const Moss& left, const Moss& right) const {
		return left.id == right.id && left.name == right.name;
	}

};

//自定义哈希函数 只能用函数对象
class Hash_Moss
{
public:
	int operator ()(const Moss& it) const {
		return it.getId();
	}
};
// 模板类特化-哈希函数
namespace std {
    template<> struct hash<Moss> {
        size_t operator()(const Moss& m) const{
            return m.getId();
        }
    };
}

int main()
{
	std::unordered_map<Moss, std::string, Hash_Moss> w1;//使用默认的less<Moss>
	std::unordered_map<Moss, std::string, Hash_Moss, Equal_to_Moss> w2;//使用 自定义比较规则

	w1[Moss(1, "1")] = "使用默认的less<Moss>";
	std::cout << w1[Moss(1, "1")] << std::endl;

	w2[Moss(1, "1")] = "使用自定义比较规则";
	std::cout << w2[Moss(1, "1")] << std::endl;
    return 0;
}
```



# 5.容器适配器

​	简单的理解容器适配器，其就是将不适用的序列式容器（包括 vector、deque 和 list）变得适用。即通过封装某个序列式容器，并重新组合该容器中包含的成员函数，使其满足某些特定场景的需要。

> ​	容器适配器本质上还是容器，只不过此容器模板类的实现，利用了大量其它基础容器模板类中已经写好的成员函数。当然，如果必要的话，容器适配器中也可以自创新的成员函数。
>
> ​	STL中的容器适配器，其内部使用的**基础容器并不是固定的**，用户可以在满足特定条件的多个基础容器中自由选择

STL 提供了 3 种容器适配器，分别为 stack 栈适配器、queue 队列适配器以及 priority_queue 优先权队列适配器

| 容器适配器     | 基础容器筛选条件                                             | 默认使用的基础容器 |
| -------------- | ------------------------------------------------------------ | ------------------ |
| stack          | 基础容器需成员函数：**empty() size() back() push_back() pop_back()**          满足条件的基础容器: **vector、deque、list** | deque              |
| queue          | 基础容器需成员函数：**empty() size() front() back() push_back() pop_front()** 满足条件的基础容器: **deque、list** | deque              |
| priority_queue | 基础容器需成员函数：**empty() size() front() push_back() pop_back()**         满足条件的基础容器: **vector、deque** | vector             |

## stack

### 创建



1) 创建一个不包含任何元素的 stack 适配器，并采用默认的 deque 基础容器：

```cpp
std::stack<int> values;
```

2. 指定一个容器

```c++
stack<T,Container=deque<T>>
std::stack<std::string, std::list<int>> values;
```

3. 基础容器来初始化 stack 适配器(只要该容器的类型和 stack 底层使用的基础容器类型相同即可)

```c++
std::list<int> values {1, 2, 3};
std::stack<int,std::list<int>> my_stack (values);
```

## queue



## priority_queue 

`#include <queue>`

```c++
template <typename T,//指定存储元素的具体类型
        typename Container=std::vector<T>,//底层使用的基础容器
        typename Compare=std::less<T> >//评定元素优先级所遵循的排序规则 less大顶堆
class priority_queue{
    //......
}
```

可以使用**普通数组或其它容器中指定范围内的数据**，对 priority_queue 容器适配器进行初始化

```c++
//使用普通数组
int values[]{4,1,3,2};
std::priority_queue<int>copy_values(values,values+4);//{4,2,3,1}

//使用序列式容器
std::array<int,4>values{ 4,1,3,2 };
std::priority_queue<int>copy_values(values.begin(),values.end());//{4,2,3,1}
```

### 自定义排序规则

1. 自定义函数对象 适用于任何情况
2. 如果优先队列存储的是struct/class的对象，重载 operator < 或 operator >,让默认的less<> greater<>变得适用

### 底层实现

[深度剖析priority_queue容器的底层实现 (cdsy.xyz)](https://www.cdsy.xyz/computer/programme/stl/20210307/cd161510785412027.html)

> ​	虽然不使用堆结构，通过编写算法调整 vector 或者 deque 容器中存储元素的次序，也能使其具备 “First in,Largest out” 的特性，但执行效率通常**没有使用堆结构高**。



| 函数                           | 功能                                                         |
| ------------------------------ | ------------------------------------------------------------ |
| make_heap(first,last,comp)     | 选择位于 [first,last) 区域内的数据，并根据 comp 排序规则建立堆，其中 fist 和 last 可以是指针或者迭代器，默认是建立大顶堆。 |
| push_heap(first,last,comp)     | 当向数组或容器中添加数据之后，此数据可能会破坏堆结构，该函数的功能是重建堆。 |
| pop_heap(first,last,comp)      | 将位于序列头部的元素（优先级最高）移动序列尾部，并使[first,last-1] 区域内的元素满足堆存储结构。 |
| sort_heap(first,last,comp)     | 对 [first,last) 区域内的元素进行堆排序，将其变成一个有序序列。 |
| is_heap_until(first,last,comp) | 发现[first,last)区域内的最大堆。                             |
| is_heap(first,last,comp)       | 检查 [first,last) 区域内的元素，是否为堆结构。               |



# 6.迭代器适配器

C++ STL 标准库中迭代器大致分为 5 种类型，分别是**输入迭代器、输出迭代器**、前向迭代器、双向迭代器以及随机访问迭代器

| 名称                                                         | 功能                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 反向迭代器（reverse_iterator）                               | 又称“逆向迭代器”，其内部重新定义了递增运算符（++）和递减运算符（--），专门用来实现对容器的逆序遍历。 |
| 安插型迭代器（inserter或者insert_iterator）                  | 通常用于在容器的任何位置添加新的元素，需要注意的是，此类迭代器不能被运用到元素个数固定的容器（比如 array）上。 |
| 流迭代器（istream_iterator / ostream_iterator） 流缓冲区迭代器（istreambuf_iterator / ostreambuf_iterator） | 输入流迭代器用于从文件或者键盘读取数据；相反，输出流迭代器用于将数据输出到文件或者屏幕上。输入流缓冲区迭代器用于从输入缓冲区中逐个读取数据；输出流缓冲区迭代器用于将数据逐个写入输出流缓冲区。 |
| 移动迭代器（move_iterator）                                  | 此类型迭代器是 C++ 11 标准中新添加的，可以将某个范围的类对象移动到目标范围，而不需要通过拷贝去移动。 |

## :one: reverse_iterator 

反向迭代器

`#include <iterator>`

- 只能选择**双向迭代器**或者**随机访问迭代器**。

- 当**反向迭代器执行 ++** 运算时，底层的**基础迭代器实则在执行 --** 操作，意味着反向迭代器在反向遍历容器；
- 当**反向迭代器执行 --** 运算时，底层的**基础迭代器实则在执行 ++** 操作，意味着反向迭代器在正向遍历容器。

```c++
template <class Iterator>//模板类定义
class reverse_iterator;
```

| 重载运算符  | 功能                                                         |
| ----------- | ------------------------------------------------------------ |
| operator*   | 以引用的形式返回当前迭代器指向的元素。                       |
| operator+   | 返回一个反向迭代器，其指向距离当前指向的元素之后 n 个位置的元素。此操作要求基础迭代器为随机访问迭代器。 |
| operator++  | 重载前置 ++ 和后置 ++ 运算符。                               |
| operator+=  | 当前反向迭代器前进 n 个位置，此操作要求基础迭代器为随机访问迭代器。 |
| operator-   | 返回一个反向迭代器，其指向距离当前指向的元素之前 n 个位置的元素。此操作要求基础迭代器为随机访问迭代器。 |
| operator--  | 重载前置 -- 和后置 -- 运算符。                               |
| operator-=  | 当前反向迭代器后退 n 个位置，此操作要求基础迭代器为**随机访问迭代器**。 |
| operator->  | 返回一个指针，其指向当前迭代器指向的元素。                   |
| operator[n] | 访问和当前反向迭代器相距 n 个位置处的元素。                  |
| base()      | **返回**当前反向迭代器底层所使用的**基础迭代器**             |

Example:

```c++
int main()
{
    std::vector<int> arr{ 1,2,3,4,5,6,7,8,9 };
    std::reverse_iterator<std::vector<int>::iterator> it = arr.rbegin() + 2;
    std::cout << *it << std::endl;//7
    

    std::reverse_iterator<std::vector<int>::iterator> it1 = arr.rbegin();
    std::reverse_iterator<std::vector<int>::iterator> it2 = arr.rend();

    for (; it1 != it2; it1++) {
        std::cout << *it1 << " ";//9 8 7 6 5 4 3 2 1
    }

    std::cout << std::endl;
    return 0;
}
```



## :two: insert_iterator

`#include <iterator>`

插入迭代器适配器

| 迭代器适配器          | 功能                                                         |
| --------------------- | ------------------------------------------------------------ |
| back_insert_iterator  | 在指定容器的**尾部插入新元素**，但前提必须是提供有 **push_back()** 成员方法的容器（包括 vector、deque 和 list）。 |
| front_insert_iterator | 在指定容器的**头部插入新元素**，但前提必须是提供有 **push_front()** 成员方法的容器（包括 list、deque 和 forward_list）。 |
| insert_iterator       | 在容器的指定位置之前插入新元素，前提是该容器必须提供有 **insert()** 成员方法。 |

#### back_insert_iterator

创建back_insert_iterator迭代器

```c++
std::back_insert_iterator<Container> back_it (container);
```

通过back_insert函数获取

```c++
template <class Container>
back_insert_iterator<Container> back_inserter (Container& x);
```

Example:

```c++
std::string arr;
std::back_insert_iterator<std::string> it(arr);//方式1
auto back_it = std::back_inserter(arr);//方式2 back_insert函数
it = '1';
it = '2';
back_it = '3';
back_it = '4';
for (auto& v : arr)
    std::cout << v << " ";//1 2 3 4
```

#### front_insert_iterator 

通过函数**front_inserter()**获取

Example:

```c++
std::list<int> w;
std::front_insert_iterator<std::list<int>> it(w);//1.手动创建
auto front_it = std::front_inserter(w);//2. 通过 front_insert函数返回
it = 4;
it = 3;
front_it = 2;
front_it = 1;
for (auto& value : w) {
    std::cout << value << " ";//1 2 3 4
}
```

#### insert_iterator

STL 标准库中所有容器都提供有 insert() 成员方法，因此 insert_iterator 是唯一**可用于关联式容器**的插入迭代器



```c++
std::insert_iterator<Container> insert_it (container,it);
```

Example:

```c++
std::list<int> w;
std::insert_iterator<std::list<int>> it(w,w.begin());//1.手动创建
auto front_it = std::inserter(w,w.begin());//2. 通过 insert函数返回
it = 4;
it = 3;
front_it = 2;
front_it = 1;
for (auto& value : w) {
    std::cout << value << " ";//4 3 2 1
}
```

**通常和 copy() 函数连用，即作为 copy() 函数的第 3 个参数**

```c++
int main () {
  std::list<int> foo, bar;//foo:1 2 3 4 5
  for (int i=1; i<=5; i++)//bar:10 20 30 40 50
  { foo.push_back(i); bar.push_back(i*10); }

  std::list<int>::iterator it = foo.begin();
  advance(it,3);//4

  std::insert_iterator< std::list<int> > insert_it (foo,it);

  std::copy (bar.begin(),bar.end(),insert_it);
  //1 2 3 10 20 30 40 50 4 5
  std::cout << "foo:";
  for ( std::list<int>::iterator it = foo.begin(); it!= foo.end(); ++it )
	  std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
```

## :three:stream_iterator

流迭代器

`#include <iterator>`

- 将绑定到输入流对象的迭代器称为输入流迭代器（istream_iterator），其可以用来读取输入流中的数据；
- 将绑定到输出流对象的迭代器称为输出流迭代器（ostream_iterator），其用来将数据写入到输出流中。

### istream_iterator

输入迭代器

只能进行 ++p、p++、*p 操作， == 和 != 

​	实际上，输入流迭代器的**底层是通过重载 ++ 运算符实现的**，该运算符**内部会调用operator >>读取数据**。也就是说，假设 iit 为输入流迭代器，则只需要执行 ++iit 或者 iit++，即可读取一个指定类型的元素。

创建

1. **默认构造函数**创建出一个**具有结束标志**的输入流迭代器

```c++
std::istream_iterator<double> eos;
```

2. 创建一个可用来**读取数据的**输入流迭代器

```c++
std::istream_iterator<double> iit(std::cin);
```

> 调用的构造函数中，会**自行尝试去指定流中读取一个指定类型的元素**

3. 拷贝构造 创建一个相同的迭代器

```c++
std::istream_iterator<int> iit2(std::cin);//等待输入(屏幕)
auto iit3 = iit2;
std::cout << *iit2 << " " << *iit3;
input :1
output:1 1
```

Example:

```c++
int main()
{
    std::istream_iterator<int> iit1;
    
    std::istream_iterator<int> iit2(std::cin);//等待输入(屏幕)
    
    while (iit1 != iit2) {//遇到EOF流结束符 结束输入
        std::cout << *iit2 << std::endl;
        iit2++;//继续读取输入
    }
    if (iit1 == iit2) {
        std::cout << "encounter EOF flag (Ctrl + Z)" << std::endl;
    }

    std::cout << std::endl;
    return 0;
}

```

### ostream_iterator

没有默认的构造函数

输出迭代器底层是通过重载赋值（=）运算符实现的，即借助该运算符，每个赋值给输出流迭代器的元素都会被写入到指定的输出流中。

Example:

```c++
std::fstream of(stdout);//文件流
std::ostream_iterator<const char*> oit0(of);
oit0 = "hello world";

int arr[] = { 1,2,3,4 };
std::ostream_iterator<int> oit(std::cout,"-");//屏幕
for (auto& value : arr) {
    oit = value;
}
//输出:hello world1-2-3-4-
std::cout << std::endl;
```

## :four:streambuf_iterator

流缓冲区迭代器

- 输入流缓冲区迭代器（istreambuf_iterator）：从输入流缓冲区中读取字符元素；
- 输出流缓冲区迭代器（ostreambuf_iterator）：将连续的字符元素写入到输出缓冲区中。

> ​	流缓冲区迭代器和流迭代器最大的区别在于，前者仅仅会将元素**以字符的形式**（包括 char、wchar_t、char16_t 及 char32_t 等）读或者写到流缓冲区中，由于不会涉及数据类型的转换，读写数据的速度比后者要快。

### istreambuf_iterator

istreambuf_iterator 输入流缓冲区迭代器的功能是从指定的流缓冲区中读取字符元素。

创建:

1. 默认构造函数，可以创建一个表示结尾的输入流缓冲区迭代器

```c++
std::istreambuf_iterator<char> end_in;
```

2. 指定要读取的流缓冲区

```c++
std::istreambuf_iterator<char> in{ std::cin };
```

3. 传入流缓冲区的地址

```c++
std::istreambuf_iterator<char> in {std::cin.rdbuf()};
```

> - rdbuf() 函数的功能是获取指定流缓冲区的地址
>
> - 无论是传入流缓冲区，还是传入其地址，它们最终构造的输入流缓冲区迭代器是一样的。

Example:

```c++
std::istreambuf_iterator<char> buf_eof;
std::istreambuf_iterator<char> buf_it(std::cin);

std::string buff;
while (buf_eof != buf_it) {
    buff += *buf_it++;
}
std::cout << "begin:" << buff << "end" << std::endl;//从缓冲区中读走了回车'\n'
/*
istreambuf_iterator:输入流缓冲 读走了回车
	123
	^Z
	begin:123 
	end
istream_iterator:输入流 不读回车
	123
	^Z
	begin:123end
*/
```

### ostreambuf_iterator	

ostreambuf_iterator 输出流缓冲区迭代器用于将字符元素写入到指定的流缓冲区中。

和 ostream_iterator 输出流迭代器一样，istreambuf_iterator 迭代器底层也是通过重载赋值（=）运算符实现的

创建:

1. 传递一个流缓冲区对象

```c++
std::ostreambuf_iterator<char> out_it (std::cout);
```

2. 借助 rdbuf()，传递一个流缓冲区的地址

```c++
std::ostreambuf_iterator<char> out_it (std::cout.rdbuf());
```

Example:

```c++
std::string mystring ("Some text here...\n");
std::ostreambuf_iterator<char> out_it (std::cout); // stdout iterator
std::copy ( mystring.begin(), mystring.end(), out_it);
//Some text here...
```

## :five: move_iterator

移动迭代器（C++ 11）

实现以移动而非复制的方式，**将某个区域空间中的元素移动至另一个指定的空间**

> - 移动构造函数是移动**整个容器**，并且会清空容器使其size为0
> - 移动迭代器可以**移动指定区域**到**另一个同类型容器的指定区域**(配合insert)，需要手动erase删除被移动的内存

```c++
template <class Iterator>
class move_iterator;
```

> ​	注意，此基础迭代器的类型虽然没有明确要求，但该模板类中某些成员方法的底层实现，需要此基础迭代器为**双向迭代器或者随机访问迭代器**。也就是说，如果指定的 Iterator 类型仅仅是输入迭代器，则某些成员方法将无法使用。

创建

1. 手动构造

2. 使用make_move_iterator<>()函数

```c++
template <class Iterator>
move_iterator<Iterator> make_move_iterator (const Iterator& it);
```

base() 获取当前使用的迭代器

### Example1:

**移动迭代器适配器**

```c++
int main()
{
    using Iter = std::vector<std::string>::iterator;//定义迭代器类型方便使用
    std::vector<std::string> v1{ "hello ","you ", "are " ,"beautiful! " };
#if 1
    //方式1:手动构造 指定区域
    std::move_iterator<Iter> it1(v1.begin() + 1);
    std::move_iterator<Iter> it2(v1.end() - 1);
    std::vector<std::string> v2{ "Hi " ,"wonderful! " };
    v2.insert(v2.begin() + 1, it1, it2);//移动到v2的第二个位置
#else
    //方式2:使用 make_move_iterator 函数 移动整个容器
    std::move_iterator<Iter> p1 = std::make_move_iterator<Iter>(v1.begin());
    std::move_iterator<Iter> p2 = std::make_move_iterator<Iter>(v1.end());
    std::vector<std::string> v2(p1, p2);//构造方式移动 
#endif

    std::cout << "v1:";
    for (auto& i : v1) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "v2:";
    for (auto& i : v2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "v1.size:" << v1.size() << std::endl;//数据移动了,但大小不变
    std::cout << "v2.size:" << v2.size() << std::endl;//
    //删除被移动的空间
#if 1
    v1.erase(it1.base(), it2.base());//使用base获取基础迭代器
#else
    v1.erase(p1.base(), p2.base());//使用base获取基础迭代器
#endif
    std::cout << "After erase v1-size:" << v1.size() << std::endl;

    std::cout << std::endl;
    return 0;
}
```

方式1输出:

```c++
v1:hello    beautiful!
v2:Hi  you  are  wonderful!
v1.size:4
v2.size:4
After erase v1-size:2
```

方式2输出:

```C++
v1:
v2:hello  you  are  beautiful!
v1.size:4
v2.size:4
After erase v1-size:0
```

> ​	**注意，即便通过移动迭代器将容器中某区域的元素移动到了其他容器中，该区域内仍可能残留有之前存储的元素，但这些元素是不能再被使用的，否则极有可能使程序产生各种其他错误。**

### Example2:

**移动构造:移动整个容器**

```c++
//移动构造
std::vector<std::string> v1{ "hello ","world "};

std::vector<std::string> v2(std::move(v1));//使用移动构造

std::cout << "v1:";
for (auto& i : v1) {
    std::cout << i << " ";
}
std::cout << std::endl << "v2:";
for (auto& i : v2) {
    std::cout << i << " ";
}
std::cout << std::endl;

std::cout << "v1-size:" << v1.size() << std::endl;//0 数据移动 大小清空
std::cout << "v2-size:" << v2.size() << std::endl;//2
```

## :six: 迭代器辅助函数

| 迭代器辅助函数        | 功能                                                         |
| --------------------- | ------------------------------------------------------------ |
| advance(it, n)        | it 表示某个迭代器，n 为整数。该函数的功能是将 it 迭代器前进或后退 n 个位置。 |
| distance(first, last) | first 和 last 都是迭代器，该函数的功能是计算 first 和 last 之间的距离。 |
| begin(cont)           | cont 表示某个容器，该函数可以返回一个指向 cont 容器中第一个元素的迭代器。 |
| end(cont)             | cont 表示某个容器，该函数可以返回一个指向 cont 容器中最后一个元素之后位置的迭代器。 |
| prev(it)              | it 为指定的迭代器，该函数默认可以返回一个指向上一个位置处的迭代器。注意，it 至少为双向迭代器。 |
| next(it)              | it 为指定的迭代器，该函数默认可以返回一个指向下一个位置处的迭代器。注意，it 最少为前向迭代器。 |

### advance

`#include <iterator>`

advance() 函数用于将迭代器前进（或者后退）指定长度的距离，移动迭代器本身

```c++
template <class InputIterator, class Distance>
void advance (InputIterator& it, Distance n);
```

根据 it 类型是否为随机访问迭代器，advance() 函数底层采用了不同的实现机制：

- 当 it 为随机访问迭代器时，由于该类型迭代器支持 p+n 或者 p-n（其中 p 就是一个随机访问迭代器）运算，advance() 函数底层采用的就是 it+n 操作实现的；
- 当 it 为其他类型迭代器时，它们仅支持进行 ++ 或者 -- 运算，这种情况下，advance() 函数底层是通过重复执行 n 个 ++ 或者 -- 操作实现的。

### distance

distance() 函数用于计算两个迭代器表示的范围内包含元素的个数

```c++
template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last);
```

first 和 last 的迭代器类型，直接决定了 distance() 函数底层的实现机制：

- 当 first 和 last 为随机访问迭代器时，distance() 底层直接采用 last - first 求得 [first, last) 范围内包含元素的个数，其时间复杂度为O(1)常数阶；
- 当 first 和 last 为非随机访问迭代器时，distance() 底层通过不断执行 ++first（或者 first++）直到 first==last，由此来获取 [first, last) 范围内包含元素的个数，其时间复杂度为O(n)线性阶。

### 转换

> ​	编译器只支持从 iterator 转换为 const_iterator，从 reverse_iterator 转换为 const_reverse_iterator，但不支持逆向转换

### begin end

begin()和end()参数为容器

```c++
//非 const 修改的容器作为参数，begin() 函数返回的为非 const 类型的迭代器
template <class Container>
auto begin (Container& cont)
//传入 const 修饰的容器，begin() 函数返回的为 const 类型的迭代器
template <class Container>
auto begin (const Container& cont)
```

begin()和end()参数为数组

```c++
template <class T, size_t N>
T* begin (T(&arr)[N]);
```

### prev()和next()

prev()该函数可用来获取一个距离指定迭代器 n 个元素的迭代器。

```c++
template <class BidirectionalIterator>
BidirectionalIterator prev ( BidirectionalIterator it, 
typename iterator_traits<BidirectionalIterator>::difference_type n = 1 );
```

> - **类型只能为双向迭代器或者随机访问迭代器**
>
> - 注意，当 n 为正数时，其返回的迭代器将位于 it 左侧；反之，当 n 为负数时，其返回的迭代器位于 it 右侧。
>
> - prev() 函数自身不会检验新迭代器的指向是否合理，需要我们自己来保证其合理性。

next()用来获取一个距离指定迭代器 n 个元素的迭代器。

```c++
template <class ForwardIterator>
ForwardIterator next (ForwardIterator it, 
typename iterator_traits<ForwardIterator>::difference_type n = 1);
```

> - 当 it 为**前向迭代器**时，n 只能为正数，该函数最终得到的新迭代器位于 it 右侧；
>
> - 当 it 为**双向迭代器或者随机访问迭代器**时，若 n 为正数，则得到的新迭代器位于 it 右侧，反之位于 it 左侧。
> - next() 函数自身也不会检查新迭代器指向的有效性，需要我们自己来保证
