# 元组基本操作

1. `std::make_tuple`: 构造元组
2. `std::get`: 获得元组某个位置的值
3. `std::tie`: 元组拆包



## 运行期索引

`std::get<>` 依赖一个编译期的常量 

```c++
int index = 1;
std::get<index>(t); // error
```





## 合并和遍历

`std::tuple_cat`