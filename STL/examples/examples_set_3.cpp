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