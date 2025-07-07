#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define mod_n 1000000007LL
#define mod(x) ((x) % mod_n)

int qpow(int x, int n)
{
    if(n == 0) return 1;
    else if(n == 1) return mod(x);
    else if(n % 2 == 0) return qpow(mod(x * x), n / 2);
    else return mod(x * qpow(mod(x * x), n / 2));
}

#define inv(x) (qpow((x), mod_n - 2))

int C(int n, int m)
{
    int fz = 1, fm = 1;
    for(int i = 1; i <= m; i++)
    {
        fm = mod(fm * i);
        fz = mod(fz * mod(n - i + 1));
    }
    return mod(fz * inv(fm));
}

void sol()
{
    int a, b, k;
    cin >> a >> b >> k;
    int n = ((a - 1) * k) + 1;
    int m = mod(mod(C(n, a) * k) * (b - 1)) + 1;
    cout << mod(n) << " " << mod(m) << "\n";
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
    {
        sol();
    }
}