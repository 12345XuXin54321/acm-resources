#include <bits/stdc++.h>
using namespace std;
#define mod_n (1000000007)
#define mod(x) ((x) % mod_n)
#define int int64_t

#define max_len 5000

int fact_arr[max_len];

void init_fact()
{
    fact_arr[0] = 1;
    for (int i = 1; i < max_len; i++)
    {
        fact_arr[i] = mod(i * fact_arr[i - 1]);
    }
}
int qpow(int x, int n)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return mod(x);
    else if (n % 2 == 0)
    {
        return qpow(mod(x * x), n / 2);
    }
    else
    {
        return mod(qpow(mod(x * x), n / 2) * x);
    }
}
int inv(int num)
{
    // cout << num << " " << qpow(num, mod_n - 2) << endl;
    return qpow(num, mod_n - 2);
}
int fact(int n)
{
    // cout << n << "! " << fact_arr[n] << endl;
    return fact_arr[n];
}

// C_m^n
int combin(int n, int m)
{
    // cout << "combin " << n << " " << m << endl;
    return mod(fact(m) *
               inv(mod(fact(n) * fact(m - n))));
}

void sol()
{
    int n;
    cin >> n;
    // group1 0,1
    // group2 2,3
    // |g2|--g1,g2---|
    int ans = 0;
    for (int g2_add = 1; g2_add <= (n - 1) - 2; g2_add++)
    {
        int g1_size = n - 1 - g2_add;
        int g2_size = g2_add + 1;

        int g2_loca = combin(g2_add, n - 1);
        int g2_num = (g2_size - 1);
        int g1_num = (g1_size - 1);

        ans += mod(g2_loca * mod(g1_num * g2_num));
        ans = mod(ans);
    }
    cout << ans << "\n";
}

int32_t main()
{
    init_fact();
    sol();
}