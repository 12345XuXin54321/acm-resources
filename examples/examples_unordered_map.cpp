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