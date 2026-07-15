#include <bits/stdc++.h>
using namespace std;
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
        return fb(n - 1) + fb(n - 2);
    }
}
int main()
{
    size_t n;
    while (cin >> n)
    {
        // 运算的计时
        const auto start{chrono::steady_clock::now()};
        auto ans = fb(n);
        const auto end{chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds{end - start};

        cout << "fb(" << n << ") = " << ans << "\t";
        cout << "time = " << elapsed_seconds.count() << "s\n\n";
    }
}