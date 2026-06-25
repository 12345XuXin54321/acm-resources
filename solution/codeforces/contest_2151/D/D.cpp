#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define max_len 200010
#define mod_n 998244353

template <typename T>
constexpr T qpow(T x, uint64_t n)
{
    T res{1};
    for (; n != 0; n /= 2, x *= x)
    {
        if (n % 2 == 1)
        {
            res *= x;
        }
    }
    return res;
}

template <typename T, T ModP>
class ModInt
{
    T x;

    constexpr T mod(const T v)
    {
        T res = v % ModP;
        if (res < 0)
            res += ModP;
        return res;
    }

public:
    constexpr ModInt() = default;
    constexpr ModInt(T v)
    {
        x = mod(v);
    }
    constexpr T val() const
    {
        return x;
    }

    constexpr ModInt inv() const
    {
        return qpow(*this, ModP - 2);
    }

    constexpr ModInt &operator+=(const ModInt &rhs)
    {
        x = mod(x + rhs.x);
        return *this;
    }
    constexpr ModInt &operator-=(const ModInt &rhs)
    {
        x = mod(x - rhs.x);
        return *this;
    }
    constexpr ModInt &operator*=(const ModInt &rhs)
    {
        x = mod(x * rhs.x);
        return *this;
    }
    constexpr ModInt &operator/=(const ModInt &rhs)
    {
        (*this) *= rhs.inv();
        return *this;
    }

    friend constexpr ModInt operator+(ModInt lhs, const ModInt &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend constexpr ModInt operator-(ModInt lhs, const ModInt &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr ModInt operator*(ModInt lhs, const ModInt &rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr ModInt operator/(ModInt lhs, const ModInt &rhs)
    {
        lhs /= rhs;
        return lhs;
    }
};

using Mint = ModInt<int, mod_n>;

int arr[max_len];
int n;

Mint fact_arr[max_len];

// C_n^m
Mint C(int n, int m)
{
    Mint num = fact_arr[n];
    Mint den = fact_arr[m] * fact_arr[n - m];
    return num / den;
}

void init_fact()
{
    fact_arr[0] = 1;
    for (int i = 1; i < max_len; i++)
    {
        fact_arr[i] = i * fact_arr[i - 1];
    }
}

int get_ans()
{
    int max_x = n / 2 + n % 2;
    int sum = 0;
    for (int i = 1; i <= max_x; i++)
    {
        sum += arr[i];
    }
    if (sum != n)
    {
        return 0;
    }
    for (int i = max_x + 1; i <= n; i++)
    {
        if (arr[i] != 0)
            return 0;
    }
    if (n % 2 == 1)
    {
        if (arr[max_x] > 1)
            return 0;
    }
    Mint ans = 1;
    int used_col = 0;
    if (n % 2 == 1)
    {
        used_col = arr[max_x];
    }
    for (int i = n / 2; i >= 1; i--)
    {
        int can_place = n - (i - 1) * 2 - used_col;

        ans = ans * C(can_place, arr[i]);

        used_col += arr[i];
    }
    return ans.val();
}

void sol()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    int ans = get_ans();
    cout << ans << "\n";
}

int32_t main()
{
    init_fact();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
    {
        sol();
    }
}