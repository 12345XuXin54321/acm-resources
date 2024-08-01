#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
#define max_len 100010
void sol()
{
    int N;
    cin >> N;

    priority_queue<long long int> pq;
    long long int sum = 0;

    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        pq.push(-tmp);
    }
    if (N == 1)
    {
        cout << 0 << "\n";
    }
    else
    {
        while (pq.size() >= 2)
        {
            int a = -pq.top();
            pq.pop();
            int b = -pq.top();
            pq.pop();
            sum += (a + b);
            pq.push(-(a + b));
        }

        cout << sum << "\n";
    }
}
int main()
{
    sol();
}