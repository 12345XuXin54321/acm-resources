# 矩阵

## 矩阵相乘

设矩阵 $\pmb{A}$ 的大小为 $P \times M$ ，
$\pmb{B}$ 的大小为 $M \times Q$ ，
矩阵 $\pmb{C} = \pmb{A} \times \pmb{B} $
，则 $\pmb{C}$ 的第 $i$ 行第 $j$ 列的元素可以表示为

$$ C_{i,j} = \sum_{k = 1}^{m}  A_{i,k} B_{k,j} $$

下面是矩阵相乘的代码， `max_len` 为矩阵最大的大小。

```cpp
struct MX
{
    int arr[max_len][max_len];
    int n, m;
    MX() {}
    MX(int nn, int mm)
    {
        n = nn, m = mm;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                arr[i][j] = 0;
            }
        }
    }
    MX operator*(const MX &r) const
    {
        // 确保m和右乘的矩阵的n相等。
        assert(m == r.n);
        MX res(n, r.m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < r.m; j++)
            {
                for (int k = 0; k < m; k++)
                {
                    res.arr[i][j] += arr[i][k] * r.arr[k][j];
                }
            }
        }
        return res;
    }
};
```

如果希望动态开空间，可以使用 `vector` 。

## 矩阵快速幂

矩阵乘法满足结合律，不满足一般的交换律。
满足结合率，就可以用快速幂来优化矩阵的幂。

设 $x > 0$ ，容易看出

$$\pmb{A}^{2x} = \pmb{A}^x \times \pmb{A}^x $$

$$\pmb{A}^{2x+1} = \pmb{A}^x \times \pmb{A}^x \times \pmb{A} $$

因此可以想到用递归来求解。

```cpp
// 单位矩阵
// 开始初始化对角线为1
MX ident_mx;

MX mx_qpow(MX x, int n)
{
    if (n == 0)
    {
        return ident_mx;
    }
    else if (n == 1)
    {
        return x;
    }
    else if (n % 2 == 0)
    {
        return mx_qpow(x * x, n / 2);
    }
    else
    {
        return x * mx_qpow(x * x, n / 2);
    }
}
```

如果每次的矩阵都相同，
也可以存下 $\pmb{A}^{2^i} $，每次计算快速幂时，
如果 $n$ 的二进制下的第 $i$ 为 $1$ ，则乘上 $\pmb{A}^{2^i} $

```cpp
#define max_pow_n 32
MX qpow_mxarr[max_pow_n];
void init_qpow(MX &x)
{
    // x^(2^0) = x
    qpow_mxarr[0] = x;
    for (int i = 1; i < max_pow_n; i++)
    {
        qpow_mxarr[i] = qpow_mxarr[i - 1] * qpow_mxarr[i - 1];
    }
}
MX mx_qpow(int n)
{
    // 单位矩阵
    MX res = ident_mx;
    for (int i = 0; i < max_pow_n; i++)
    {
        if (n & (1ULL << i))
        {
            res = res * qpow_mxarr[i];
        }
    }
    return res;
}
```

## 题单

| 序号  | 题号              | 标题              | 题型                  | 难度评级 | 题解                             |
|-------|-------------------|-------------------|-----------------------|----------|:---------------------------------|
| 1     | ccfcsp_201512_5   | 矩阵              | 矩阵乘法、矩阵快速幂  | ⭐⭐⭐⭐⭐  |[👍](sol/ccfcsp_201512_5/sol.md)  |
| 2     | luogu_P1939       | 矩阵加速（数列）  | 矩阵快速幂            | ⭐⭐⭐     |[👍](sol/luogu_P1939/sol.md)      |

## 参考

* [矩阵](https://oi-wiki.org/math/linear-algebra/matrix/)