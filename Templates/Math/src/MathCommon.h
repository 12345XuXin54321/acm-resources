#include <bits/stdc++.h>
using namespace std;

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
