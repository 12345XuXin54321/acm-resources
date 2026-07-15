# 乘法逆元

## 定义

如果一个线性同余方程 $ax \equiv 1 \pmod{b}$ ，
则称 $x$ 为 $a \pmod{b}$ 的逆元，记作 $a^{-1}$

## 求法

### 快速幂法

如果 $b$ 是质数，可以根据费马小定理得出

$$ x \equiv a^{b-2} \pmod{b} $$

设 $b = 1000000007$

```cpp
#define mod_n 1000000007
#define mod(x) ((x) % mod_n)

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
    return qpow(num, mod_n - 2);
}
```

### exgcd法

当 $b$ 不是质数的时候，可以使用拓展欧几里德法。
也就是求同余方程

$$ax + by = 1$$

只需要保证 $gcd(a,b) = 1$

```cpp
// ax + by = gcd(a, b)
int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    else
    {
        int x2, y2;
        int g = exgcd(b, a % b, x2, y2);
        x = y2;
        y = x2 - (a / b) * y2;
        return g;
    }
}

// ax + by = 1
int inv(int a, int b)
{
    int x0, y0;
    int g = exgcd(a, b, x0, y0);

    int x_step = b / g;
    return ((x0 % x_step) + x_step) % x_step;
}
```

## 参考

* [乘法逆元](https://oi-wiki.org/math/number-theory/inverse/)