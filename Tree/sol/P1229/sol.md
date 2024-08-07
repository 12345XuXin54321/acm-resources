# P1229 遍历问题 

## 题意

给出一个二叉树的前序遍历和后序遍历，不能确定一个二叉树，请问有多少种不同的中序遍历（即有多少种二叉树）

## 解释

### 为什么不能确定一颗二叉树

前序遍历的代码如下

```cpp
int dfs(r)
{
    visit(r);
    dfs(r->lch);
    dfs(r->rch);
}
```

后序遍历的代码如下

```cpp
int dfs(r)
{
    dfs(r->lch);
    dfs(r->rch);
    visit(r);
}
```

对应的序列为 `|root|l|r|` 和 `|l|r|root|` 两种。
发现除了第一个结点可以确定为根结点外，
其余的字母可能是访问左结点访问的，
也可能是没有左结点，直接访问右结点生成的。

因此不能确定一颗二叉树。
同理，多叉树也一样不能确定。


## 思路

可以用递归和分类讨论的思想，把一段字符串分为

* 根结点和左子树，没有右子树
* 根结点和左子树，有右子树
* 根结点和右子树

然后递归子树的可能的种类，然后相加。

## 题解代码

[代码](main.cpp)