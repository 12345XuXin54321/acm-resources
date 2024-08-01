# UVA-548 Tree

## 题意

给出结点值的中序遍历，后序遍历。问哪一个叶子结点到根结点的路径的权值的和最小，输出这个叶子结点的权值，如果有多个，输出最小的权值。

## 思路

可以直接把权值当作结点的下标，先构建二叉树，再从根结点遍历，当左右子结点的下标都为0是代表是叶子结点。

## 题解代码

[代码](main.cpp)