# 圆和反演变换

## 引入

在计算几何的题目中，有时会出现和圆相关的计算。
大部分时候只使用三角函数和一些常见的公式就可以完成计算。

如果题目中有多个直线和圆的相切关系，则可以使用反演变换，
来减少计算量。

## 圆专题

大部分可以使用三角函数和列方程组来解决，
不过有些时候可能会有较为复杂的计算。

## 反演变换

### 定义

给定反演中心 $O$ 和反演半径 $R$ 。
若平面上点 $P$ 和 $P'$ 满足：

* 点 $P'$ 在射线 $\overrightarrow{OP}$ 上

* $|OP| \cdot |OP'| = R^2$

则称点 $P$ 和点 $P'$ 互为反演点。

### 性质

* 圆 $O$ 外（内）的点的反演点在圆 $O$ 内（外），圆 $O$ 上的点的反演点为其自身。
* 不过点 $O$ 的圆，反演图形也是不过点 $O$ 的圆。
* 过点 $O$ 的圆，反演图形是不过点 $O$ 的直线。
* 两个图形相切且存在不为点 $O$ 的切点，则他们的反演图形也相切。

### 相关计算

#### 求不过点 $O$ 的圆的反演图形

记圆 $O$ 的半径为 $R$ ，圆心坐标为 $(x_0, y_0)$ ，
圆 $A$ 的半径为 $r_1$ ，圆心坐标为 $(x_1, y_1)$ 。
圆 $A$ 的反演图形为圆 $B$ ，则：

圆 $B$ 的半径为
$$r_2 = \frac{R^2 \cdot r_1}{|OA|^2 - r_1^2}$$
圆心坐标 $(x_2, y_2)$ 为
$$
    x_2 = x_0 + \frac{(R^2 + r_1 \cdot r_2) (x_1 - x_0)}{|OA|^2} \\
    y_2 = y_0 + \frac{(R^2 + r_1 \cdot r_2) (y_1 - y_0)}{|OA|^2}
$$

```cpp
circle circle_inversion(const circle &c1, const circle &base_circle)
{
    auto [pO, R] = base_circle;
    auto [x0, y0] = pO;

    auto [pA, r1] = c1;
    auto [x1, y1] = pA;

    if (pO == pA)
    {
        return circle{pO, R * R / r1};
    }

    auto len2_OA = (pA - pO).len2();
    auto r2 = R * R * r1 / (len2_OA - (r1 * r1));

    auto x2 = x0 + (R * R + r1 * r2) * (x1 - x0) / len2_OA;
    auto y2 = y0 + (R * R + r1 * r2) * (y1 - y0) / len2_OA;

    return circle{{x2, y2}, abs(r2)};
}
```

#### 求过点 $O$ 的圆的反演图形

```cpp
line circle_through_center_inversion(const circle &c1, const circle &base_circle)
{
    auto [pO, R] = base_circle;
    auto [pC, r] = c1;

    point OC = pC - pO;

    // 计算直线到O点的距离
    double d = (R * R) / (2 * r);

    // 计算垂足点（直线与OC连线的交点）
    // OC 的方向向量乘上距离
    point p1 = pO + OC.normalized() * d;

    // 返回直线上一点，和直线的方向向量
    return line(p1, OC.normalized().rotate90());
}
```



## 参考

* https://oi-wiki.org