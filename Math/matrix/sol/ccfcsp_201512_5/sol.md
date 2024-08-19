# ccfcsp 201512-5 矩阵

## 题意

有一个大小为 $m \times 1$ 的初始矩阵 $\pmb{b}$
，大小为 $m \times m$ 的转移矩阵 $\pmb{A}$
，设当前的状态为 $\pmb{b}$ ，下一个状态则为 $\pmb{A} \pmb{b}$ 。

矩阵的每一个元素都满足 $a_{i, j} \in \{0, 1\}$
，令相乘为与运算，相加为异或运算。

求 $A^k b$ 。

## 思路

由于输出为 $( \pmb{A}^k \pmb{b})^T$
，有

$$(\pmb{A}^k \pmb{b})^T  = \pmb{b}^T (\pmb{A}^T)^k$$

### 矩阵相乘

设矩阵的大小为 $m \times m$
。 $m$ 较大，
因为矩阵为 `01矩阵` ，相乘时可以用 `bitset` 来优化。

朴素的矩阵乘法如下

```cpp
for (int i = 0; i < m; i++)
{
    for (int j = 0; j < m; j++)
    {
        for (int k = 0; k < m; k++)
        {
            bool b = (l.arr[i][k] & r.arr[k][j]);
            ans.arr[i][j] = (ans.arr[i][j] ^ b);
        }
    }
}
```

等效于

```cpp
for (int i = 0; i < m; i++)
{
    for (int k = 0; k < m; k++)
    {
        for (int j = 0; j < m; j++)
        {
            bool b = (l.arr[i][k] & r.arr[k][j]);
            ans.arr[i][j] = (ans.arr[i][j] ^ b);
        }
    }
}
```

发现 `ans.arr[i][j]` 和 `r.arr[k][j]` 对齐了，
可以用 `bitset` 优化。

```cpp
for (int i = 0; i < m; i++)
{
    for (int k = 0; k < m; k++)
    {
        if (l.arr[i][k])
        {
            ans.arr[i] ^= r.arr[k];
        }
    }
}
```

### 矩阵快速幂

由于 $k$ 很大，所有需要使用矩阵的快速幂运算。
先计算出 $(\pmb{A}^T)^{2^i} $

考虑到 $\pmb{b}^T$ 的大小为 $1 \times m$
，右乘的矩阵 $\pmb{X}$ 大小为 $m \times m$
，可以先令 $\pmb{X}^T$ 为 $\pmb{X}$ 的转置
，然后 $\pmb{b}[i]$ 的值就等于 $\pmb{b}$和 $\pmb{X}^T[i]$
进行与运算后，每一位的值进行异或后的值。

$\pmb{b}^T (\pmb{A}^T)^{2^i} $的大小仍为 $1 \times m$，
所以可以连续地右乘 $(\pmb{A}^T)^{2^i} $。

## 复杂度

首先需要预处理 $(\pmb{A}^T)^{2^i} , i \in [0, k)$ ，取 $k = 32 $
，复杂度为 $O(k \times \frac{n^3}{w})$
，每次计算的复杂度为 $O(k \times \frac{n^2}{w})$
，总复杂度为 $O(k \times \frac{n^3}{w} + Qk \times \frac{n^2}{w})$

取 $w=64$ ，约要计算 $5.5 \times 10^8$次。 `bitset` 的常数较小，勉强可以在 `1s` 内跑完。

## 题解代码

[代码](main.cpp)

## 参考

* [AcWing 3226. [CSP201512-5] 矩阵 bitset 01乘法+矩阵转置卡常](https://www.acwing.com/solution/content/244818/)
