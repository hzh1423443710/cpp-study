### 初始化列表

- **调用顺序只与成员的声明顺序有关**

```c++
class People
{
public:
    People(const string &name) : m_name(name), m_len(m_name.size()) {} // error 也可以更改成员的声明顺序 也可以m_len(name.size())
    People(const char *name) : m_name(name == NULL ? "" : name), m_len(name == NULL ? 0 : strlen(name)) {}

    int m_len;     //先初始化
    string m_name; //后初始化
};
void test2()
{
    People peo("Frank");
    cout << peo.m_name << "," << peo.m_len << endl;//Frank 5
    People peo2(string{"hello world"});
    cout << peo2.m_name << "," << peo2.m_len << endl;//hello world 4207208
}
```

 `People(const string &name) : m_name(name), m_len(m_name.size()) {}`会先初始化m_len,但m_name还未初始化