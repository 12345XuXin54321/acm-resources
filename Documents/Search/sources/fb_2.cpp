#include <bits/stdc++.h>
using namespace std;
// 记忆化数组
size_t arr[10000];
// 斐波那契数列，n需要大于或等于0
size_t fb(size_t n)
{
    if (n <= 1)
    {
        // f(0) = 0, f(1) = 1
        return n;
    }
    else
    {
        // 当数组内的值没有被计算，才进行计算
        if (arr[n] == 0)
            arr[n] = fb(n - 1) + fb(n - 2);
        return arr[n];
    }
}
int main()
{
    size_t n;
    while (cin >> n)
    {
        const auto start{chrono::steady_clock::now()};
        auto ans = fb(n);
        const auto end{chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds{end - start};

        cout << "fb(" << n << ") = " << ans << "\t";
        cout << "time = " << elapsed_seconds.count() << "s\n\n";
    }
}