#include <string>
#include <iostream>
using namespace std;
int main()
{
    string str = "aaabbb";

    // 字符串拼接
    string str_2 = "ccc";
    cout << str + str_2 << "\n"
         << str_2 + str << endl;

    char c = 'd';
    cout << str + c << endl;
    cout << c + str << endl;

    cout << str + "eeee" << "\n"
         << str + 'f' << endl;
    cout << "eeee" + str << "\n"
         << 'f' + str << endl;

    // 编译错误
    // cout << "aaaa" + "bbbbb" << endl;
}