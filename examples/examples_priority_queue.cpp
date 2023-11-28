#include <queue>
#include <iostream>
using namespace std;
int main()
{
    priority_queue<int> q;
    // 添加元素
    q.push(22);
    q.push(11);
    q.push(33);
    q.push(44);
    q.push(11);

    while (q.size() != 0)
    {
        cout << q.top() << endl;
        q.pop();
    }
}