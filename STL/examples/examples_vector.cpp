#include <vector>
#include <iostream>
using namespace std;
int main()
{
    // 定义vector时需要指定要存储的变量的类型
    // 格式为 vector<类型> 变量名(初始大小);
    vector<int> vec(5);

    // 向末尾添加元素
    vec.push_back(10);
    vec.push_back(20);

    // 访问、更改元素
    cout << vec[0] << " " << vec[1] << "\n"
         << vec[5] << " " << vec[6] << "\n";

    vec[1] = 100;
    cout << vec[1] << "\n";

    // 遍历元素，需要C++11
    // 还有一种遍历的方法只需要C++98，等一下会提到
    for (auto n : vec)
    {
        cout << n << " ";
    }
    cout << endl;

    // 删除末尾的元素
    vec.pop_back();

    for (auto n : vec)
    {
        cout << n << " ";
    }
    cout << endl;

    cout << vec.size() << endl;
    // 清空vector
    vec.clear();
    cout << vec.size() << endl;
}