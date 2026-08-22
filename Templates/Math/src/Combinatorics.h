#include "MathCommon.h"

// T 需要传入 ModInt
template <typename T, int MaxLen>
struct Combination
{
    T fact[MaxLen], inv_fact[MaxLen];

    constexpr Combination()
    {
        fact[0] = T(1);
        for (int i = 1; i < MaxLen; i++)
        {
            fact[i] = fact[i - 1] * T(i);
        }

        inv_fact[MaxLen - 1] = fact[MaxLen - 1].inv();
        for (int i = MaxLen - 1; i >= 1; i--)
        {
            inv_fact[i - 1] = inv_fact[i] * T(i);
        }
    }

    constexpr T comb(int n, int k) const
    {
        if (k < 0 || k > n)
            return T(0);
        return fact[n] * inv_fact[k] * inv_fact[n - k];
    }
    constexpr T perm(int n, int k) const
    {
        if (k < 0 || k > n)
            return T(0);
        return fact[n] * inv_fact[n - k];
    }
};
