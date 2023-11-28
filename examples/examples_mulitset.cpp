#include <set>
#include <iostream>
using namespace std;
void print_set(multiset<int> &s)
{
    for (auto n : s)
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