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
    // 格式为 vector<类型> 变量名(初始大小);
    vector<int> vec(5);

    // 向末尾添加元素
    vec.push_back(10);
    vec.push_back(20);

    // 访问、更改元素
    cout << vec[0] << " " << vec[1] << "\n"
         << vec[5] << " " << vec[6] << "\n";

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
0 0
10 20
100
0 100 0 0 0 10 20 
0 100 0 0 0 10 
6
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

set是元素不重复的集合，里面的数据是有序的，可以以对数的复杂度进行搜索、插入和删除。通常以红黑树实现。
* 复杂度

搜索、插入和删除操作$O(N \cdot logN)$
* 头文件
```cpp
#include <set>
```
* 用法
```cpp
#include <set>
#include <iostream>
using namespace std;
void print_set(set<int>& s)
{
    for(auto n : s)
    {
        cout << n << " ";
    }
    cout << "\n";
}
int main()
{
    set<int> s;

    // 插入元素
    s.insert(11);
    s.insert(22);
    s.insert(33);
    s.insert(33);
    s.insert(44);

    print_set(s);

    // 获取元素的个数
    cout << s.count(33) << endl;

    // 查找元素
    auto itor = s.find(44);
    if(itor != s.end())
    {
        cout << "找到" << *itor << endl;
    }
    else
    {
        cout << "没找到" << endl;
    }

    // 删除元素
    s.erase(22);
    print_set(s);
}
```
* 输出
<pre>
11 22 33 44 
1
找到44
11 33 44 
</pre>

* 使用自定义类型
```cpp
#include <set>
#include <iostream>
struct my_type
{
    int a, b;
    my_type() {}
    my_type(int ia, int ib)
    {
        a = ia, b = ib;
    }

    // 需要重载小于号
    bool operator<(const my_type &r) const
    {
        return a < r.a || (a == r.a && b < r.b);
    }
};
using namespace std;
int main()
{
    set<my_type> s;
    s.insert(my_type(1, 2));
    s.insert(my_type(33, 11));
    s.insert(my_type(-44, 22));
    s.insert(my_type(33, 11));
    s.insert(my_type(33, 22));

    for (auto d : s)
    {
        cout << d.a << " " << d.b << "\n";
    }
}
```
* 输出
<pre>
-44 22
1 2
33 11
33 22
</pre>

* 使用自定义比较函数
```cpp
#include <set>
#include <iostream>
using namespace std;
struct my_type
{
    int a, b;
    my_type() {}
    my_type(int ia, int ib)
    {
        a = ia, b = ib;
    }
};
// 需要比较的结构体
struct cmp
{
    // 重载括号
    bool operator()(const my_type &l, const my_type &r) const
    {
        return l.a > r.a || (l.a == r.a && l.b > r.b);
    }
};
int main()
{
    set<my_type, cmp> s;
    s.insert(my_type(1, 2));
    s.insert(my_type(33, 11));
    s.insert(my_type(-44, 22));
    s.insert(my_type(33, 11));
    s.insert(my_type(33, 22));

    for (auto d : s)
    {
        cout << d.a << " " << d.b << "\n";
    }
}
```
* 输出
<pre>
33 22
33 11
1 2
-44 22
</pre>

### multiset

* 介绍

可以有多个相同元素的set
* 复杂度

同set
* 头文件
```cpp
#include <set>
```
* 用法
```cpp
#include <set>
#include <iostream>
using namespace std;
void print_set(multiset<int>& s)
{
    for(auto n : s)
    {
        cout << n << " ";
    }
    cout << "\n";
}
int main()
{
    multiset<int> s;

    // 插入元素
    s.insert(11);
    s.insert(22);
    s.insert(33);
    s.insert(33);
    s.insert(44);

    print_set(s);

    // 获取元素的个数
    cout << s.count(33) << endl;

    // 删除元素
    s.erase(33);
    print_set(s);
}
```
* 输出
<pre>
11 22 33 33 44 
2
11 22 44 
</pre>

### map

* 介绍
map是映射，可以提供键（key）到数据的映射。在map中，键是有序且唯一的。底层实现一般是红黑树。
* 复杂度

搜索、插入和删除操作$O(N \cdot logN)$
* 头文件
```cpp
#include <map>
```
* 用法
```cpp
#include <map>
#include <iostream>
using namespace std;
int main()
{
    // 从int映射到string
    map<int, string> m;

    // 添加映射
    m[1] = "Mon";
    m[2] = "Tues";
    m[3] = "Wed";
    m[4] = "Thur";
    m[5] = "Fir";

    // 访问
    cout << "今天是" << m[2] << endl;

    // 遍历的时候，p是键值对
    for (auto p : m)
    {
        cout << p.first << " " << p.second << "\n";
    }

    // 删除元素
    m.erase(3);

    for (auto itor = m.begin(); itor != m.end(); itor++)
    {
        cout << (*itor).first << " " << (*itor).second << "\n";
    }
}
```
* 输出
<pre>
今天是Tues
1 Mon
2 Tues
3 Wed
4 Thur
5 Fir
1 Mon
2 Tues
4 Thur
5 Fir
</pre>

* 使用自定义类型
自定义类型作为key是要重载小于号
```cpp
#include <map>
#include <iostream>
using namespace std;
struct my_type
{
    int a, b;
    my_type() {}
    my_type(int ia, int ib)
    {
        a = ia, b = ib;
    }

    // 需要重载小于号
    bool operator<(const my_type &r) const
    {
        return a < r.a || (a == r.a && b < r.b);
    }
};

struct my_type_2
{
    int a, b;
    my_type_2() {}
    my_type_2(int ia, int ib)
    {
        a = ia, b = ib;
    }
};

int main()
{
    map<my_type, my_type_2> m;
    m[my_type(1, 2)] = my_type_2(8, 3);
    m[my_type(12, 2)] = my_type_2(21, 13);
    m[my_type(-1, -2)] = my_type_2(7, 43);
    m[my_type(22, 22)] = my_type_2(2, 43);
    m[my_type(1, 2)] = my_type_2(22, 3);

    for (auto p : m)
    {
        cout << p.first.a << " " << p.first.b << " -> "
             << p.second.a << " " << p.second.b << "\n";
    }
}
```
* 输出
<pre>
-1 -2 -> 7 43
1 2 -> 22 3
12 2 -> 21 13
22 22 -> 2 43
</pre>

### unordered_map

* 介绍

利用hash的map，有不重复的键。元素在容器内部没有按特定顺序排序，而是利用哈希放到对应的桶里。
* 复杂度

没有hash冲突的时候，搜索、插入、删除时间复杂度为$O(1)$
* 头文件
```cpp
#include <unordered_map>
```
* 用法
```cpp
#include <unordered_map>
#include <iostream>
using namespace std;
int main()
{
    // 从int映射到string
    unordered_map<int, string> m;

    // 添加映射
    m[1] = "Mon";
    m[2] = "Tues";
    m[3] = "Wed";
    m[4] = "Thur";
    m[5] = "Fir";

    // 访问
    cout << "今天是" << m[2] << endl;

    // 遍历的时候，p是键值对
    for (auto p : m)
    {
        cout << p.first << " " << p.second << "\n";
    }

    // 删除元素
    m.erase(3);

    for (auto itor = m.begin(); itor != m.end(); itor++)
    {
        cout << (*itor).first << " " << (*itor).second << "\n";
    }
}
```
* 输出
<pre>
今天是Tues
5 Fir
4 Thur
3 Wed
2 Tues
1 Mon
5 Fir
4 Thur
2 Tues
1 Mon
</pre>

* 使用自定义类型
自定义类型需要定义hash函数，和判断相等的函数
```cpp
#include <unordered_map>
#include <iostream>
using namespace std;
struct my_type
{
    int a, b;
    my_type() {}
    my_type(int ia, int ib)
    {
        a = ia, b = ib;
    }
    // 需要判断相等，重载==
    bool operator==(const my_type &r) const
    {
        return a == r.a && b == r.b;
    }
};
// 定义结构体，重载括号
struct my_hash
{
    size_t operator()(const my_type &c) const
    {
        // 自己写一个hash函数
        return c.a * 23 + c.b;
    }
};
int main()
{
    unordered_map<my_type, int, my_hash> m;
    m[my_type(1, 2)] = 1;
    m[my_type(2, 3)] = 2;
    m[my_type(3, 4)] = 3;
    m[my_type(5, 6)] = 4;
    for (auto p : m)
    {
        cout << p.first.a << " " << p.first.b << " -> "
             << p.second << "\n";
    }
    cout << "------\n";

    // hash冲突
    m[my_type(0, 25)] = 5;
    for (auto p : m)
    {
        cout << p.first.a << " " << p.first.b << " -> "
             << p.second << "\n";
    }
}
```
* 输出
<pre>
5 6 -> 4
3 4 -> 3
2 3 -> 2
1 2 -> 1
------
5 6 -> 4
3 4 -> 3
2 3 -> 2
0 25 -> 5
1 2 -> 1
</pre>

### priority_queue

* 介绍

priority_queue是优先队列，在压入数据之后，可以按照一定顺序弹出（默认弹出数据中的最大值）
* 复杂度

查找最大值$O(1)$

插入元素$O(logn)$
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
    // 如果是自定义类型，需要重载小于号，或者写比较函数
    // priority_queue<int, vector<int>, cmp> q;
    priority_queue<int> q;
    // 添加元素
    q.push(22);
    q.push(11);
    q.push(33);
    q.push(44);
    q.push(11);

    while (q.size() != 0)
    {
        // 获取最大的元素
        cout << q.top() << endl;
        // 弹出元素
        q.pop();
    }
}
```
* 输出
<pre>
44
33
22
11
11
</pre>

### 容器的嵌套使用

## 算法

## 参考
* https://zh.cppreference.com/