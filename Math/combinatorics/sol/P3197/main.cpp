#include <bits/stdc++.h>
using namespace std;
#define mod_n 100003
#define mod(x) ((x) % mod_n)
int64_t qpow(int64_t x, int64_t n)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return mod(x);
    else if (n % 2 == 0)
        return qpow(mod(x * x), n / 2);
    else
        return mod(x * qpow(mod(x * x), n / 2));
}
void sol()
{
    int64_t m, n;
    cin >> m >> n;
    int64_t all_num = qpow(m, n);
    int64_t not_num = mod(m * qpow(m - 1, n - 1));
    cout << mod(mod_n + all_num - not_num) << "\n";
}
int main()
{
    sol();
}