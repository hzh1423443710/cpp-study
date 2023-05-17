# C

## time

```c++
#include <ctime>
time_t time(time_t *t);
```

返回值：从1970-01-01 00:00:00 到系统当前时间所经过的时间以秒为单位

参数:可以为nullptr,不为nullpr,可将时间戳存储至参数指针中

## ctime

```c++
char* ctime(const time_t *timer);
```

将time_t类型的时间**以字符串形式**转换为当前时间

## localtime

```c++
struct tm *localtime(time_t *seconds);
struct tm {
  int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
  int tm_min;   // 分，范围从 0 到 59
  int tm_hour;  // 小时，范围从 0 到 23
  int tm_mday;  // 一月中的第几天，范围从 1 到 31
  int tm_mon;   // 月，范围从 0 到 11
  int tm_year;  // 自 1900 年起的年数
  int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
  int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
  int tm_isdst; // 夏令时
}
```

将time_t类型的指针转换为tm结构的指针

## clock

```c++
clock_t clock(void);
```

返回程序执行起（一般为程序的开头），**处理器时钟所使用的时间**。

为了获取 CPU 所使用的秒数，通常需要除以`CLOCKS_PER_SEC`

Example:

```c++
#include <ctime>

clock_t start_t, end_t;
start_t = clock(); //clock_t clock(void) 
int i = 0;
while(i < 10000000){i++;}
end_t = clock();
cout << "程序段运行时间为：" << double(end_t - start_t)/CLOCKS_PER_SEC << "s" << endl;
// 运行结果：
// 程序段运行时间为：0.017s
```



# C++

chrono库主要包含了三个概念：duration, time_point 和 clock

## 1.chrono::duration

时间间隔

- duration描述的是一段时间范围，比如10秒钟，两个小时，三个月…

```c++
template <class Rep, class Period = ratio<1> >
class duration;
```

- 通过数值（Rep）+ 单位（Period，即小时，分，秒）来进行表示时间范围，单位通过ratio来进行表示

```c++
#include <ratio>
template <intmax_t N, intmax_t D = 1>
class ratio;
```

- N为分子，D为分母，以N/D秒表示单位，如`std::ratio<60,1>`或`std::ratio<60>`为一分钟，`std::ratio<1,1000>`为毫秒

```c++
std::chrono::duration<double, ratio<60,1>>  sec(1);     //一分钟
std::chrono::duration<double,ratio<60*60,1>>  hour(1);	//一小时
```

- 为了方便使用，在ratio头文件中定义了**常用比率的别名**：

```c++
typedef ratio<1,       1000000000000000000> atto;
typedef ratio<1,         1000000000000000> femto;
typedef ratio<1,             1000000000000> pico;
typedef ratio<1,                1000000000> nano;
typedef ratio<1,                  1000000> micro;
typedef ratio<1,                     1000> milli;
typedef ratio<1,                      100> centi;
typedef ratio<1,                        10> deci;
typedef ratio<                       10, 1> deca;
typedef ratio<                     100, 1> hecto;
typedef ratio<                     1000, 1> kilo;
typedef ratio<                  1000000, 1> mega;
typedef ratio<               1000000000, 1> giga;
typedef ratio<            1000000000000, 1> tera;
typedef ratio<         1000000000000000, 1> peta;
typedef ratio<       1000000000000000000, 1> exa;
```

- 在chrono库定义了如下的**常用时间单位**：

```c++
typedef duration<int64_t, nano>     nanoseconds;
typedef duration<int64_t, micro>    microseconds;
typedef duration<int64_t, milli>    milliseconds;
typedef duration<int64_t>		   seconds;
typedef duration<int, ratio< 60>>   minutes;
typedef duration<int, ratio<3600>>  hours;
```

### **count**

通过使用**内部函数cout**，我们可以得到这一段时间的**数值**

Example:

```c++
std::chrono::seconds sec(55);
std::chrono::duration<double,std::ratio<60*60,1>> hour(24);
std::chrono::duration<unsigned,std::ratio<60,1>> min(30);

std::cout << sec.count() << "s\n";      // 55s
std::cout << hour.count() << "h\n";     // 24h
std::cout << min.count() << "min\n";    // 30min
```

### 运算

```c++
std::chrono::seconds sec1(60);  // 60s
std::chrono::minutes min1(60);  // 60min
std::chrono::hours hour1(2);    // 2h
// 减运算
std::chrono::seconds ret = min1 - sec1;
std::cout << ret.count() << "s\n";  // 3540s
ret = hour1 - min1;
std::cout << ret.count() << "s\n";  // 3600s
ret = hour1 - sec1;
std::cout << ret.count() << "s\n";  // 7140s

// 赋值
// assignment operator 只能向低 ratio方向 
std::chrono::minutes min2 = hour1;  // hours -> minutes
std::chrono::seconds sec2 = hour1;  // hours -> seconds
std::cout << "After `hour1` is assigned to `min2`, min2 = " << min2.count() << "min\n"; // 120
std::cout << "After `sec1` is assigned to `sec2`, sec2 = " << sec2.count() << "s\n";  // 7200  
```

### 时间单位转换

为了方便我们对于不同单位时间的转化，chrono库提供了**duration_cast类型转换函数模板**。

```c++
template <class ToDuration, class Rep, class Period>
constexpr ToDuration duration_cast (const duration<Rep,Period>& dtn);
```

Example:

```c++
std::chrono::seconds sec1(60);  // 60s
std::chrono::minutes min1(60);  // 60min
std::chrono::hours hour1(2);    // 2h

// Use:duration_cast<>() 向高ratio 低ratio 转换都支持
// hours -> seconds  
std::chrono::seconds var1 =  std::chrono::duration_cast<std::chrono::seconds>(hour1);
std::cout << "variable `hour1` convert to seconds : " << var1.count() << "s\n"; // 7200s
// seconds -> minutes
std::chrono::minutes var2 =  std::chrono::duration_cast<std::chrono::minutes>(sec1);
std::cout << "variable `sec1` convert to minutes : " << var2.count() << "min\n"; // 1min
```



## 2.chrono::time_point

时间点 时刻

​	通过一个相对epoch的时间间隔duration来实现，epoch就是1970-1-1时刻，对于同一个时钟来说，所有的time_point的epoch都是固定的。这个类可以与标准库ctime结合起来显示时间，ctime内部的time_t类型就是代表这个秒数。

```c++
template<typename _Clock, typename _Dur = typename _Clock::duraion>
class time_point{};
```

第一个参数:当前计时使用的时钟，可选为“system_colck”、“steady_colck”、“high_resolution_clock”或者是自定义的时钟类

第二个参数:时间间隔，**默认为使用的时钟相同的间隔** 不同的时钟有不同的duration(内部维护)



### time_since_epoch

和C语言中`time()`函数相同，返回从1970-01-01 00:00:00 到系统当前时间**所经过的时间**，以秒为单位。

```c++
std::chrono::system_clock::time_point today = std::chrono::system_clock::now(); // 获取当前时刻

std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(today.time_since_epoch());
std::cout << "C++ Style : " << sec.count() << "s\n";
std::cout << "C Style : " << time(nullptr) << "s\n";
// C++ Style : 1682922365s
// C Style : 1682922365s
```



## 3.chrono::clock

时钟

clock包含`system_clock`, `steady_clock `和 `high_resolution_clock`

### system_clock

系统时钟

**now()**		 : 获取当前时刻 time_point
**to_time_t()**   : time_point 转换为 time_t类型
**from_time_t()** : 从 time_t 类型转换为 time_point 类型

Example:

```c++
time_t timestamp = time(nullptr);
// time_t -> time_point
std::chrono::system_clock::time_point today = std::chrono::system_clock::from_time_t(timestamp);
std::cout << std::chrono::duration_cast<std::chrono::seconds>(today.time_since_epoch()).count() 
    << "s\n";

today = std::chrono::system_clock::now();// 获取当前时刻
using Days = std::chrono::duration<int,std::ratio<24*60*60>>;
auto tomorrow = today + Days(1);		// 明天的当前时刻

time_t tt;
// time_point -> time_t
tt = std::chrono::system_clock::to_time_t(today);
std::cout << "Today is\t" << std::ctime(&tt);	// Today is        Mon May  1 14:45:09 2023
tt = std::chrono::system_clock::to_time_t(tomorrow);
std::cout << "Tomorrow is\t" << std::ctime(&tt);// Tomorrow is     Tue May  2 14:46:42 2023
```



### steady_clock

steady_clock专门用于**计算时间差**的工具，steady_clock 类只有一个**静态函数now()**,用于获取当前的时间

```c++
auto start = std::chrono::steady_clock::now();

for(int i = 0; i < 1000000000;i++) {}

auto end = std::chrono::steady_clock::now();

auto diff = end - start;
// 转为double
std::cout << "duration = " << std::chrono::duration_cast<std::chrono::duration<double>>(diff).count() <
    < "s\n"; 
// duration = 0.351719s
```



### high_resolution_clock

high_resolution_clock是系统可用的**最高精度的时钟**。实际上high_resolution_clock只不过是system_clock或者steady_clock的typedef



