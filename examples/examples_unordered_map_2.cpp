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