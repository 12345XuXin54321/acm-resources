#include <queue>
#include <iostream>
using namespace std;
int main()
{
    queue<int> q;
    // 向队尾插入元素
    q.push(11);
    q.push(22);
    q.push(33);
    q.push(44);

    // 访问队头元素
    cout << q.front() << endl;
    // 访问队尾元素
    cout << q.back() << endl;

    // 弹出队头元素
    q.pop();
    cout << q.front() << endl;
}