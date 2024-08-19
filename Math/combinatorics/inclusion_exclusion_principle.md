# 容斥原理

## 引入

有三个集合，用 $A, B, C$ 表示，
如果想要知道它们的并集里面有多少个元素，
也就是要求

$$ | A \cup B \cup C | $$

，应该怎样计算？

如果正向来做，把集合根据和其它集合的交集来分割，再进行计算，
在有些时候会比较复杂。

这个时候就可以考虑反向来思考，
先把每个集合的元素个数相加，
减去两个集合的交集的元素个数，
也就是重复加的，
再加上三个集合的交集的元素个数……
也就是

$$
| A \cup B \cup C | =
|A| + |B| + |C|- 
| A \cup B | - 
| B \cup C | - 
| C \cup A | + 
| A \cup B \cup C |
$$

![图解](https://oi-wiki.org/math/combinatorics/images/incexcp.png)

把它推广到一般的情况，就是容斥原理。

## 定义

设 $U$ 中元素有 $n$ 种不同的属性，
第 $i$ 种属性称为 $P_i$ ，
拥有属性 $P_i$ 的元素构成集合 $S_i$ ，
那么

$$
\left|
  \bigcup^n_{i=1} S_i
\right| =
\sum_i |S_i| - 
\sum_{i < j} | S_i \cap S_j | + 
\sum_{i < j < k} | S_i \cap S_j \cap S_k | - 
\dots + 
(-1)^{m-1} \sum_{a_i < a_{i+1}}
\left|
  \bigcap^m_{i=1} S_{a_i}
\right| + 
\dots + 
(-1)^{n-1} | S_1 \cap \dots \cap S_n |
$$

也就是

$$
\left|
  \bigcup^n_{i=1} S_i
\right| =
\sum^m_{m=1}
(-1)^{m-1} \sum_{a_i < a_{i+1}}
\left|
  \bigcap^m_{i=1} S_{a_i}
\right|
$$

可以这样理解：
先把全部集合的属性个数相加，
减去重复加的，加上重复减的……
结果就是所有集合并集的属性的个数。

## 拓展

如果集合间是其他的运算，那么容斥系数可能会有所不同。

比如，类比二进制运算中的异或，定义集合间运算 $XOR$ ，
需要计算 $ | XOR^n_{i=1} A_i | $
，可以得到容斥系数为 $ (-1)^{m+1} 2^{m-1} $

可得

$$
| XOR^n_{i=1} A_i | =
\sum_{S \neq \emptyset, S \subset [n] }
(-1)^{ |S| + 1 } 2^{ |S| - 1 }
\left|
  \bigcap_{i \in S} A_i
\right|
$$

## 题单

| 序号  | 题号  | 标题                    | 题型            | 难度评级 | 题解                   |
|-------|-------|-------------------------|-----------------|----------|:-----------------------|
| 1     | P3197 | [HNOI2008] 越狱         | 容斥原理        | ⭐⭐      |[👍](sol/P3197/sol.md)  |
| 2     | P4515 | [COCI2009-2010#6] XOR   | 容斥原理，几何  | ⭐⭐⭐⭐   |[👍](sol/P4515/sol.md)  |


## 参考

* [容斥原理](https://oi-wiki.org/math/combinatorics/inclusion-exclusion-principle/)

* [[复习资料]容斥原理学习笔记](https://www.cnblogs.com/lsq147/p/13621250.html)
