# 函数对象

# 1.查找算法

- [x] adjacent_find : 查重==第一个==相邻重复元素,返回首个元素iter
- [x]  binary_search: 二分查找==有序== 返回值bool
- [x]  count: 区间统计某个元素出现的次数
- [x]  count_if: 条件查找-区间统计某个元素出现的次数
- [ ]  equal: 比较
- [ ]  equal_range :区间元素比较
- [x] find:区间查找元素 并返回该位置的迭代器
- [ ]  find_first_of:区间查找第一次出现值
- [x]  find_if : 条件查找 并返回该位置的迭代器
- [ ]  upper_bound:查找最后一个大于等于val的位置
- [ ]  lower_bound: 查找第一个大于等于val的位置
- [x]  search:查找子序列,返回子序列的首个迭代器

```c++
vector<int> v1 = { 1,2,3,4,5,2,2,2,2 };
list<int>  l = { 1,2,3 };
vector<int> v2 = { 2,4,6 };
auto it1 = search(v1.begin(), v1.end(), l.begin(), l.end());
//二元谓词方式
auto it2 = search(v1.begin(), v1.end(), v2.begin(), v2.end(),
                  [](int val1, int val2) {return val1 * 2 == val2; });
```

- [x]  search_n:指定元素的次数查找子序列

```c++
vector<int> v1 = { 1,2,3,4,5,2,2,2,2 };
auto it3 = search_n(v1.begin(), v1.end(),4, 2);
cout << it3 - v1.begin() << endl;//输出index:5
```

# 2.排序和通用算法

排序和通用算法就是用来给容器排序，主要的排序算法主要是有以下14个：

- [x] merge: 归并排序(前提有序)，存于新容器
- [ ] inpace_merge: 归并排序，覆盖原区间
- [x] sort: 排序，更改原容器顺序
- [ ] stable_sort: 排序，保存原容器数据顺序
- [ ] nth_element: 关键字排序
- [ ] partition:范围排序
- [ ] partial_sort:范围排序
- [ ] partial_sort_copy:范围排序外加复制操作
- [ ] stable_partition: 范围排序，保存原容器顺序
- [x] random_shuffle: 随机排序==配合srand()==
- [x] reverse:逆序原容器
- [x] reverse_copy: 逆序容器保存到新容器==(新容器必须有大小)==
- [ ] rotate:移动元素到容器末尾
- [ ] rotate_copy:移动元素到新容器

# 3.删除和替换算法

删除和替换算法一般都会修改容器的存储现状，一般处理删除和替换的算法主要有以下的15种：

- [x] copy: 拷贝函数,==新容器必须要有足够的大小==  可以不同容器

- [x] copy_backward: 从后往前拷贝

```c++
vector<int> arr{ 1,2,3,4,5 };
vector<int> arr2(arr.size());
copy_backward(arr.begin(), arr.begin()+2, arr2.end());
for (auto v : arr2)
    cout << v << " ";//输出0 0 0 1 2
```

- [x] iter_swap: 交换
- [x] remove: 删除指定的val,返回没有指定值的新范围的结束位置==并不是真正删除==
- [x] remove_copy: 删除元素复制到新容器==并不是真正删除==
- [ ] remove_if:条件删除
- [ ] remove_copy_if:条件删除拷贝到新容器
- [x] replace:替换 区间内对某个元素替换
- [ ] replace_copy: 替换，结果放到新容器
- [x] replace_if: 条件替换 
- [ ] replace_copy_if:条件替换，结果另存
- [x] swap: 交换 两个容器
- [x] swap_range:区间交换
- [x] unique:去重,==返回迭代器==指向不包含连续重复项的已修改序列新末尾位置==并不是真正删除==

```c++
vector<int> a1 = { 1,5,5,5,5,2};
vector<int>::iterator it2 = unique(a1.begin(), a1.end());
for (auto v : a1)
    cout << v << " ";	//输出1 5 2 5 5 2 it2指向第二个5
for (auto it = a1.begin(); it != it2; it++)
    cout << *it << " ";	//输出1 5 2
```

- [x]  unique_copy:去重，结果另存

# 4.排列组合算法

**提供计算给定集合按一定顺序的所有可能排列组合 ，主要有以下两个:**

- [x] next_permutation:下一个排序序列的组合

```c++
array<int,3> arr= { 1,2,3 };
do
{
    cout << arr[0] << arr[1] << arr[2] << endl;

} while (next_permutation(arr.begin(), arr.end()));
/*123
  132
  213
  231
  312
  321*/
```

- [x] prev_permutation:上一个排序序列的组合

```c++
array<int, 3> arr = { 3,2,1 };
do
{
    cout << arr[0] << arr[1] << arr[2] << endl;

} while (prev_permutation(arr.begin(), arr.end()));
/*321
  312
  231
  213
  132
  123*/
```

**算术运算算法主要用来做容器的算术运算，使用的时候加上==numeric==头文件，主要有以下4个：**

- [x] accumulate:区间求和      ==注意最后一个参数==

Example1:

```c++
template <class InIt, class T, class Pred>
T accumulate(InIt first, InIt last, T val, Pred op);//加上初始值val

int sumSquare(int init, int value) {
    return init + value * value;
}
int arr[]{ 1,2,3 };
auto ret = std::accumulate(arr, arr + 3, 2, sumSquare);
std::cout << ret << std::endl;//1*1 +2*2 +3*3 + 2 = 16
```

Example2:

```c++
std::string dash_char(std::string init, int value) {
    return std::move(init) + '-' + std::to_string(value);//返回作为第二次加法的init
}
int main()
{
    int arr[]{ 1,2,3 ,4,5 };
    std::string ret = std::accumulate(std::begin(arr) + 1, std::end(arr), 
                                      std::to_string(arr[0]), dash_char);
    std::cout << ret << std::endl;//1-2-3-4-5
    return 0;
}
```

- [ ] partial_sum:相邻元素的和

- [x] inner_product:序列内积运算

```c++
array<int, 5> s1{ 1,2,3,4,5 };
array<int, 5> s2{ 1,1,1,1,1 };
cout << inner_product(s1.begin(), s1.end(), s2.begin(), 0);//输出15
```


- [ ] adjacent_difference:相邻元素的差

# 5.生成和异变算法

生成和一遍算法总共有以下6个下，相对于来说for_each用的相对于来说更多一些:

- [x] for_each:迭代访问

```c++
array<int, 5> s1{ 1,2,3,4,5 };
for_each(s1.begin(), s1.end(), [](int& val) {val += 1; });
for_each(s1.begin(), s1.end(), [](int& val) {cout << val << " "; });
//输出2 3 4 5 6
```

- [x] transform: 搬运容器(==t通过Fu运算后==)到另一个容器中==目标容器要分配空间(不会修改原容器)==

```c++
//重载1
string s = "AaBbCcDd";
string s2(s.size(), '\0');
transform(s.begin(), s.end(), s2.begin(), tolower);
cout << "s =" << s << endl;//输出
//s  =AaBbCcDd
//s2 =aabbccdd

//重载2
vector<int> s{ 1,3,5,7,9 };
vector<int> s2{ 7,4,1,8,5,2 };
vector<int> s3(10);
transform(s.begin(), s.end(), s2.begin(), s3.begin(), [](int a, int b) {return a + b; });
copy(s.begin(), s.end(), ostream_iterator<int>{cout, " "});		cout << endl;//1 3 5 7 9
copy(s2.begin(), s2.end(), ostream_iterator<int>{cout, " "});	cout << endl;//7 4 1 8 5 2
copy(s3.begin(), s3.end(), ostream_iterator<int>{cout, " "});	cout << endl;//8 7 6 15 14 0 0 0 0 0
```

- [x] fill:区间填充方式初始容器
- [ ] fill_n:指定长度填充容器
- [ ] generate_n:填充前n个位置

# 6.关系算法

关系算法类似与条件表达式一样的作用，主要用来判断容器中元素是否相等等运算，主要有以下8个：

- [ ] equal:两容器元素是否都相同
- [ ] includes:是否是包含关系
- [ ] lexicographical_compare:比较两个序列
- [x] max:求最大值 ,比较容器返回容器,比较初始化列表
- [ ] max_element:返回最大值的iterator
- [x] min:求最小值
- [ ]  min_element:求最小值的iterator
- [ ] mismatch:找到第一个不同的位置

# 7.集合算法

==前提有序==

集合算法主要是集合上的一些运算，例如集合加法：并集，集合的减法：差集，还有交集。主要有以下4个：

- [x] set_union:并集

- [x] set_intersection:交集

- [x] set_difference:差集

- [x] set_symmetric_difference:对称差集

```c++
array<int, 5> A{ 1,2,3,4,5 };
array<int, 3> B{ 1,5,9 };
array<int, 10> C={0};
set_union(A.begin(),A.end(),B.begin(),B.end(),C.begin());
for (auto v : C)
    cout << v << " ";
cout << endl;		//输出:1 2 3 4 5 9 0 0 0 0
C.assign(0);
set_intersection(A.begin(),A.end(),B.begin(),B.end(),C.begin());
for (auto v : C)
    cout << v << " ";
cout << endl;		//输出:1 5 0 0 0 0 0 0 0 0
C.assign(0);
set_difference(A.begin(), A.end(), B.begin(), B.end(), C.begin());
for (auto v : C)
    cout << v << " ";
cout << endl;		//输出:2 3 4 0 0 0 0 0 0 0
C.assign(0);
set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(), C.begin());
for (auto v : C)
    cout << v << " ";//输出:2 3 4 9 0 0 0 0 0 0
cout << endl;
```

# 8.堆算法

==less大堆greater小堆== 

堆算法，就是把容器当做堆去操作，主要算法函数只有以下4个：

- [x] is_heap:判断是不是堆 bool

- [x] make_heap:生成一个堆
- [x] pop_heap:出堆
- [x] push_heap:入堆 ==入堆之前要在容器中插入元素==
- [x] sort_heap:堆排序

```c++
vector<int> arr{ 7,4,1,8,11,22,33,5,2,9,6,3,0 };
make_heap(arr.begin(), arr.end());
for (auto v : arr)
{
    cout << v << " ";
}
cout << endl;
arr.push_back(12);
push_heap(arr.begin(), arr.end());
for (auto v : arr)	
{
    cout << v << " ";
}
cout << endl;
cout << endl;

while (!arr.empty())
{
    for (auto v : arr)
        cout << v << " ";
    cout << endl;
    pop_heap(arr.begin(), arr.end());
    arr.pop_back();
}
```
