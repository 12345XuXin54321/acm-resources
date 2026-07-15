#include <bits/stdc++.h>
using namespace std;
#define max_len 1000010
#define mod_n 1000000007
#define mod(x) ((x) % mod_n)

int64_t fact_arr[max_len];

void init_fact()
{
    fact_arr[0] = 1;
    for (int i = 1; i < max_len; i++)
    {
        fact_arr[i] = mod(i * fact_arr[i - 1]);
    }
}
int64_t qpow(int64_t x, int64_t n)
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
int64_t inv(int64_t num)
{
    // cout << num << " " << qpow(num, mod_n - 2) << endl;
    return qpow(num, mod_n - 2);
}
int64_t fact(int64_t n)
{
    // cout << n << "! " << fact_arr[n] << endl;
    return fact_arr[n];
}

// C_m^n
int64_t combin(int64_t n, int64_t m)
{
    // cout << "combin " << n << " " << m << endl;
    return mod(fact(m) *
               inv(mod(fact(n) * fact(m - n))));
}

int64_t not_in_loca[max_len];

void init_loca()
{
    not_in_loca[0] = 1;
    not_in_loca[1] = 0;
    not_in_loca[2] = 1;
    for (int i = 3; i < max_len; i++)
    {
        not_in_loca[i] = mod(not_in_loca[i - 1] * (i - 1));
        not_in_loca[i] += mod(not_in_loca[i - 2] * (i - 1));
        not_in_loca[i] = mod(not_in_loca[i]);
    }
}

void sol()
{
    int n, m;
    cin >> n >> m;
    cout << mod(not_in_loca[n - m] * combin(m, n)) << "\n";
}

int main()
{
    init_fact(), init_loca();
    int T;
    cin >> T;
    while (T--)
    {
        sol();
    }
}