# Algorithm

[C++ Standard Library Algorithms Visual Overview | hacking C++ (hackingcpp.com)](https://hackingcpp.com/cpp/std/algorithms.html)

## 1.查找算法

- [ ] adjacent_find : 查重==第一个==相邻重复元素,返回首个元素iter
- [ ]  binary_search: 二分查找==有序== 返回值bool
- [ ]  count: 区间统计某个元素出现的次数
- [ ]  count_if: 条件查找-区间统计某个元素出现的次数
- [ ]  equal: 比较
- [ ]  equal_range :区间元素比较
- [ ] find:区间查找元素 并返回该位置的迭代器
- [ ]  find_first_of:区间查找第一次出现值
- [ ]  find_if : 条件查找 并返回该位置的迭代器
- [ ]  upper_bound:查找最后一个大于等于val的位置
- [ ]  lower_bound: 查找第一个大于等于val的位置
- [ ]  search:查找子序列,返回子序列的首个迭代器

- [ ] search_n:指定元素的次数查找子序列

  

## 2.排序和通用算法

排序和通用算法就是用来给容器排序，主要的排序算法主要是有以下14个：

- [ ] merge: 归并排序(前提有序)，存于新容器
- [ ] inpace_merge: 归并排序，覆盖原区间
- [ ] sort: 排序，更改原容器顺序
- [ ] stable_sort: 排序，保存原容器数据顺序
- [ ] nth_element: 关键字排序
- [ ] partition:范围排序
- [ ] partial_sort:范围排序
- [ ] partial_sort_copy:范围排序外加复制操作
- [ ] stable_partition: 范围排序，保存原容器顺序
- [ ] random_shuffle: 随机排序==配合srand()==
- [ ] reverse:逆序原容器
- [ ] reverse_copy: 逆序容器保存到新容器==(新容器必须有大小)==
- [ ] rotate:移动元素到容器末尾
- [ ] rotate_copy:移动元素到新容器

## 3.删除和替换算法

删除和替换算法一般都会修改容器的存储现状，一般处理删除和替换的算法主要有以下的15种：

- [ ] copy: 拷贝函数,==新容器必须要有足够的大小==  可以不同容器

- [ ] copy_backward: 从后往前拷贝

- [ ] iter_swap: 交换
- [ ] remove: 删除指定的val,返回没有指定值的新范围的结束位置==并不是真正删除==
- [ ] remove_copy: 删除元素复制到新容器==并不是真正删除==
- [ ] remove_if:条件删除
- [ ] remove_copy_if:条件删除拷贝到新容器
- [ ] replace:替换 区间内对某个元素替换
- [ ] replace_copy: 替换，结果放到新容器
- [ ] replace_if: 条件替换 
- [ ] replace_copy_if:条件替换，结果另存
- [ ] swap: 交换 两个容器
- [ ] swap_range:区间交换
- [ ] unique:去重,==返回迭代器==指向不包含连续重复项的已修改序列新末尾位置==并不是真正删除==

- [ ]  unique_copy:去重，结果另存



## 4.排列组合算法

**提供计算给定集合按一定顺序的所有可能排列组合 ，主要有以下两个:**

- [ ] next_permutation:下一个排序序列的组合

- [ ] prev_permutation:上一个排序序列的组合

**算术运算算法主要用来做容器的算术运算，使用的时候加上==numeric==头文件，主要有以下4个：**

- [ ] accumulate:区间求

- [ ] partial_sum:相邻元素的和

- [ ] inner_product:序列内积运算


- [ ] adjacent_difference:相邻元素的差

5.生成和异变算法

生成和一遍算法总共有以下6个下，相对于来说for_each用的相对于来说更多一些:

- [ ] for_each:迭代访问

- [ ] transform: 搬运容器(==t通过Fu运算后==)到另一个容器中==目标容器要分配空间(不会修改原容器)==

- [ ] fill:区间填充方式初始容器
- [ ] fill_n:指定长度填充容器
- [ ] generate_n:填充前n个位置



## 6.关系算法

关系算法类似与条件表达式一样的作用，主要用来判断容器中元素是否相等等运算，主要有以下8个：

- [ ] equal:两容器元素是否都相同
- [ ] includes:是否是包含关系
- [ ] lexicographical_compare:比较两个序列
- [ ] max:求最大值 ,比较容器返回容器,比较初始化列表
- [ ] max_element:返回最大值的iterator
- [ ] min:求最小值
- [ ]  min_element:求最小值的iterator
- [ ] mismatch:找到第一个不同的位置



## 7.集合算法

==前提有序==

集合算法主要是集合上的一些运算，例如集合加法：并集，集合的减法：差集，还有交集。主要有以下4个：

- [ ] set_union:并集

- [ ] set_intersection:交集

- [ ] set_difference:差集

- [ ] set_symmetric_difference:对称差集



## 8.堆算法

==less大堆greater小堆== 

堆算法，就是把容器当做堆去操作，主要算法函数只有以下4个：

- [ ] is_heap:判断是不是堆 bool

- [ ] make_heap:生成一个堆
- [ ] pop_heap:出堆
- [ ] push_heap:入堆 ==入堆之前要在容器中插入元素==
- [ ] sort_heap:堆排序
