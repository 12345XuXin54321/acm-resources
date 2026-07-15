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