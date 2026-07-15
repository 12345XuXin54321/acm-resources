# 组合数学

## 公式

### 排列数

从 $n$ 个不同元素中，任取 $m$ 个元素按照**一定顺序**排成一列，
叫做从 $n$ 个不同元素中取出 $m$ 个元素的一个排列

从 $n$ 个不同元素中取出 $m$ 个元素的所有排列的个数，
叫做从 $n$ 个不同元素中取出 $m$ 个元素的排列数，用符号
$\mathrm A_n^m$ 表示。

$$\mathrm A_n^m = \frac{n!}{(n - m)!}$$

### 组合数

从 $n$ 个不同元素中，任取 $m$ 个元素组成一个集合，
叫做从 $n$ 个不同元素中取出 $m$ 个元素的一个组合

从 $n$ 个不同元素中取出 $m$ 个元素的所有组合的个数，
叫做从 $n$ 个不同元素中取出 $m$ 个元素的组合数，用符号
$\dbinom{n}{m}$ 来表示。

组合数计算公式

$$\dbinom{n}{m} = \frac{n!}{m! (n - m)!}$$

## 计算

组合数的计算中需要用到大量的阶乘计算，
如果直接计算会耗费大量的时间。
可以考虑递推来求阶乘。

```cpp
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
    return qpow(num, mod_n - 2);
}
int64_t fact(int64_t n)
{
    return fact_arr[n];
}

// C_m^n
int64_t combin(int64_t n, int64_t m)
{
    return mod(fact(m) *
               inv(mod(fact(n) * fact(m - n))));
}
```

先用 `init_fact` 初始化阶乘的数组后，
就可以求组合数了。

## 题单

| 序号  | 题号              | 标题                  | 题型                  | 难度评级 | 题解                             |
|-------|-------------------|-----------------------|-----------------------|----------|:---------------------------------|
| 1     | P4071             | [SDOI2016] 排列计数   | 组合数学、逆元        | ⭐⭐⭐     |[👍](sol/P4071/sol.md)            |
| 2     | ccfcsp_201312_4   | 有趣的数              | 组合数学、枚举、逆元  | ⭐⭐⭐     |[👍](sol/ccfcsp_201312_4/sol.md)  |

## 参考

[排列组合](https://oi-wiki.org/math/combinatorics/combination/)