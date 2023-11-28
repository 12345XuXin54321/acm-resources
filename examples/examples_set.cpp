#include <set>
#include <iostream>
using namespace std;
void print_set(set<int> &s)
{
    for (auto n : s)
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
    if (itor != s.end())
    {
        cout << "找到" << *itor << endl;
    }
    else
    {
        cout << "没找到" << endl;
    }

    // 首个不小于给定值的迭代器
    cout << *(s.lower_bound(33)) << endl;
    // 首个大于给定值的迭代器
    cout << *(s.upper_bound(33)) << endl;

    // 返回特定值元素范围
    auto itor_pir = s.equal_range(33);
    for (auto itor = itor_pir.first; itor != itor_pir.second; itor++)
    {
        cout << *itor << endl;
    }

    // 删除元素
    s.erase(22);
    print_set(s);
}