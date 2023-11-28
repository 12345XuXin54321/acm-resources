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