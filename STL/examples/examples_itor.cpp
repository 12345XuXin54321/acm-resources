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
    if (itor_begin == itor_end)
    {
        cout << "相同" << endl;
    }
    else
    {
        cout << "不相同" << endl;
    }
}