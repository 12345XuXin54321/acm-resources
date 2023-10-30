# STL

## 简介

STL是在c++中使用非常广泛的一个库，里面包含了许多的常用的容器和算法。使用STL，可以简化代码，减少写代码的时间，把重点放在算法的实现上。

一般来说，可以添加这两行来使用STL。
```cpp
#include <bits/stdc++.h>
using namespace std;
```
不过 `#include <bits/stdc++.h>` **不是**标准C++的头文件，而是GNU ISO C++的头文件，一般只有 `gcc` 和 `clang` 支持，**大部分**的oj和竞赛**也支持**，具体要看oj的官方说明。

`using namespace std;` 在平常写代码的时候最好不要用，用的话可能会有命名的冲突。如果非要用的话要注意，变量名、函数名不要取STL里面有的名字。如果不用的话，使用STL里的库时要添加限定名 `std::` ，比如 `std::vector<int> vec;` 和 `std::cout << "hello world!" << std::endl;`。

接下来的讲解中，会说明这个用法所需要包含的头文件和最少需要的C++版本。


## 用法

### 基础的容器

#### vector
* 介绍

vector是封装后的顺序存储的大小可变的数组。

简单来说就是数组，数据是连续储存的。可以用下标访问。
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

#### list
* 介绍

list是链表（一般是双向链表），可以以$O(1)$的复杂度进行插入和删除操作（即花费常数的时间）。但是，链表的数据不是连续存放的，因此不能用下标访问。
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

    //向开头添加元素
    l.push_front(44);
    l.push_front(55);

    // 遍历元素，同vector，需要C++11
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

    // 更改、删除元素需要使用迭代器
    .....

    cout << l.size() << endl;
    // 清空list
    l.clear();
    cout << l.size() << endl;
}
```

#### queue
* 介绍
* 头文件
```cpp
```
* 用法
```cpp
```

#### stack
* 介绍
* 头文件
```cpp
```
* 用法
```cpp
```

#### list
* 介绍
* 头文件
```cpp
```
* 用法
```cpp
```

#### 小总结

##### 遍历(c++98)
##### 遍历(c++11)
##### 构造函数
##### 公共的成员函数

### 加了算法的容器

#### set

#### map

#### priority_queue

#### unordered_map

### 容器的遍历

### 算法

