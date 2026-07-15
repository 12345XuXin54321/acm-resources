#include <stack>
#include <iostream>
using namespace std;
int main()
{
    stack<int> s;
    // 添加元素
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    // 访问栈顶元素
    cout << s.top() << endl;

    // 弹出栈顶元素
    s.pop();
    cout << s.top() << endl;
}