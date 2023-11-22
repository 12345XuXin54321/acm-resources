# STL

## 简介

STL是在c++中使用非常广泛的一个库，里面包含了许多的常用的容器和算法。使用STL，可以简化代码，减少写代码的时间，把重点放在算法的实现上。

一般来说，可以添加这两行来使用STL。
```cpp
#include <bits/stdc++.h>
using namespace std;
```
不过 `#include <bits/stdc++.h>` **不是**标准C++的头文件，而是GNU ISO C++的头文件，一般只有 `gcc` 和 `clang` 支持，**大部分**的oj和竞赛**也支持**，具体要看oj的官方说明。

`using namespace std;` 在平常写代码的时候用的话，容易造成命名的冲突。用的话要注意，变量名、函数名不要取STL里面有的名字。如果不用的话，使用STL里的库时要添加限定名 `std::` ，比如 `std::vector<int> vec;` 和 `std::cout << "hello world!" << std::endl;`。

接下来的讲解中，会说明这个用法的复杂度，还有所需要包含的头文件和最少需要的C++版本。


## 容器的使用

### vector
* 介绍

vector是封装后的顺序存储的大小可变的数组。

简单来说可以当作数组，数据是连续储存的。可以用下标访问。
* 复杂度

* 头文件
```cpp
#include <vector>
```
* 用法
```cpp
#include <vector>
#include <iostream>
using namespace std;
int main()
{
    // 定义vector时需要指定要存储的变量的类型
    // 格式为 vector<类型> 变量名;
    vector<int> vec;

    // 向末尾添加元素
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // 访问、更改元素
    cout << vec[0] << "\n";
    cout << vec[1] << "\n";

    vec[1] = 100;
    cout << vec[1] << "\n";

    // 遍历元素，需要C++11
    // 还有一种遍历的方法只需要C++98，等一下会提到
    for(auto n : vec)
    {
        cout << n << " ";
    }
    cout << endl;

    // 删除末尾的元素
    vec.pop_back();

    for(auto n : vec)
    {
        cout << n << " ";
    }
    cout << endl;

    cout << vec.size() << endl;
    // 清空vector
    vec.clear();
    cout << vec.size() << endl;
}
```
* 输出
<pre>
10
20
100
10 100 30 
10 100 
2
0
</pre>

### list
* 介绍

list是链表（一般是双向链表），可以以 $O(1)$ 的复杂度进行插入和删除操作（即花费常数的时间）。但是，链表的数据不是连续存放的，因此不能用下标访问。
* 复杂度

* 头文件
```cpp
#include <list>
```
* 用法
```cpp
#include <list>
#include <iostream>
using namespace std;
int main()
{
    // 定义list时需要指定要存储的变量的类型
    // 格式为 list<类型> 变量名;
    list<int> l;

    // 向末尾添加元素
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);

    // 遍历元素，同vector，需要C++11
    for(auto n : l)
    {
        cout << n << " ";
    }
    cout << endl;

    //向开头添加元素
    l.push_front(44);
    l.push_front(55);

    for(auto n : l)
    {
        cout << n << " ";
    }
    cout << endl;

    // 删除末尾的元素
    l.pop_back();

    for(auto n : l)
    {
        cout << n << " ";
    }
    cout << endl;

    // 更改、插入、删除元素需要使用迭代器
    // auto实际为list<int>::iterator
    auto itor = l.begin();
    itor++;
    cout << *itor << endl;
    
    // 更改元素
    *itor = 2333;
    for(auto n : l)
    {
        cout << n << " ";
    }
    cout << endl;

    // 插入元素
    // 在迭代器的前面插入元素
    l.insert(itor, 1000);
    for(auto n : l)
    {
        cout << n << " ";
    }
    cout << endl;

    // 删除元素
    l.erase(itor);
    for(auto n : l)
    {
        cout << n << " ";
    }
    cout << endl;

    cout << l.size() << endl;
    // 清空list
    l.clear();
    cout << l.size() << endl;
}
```
* 输出
<pre>
10 20 30 
55 44 10 20 30 
55 44 10 20 
44
55 2333 10 20 
55 1000 2333 10 20 
55 1000 10 20 
4
0
</pre>

### queue
* 介绍

queue是队列，满足先进先出（FIFO）的数据结构，即最先进入的元素最先弹出。
* 复杂度

* 头文件
```cpp
#include <queue>
```
* 用法
```cpp
#include <queue>
#include <iostream>
using namespace std;
int main()
{
    queue<int> q;
    // 向队尾插入元素
    q.push(11);
    q.push(22);
    q.push(33);
    q.push(44);

    // 访问队头元素
    cout << q.front() << endl;
    // 访问队尾元素
    cout << q.back() << endl;

    // 弹出队头元素
    q.pop();
    cout << q.front() << endl;
}
```
* 输出
<pre>
11
44
22
</pre>

### stack
* 介绍

stack是栈，和队列相反，stack是满足先进后出（FILO）的数据结构，即最先进入的元素最后弹出
* 复杂度

* 头文件
```cpp
#include <stack>
```
* 用法
```cpp
#include <stack>
#include <iostream>
using namespace std;
int main()
{
    stack<int> s;
    // 添加元素
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    // 访问栈顶元素
    cout << s.top() << endl;

    // 弹出栈顶元素
    s.pop();
    cout << s.top() << endl;
}
```
* 输出
<pre>
4
3
</pre>

### string
* 介绍

和c风格的字符串（char*）有所不同，string是c++风格的字符串。string是std里的一个类，里面的数据是顺序储存的。
* 复杂度

* 头文件
```cpp
// 注意不是 #include <string.h>
#include <string>
```
#### 字符串拼接
* 用法
```cpp
#include <string>
#include <iostream>
using namespace std;
int main()
{
    string str = "aaabbb";

    // 字符串拼接
    string str_2 = "ccc";
    cout << str + str_2 << "\n"
         << str_2 + str << endl;

    char c = 'd';
    cout << str + c << endl;
    cout << c + str << endl;

    cout << str + "eeee" << "\n"
         << str + 'f' << endl;
    cout << "eeee" + str << "\n"
         << 'f' + str << endl;

    // 编译错误
    // cout << "aaaa" + "bbbbb" << endl;
}
```
* 输出
<pre>
aaabbbccc
cccaaabbb
aaabbbd
daaabbb
aaabbbeeee
aaabbbf
eeeeaaabbb
faaabbb
</pre>

#### 输入单个字符串
* 用法
```cpp
#include <string>
#include <iostream>
using namespace std;
int main()
{
    string str;
    cin >> str;
    cout << str << endl;
}
```
* 输入 1
<pre>
aaa
</pre>
* 输出 1
<pre>
aaa
</pre>
---
* 输入 2
<pre>
aaa bbb
</pre>
* 输出 2
<pre>
aaa
</pre>

#### 输入一行
* 用法
```cpp
#include <string>
#include <iostream>
using namespace std;
int main()
{
    string str;
    getline(cin, str);
    cout << str << endl;
}
```
* 输入
<pre>
aaa bbb
</pre>
* 输出
<pre>
aaa bbb
</pre>


### 小总结

#### 遍历容器(c++98)
需要用到迭代器
```cpp
#include <list>
#include <iostream>
using namespace std;
int main()
{
    list<int> l({1, 2, 3, 4});
    for (list<int>::iterator itor = l.begin();
         itor != l.end();
         itor++)
    {
        cout << *itor << endl;
    }
}
```
#### 遍历容器(c++11)
```cpp
#include <list>
#include <iostream>
using namespace std;
int main()
{
    list<int> l({1, 2, 3, 4});
    for (auto n : l)
    {
        cout << n << endl;
    }
}
```
#### 迭代器
iterator，即迭代器，一般是用来访问**stl**容器中的元素。不同容器的迭代器支持的操作也不一样。
```cpp
#include <list>
#include <iostream>
using namespace std;
int main()
{
    list<int> l({1, 2, 3, 4});
    // 获取开头的迭代器
    auto itor_begin = l.begin();
    // 获取结尾的迭代器
    // 注意，这是最后一个元素之后的元素
    auto itor_end = l.end();

    // 访问元素
    cout << *itor_begin << endl;

    // 修改元素
    *itor_begin = 10;

    // 迭代器自增
    itor_begin++;

    // 迭代器比较
    if(itor_begin == itor_end)
    {
        cout << "相同" << endl;
    }
    else
    {
        cout << "不相同" << endl;
    }
}
```
#### 构造函数
stl的容器有些有多种的构造函数，如果希望容器中有初值，可以使用构造函数。不同的容器可能会有不同的构造函数。
```cpp
#include <list>
#include <iostream>
using namespace std;
int main()
{
    // 需要c++11
    list<int> l1({1, 2, 3, 4});

    // c++98
    list<int> l2(l1.begin(), l1.end());

    // c++98
    list<int> l3(l2);
}
```
### set

* 介绍

* 复杂度

* 头文件
```cpp
```
* 用法
```cpp
```
* 输出
<pre>
</pre>

### map

* 介绍
* 复杂度

* 头文件
```cpp
```
* 用法
```cpp
```
* 输出
<pre>
</pre>

### priority_queue

* 介绍
* 复杂度

* 头文件
```cpp
```
* 用法
```cpp
```
* 输出
<pre>
</pre>

### mulitset

* 介绍
* 复杂度

* 头文件
```cpp
```
* 用法
```cpp
```
* 输出
<pre>
</pre>

### unordered_map

* 介绍
* 复杂度

* 头文件
```cpp
```
* 用法
```cpp
```
* 输出
<pre>
</pre>

### 容器的嵌套使用

## 算法

## 参考
* https://zh.cppreference.com/