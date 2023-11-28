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