# P1939 矩阵加速（数列） 

## 题意

有一个数列 $a_n$ ，满足
$$
a_x = 
\begin{cases}
    1 & x \in \{ 1,2,3 \} \\
    a_{x-1} + a_{x-3} & x \geq 4
\end{cases}
$$
求数列的第 $n$ 项对 $10^9+7$ 取余的值。

## 思路

设初始矩阵
$$
\pmb{b} = 
\begin{pmatrix}
    a_{n-2} & a_{n-1} & a_n
\end{pmatrix}
$$

设矩阵 $\pmb{A}$ ，使
$$ \pmb{bA} = 
\begin{pmatrix}
    a_{n-1} & a_n & a_{n+1}
\end{pmatrix}
$$

解得
$$ \pmb{A} = 
\begin{pmatrix}
    0 & 0 & 1 \\
    1 & 0 & 0 \\
    0 & 1 & 1 
\end{pmatrix}
$$

$x \geq 4$ 时， $a_x$ 即为 $bA^{x-3}$ 的第三项。
其中， $A^{x-3}$ 可以用矩阵快速幂求。

## 题解代码

[代码](main.cpp)