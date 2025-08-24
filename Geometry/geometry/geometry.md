# 计算几何

这里介绍在二维平面内的计算几何的内容，
坐标系设为平面直角坐标系。

## 计算几何基础

### 点和向量的表示

点一般用横纵坐标表示，向量也一样。
一般定义结构体来储存，并重载运算符。

### 直线和射线的表示

一般用直线上一点和直线的方向向量来表示。

### 线段的表示

只需要记录左右端点。

### 多边形

使用数组按一定顺序记录多边形每个顶点即可。

## 极角排序

以一点为原点，把其他点按照和这一点的角度排序。

由于 `atan2` 可能有精度问题，
所以一般使用叉积来进行排序。

### 例题 [Horizon Scanning](https://codeforces.com/gym/105588/problem/H)

#### 题意

海洋中有 $n$ 个岛屿，第 $i$ 个岛屿位于 $(x_i​,y_i​)$ ，
可以视为平面上的一个点。
假设雷达的扫描角度范围为 $\alpha$ 。
当雷达旋转到角度 $\theta$ 时，
它可以监控位于角度范围
$[\theta − \frac{\alpha}{2}​, \theta + \frac{\alpha}{2}​]$ 内的所有岛屿。

在 $(0, 0)$ 处有一个雷达，当最小扫描角 $\alpha$ 是多少时，
可以确保在任意角度 $\theta$ 下，
雷达至少可以监控到 $k$ 个岛屿。

#### 思路

把所有岛屿按照对于雷达的极角进行排序，
对于每个岛屿 $i$ ，计算与第 $(i + k) \pmod{n}$
岛屿的极角的差是多少。
此时扫描区间覆盖 $k + 1$ 个岛屿，
但是当 $\theta$ 改变时就只会覆盖 $k$ 个岛屿了。

如果 $i = (i + k) \pmod{n}$ ，
则说明需要覆盖全部的岛屿，此时 $\alpha = 2 \pi$

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define eps 1e-7
#define max_len 200010
constexpr long double PI = 3.1415926535897932384l;

// 点与向量
template <typename T>
struct point
{
    T x, y;
    point() {}
    point(T _x, T _y) { x = _x, y = _y; }
    bool operator==(const point &a) const { return (abs(x - a.x) <= eps && abs(y - a.y) <= eps); }
    bool operator<(const point &a) const
    {
        if (abs(x - a.x) <= eps)
            return y < a.y - eps;
        return x < a.x - eps;
    }
    bool operator>(const point &a) const { return !(*this < a || *this == a); }
    point operator+(const point &a) const { return {x + a.x, y + a.y}; }
    point operator-(const point &a) const { return {x - a.x, y - a.y}; }
    point operator-() const { return {-x, -y}; }
    point operator*(const T k) const { return {k * x, k * y}; }
    point operator/(const T k) const { return {x / k, y / k}; }
    T operator*(const point &a) const { return x * a.x + y * a.y; } // 点积
    T operator^(const point &a) const { return x * a.y - y * a.x; } // 叉积，注意优先级
    T len2() const { return (*this) * (*this); }                    // 向量长度的平方
    T dis2(const point &a) const { return (a - (*this)).len2(); }   // 两点距离的平方

    long double len() const { return sqrtl(len2()); }                // 向量长度
    long double dis(const point &a) const { return sqrtl(dis2(a)); } // 两点距离
};

// 极角排序
template <typename T>
struct argcmp
{
    point<T> base_point;
    argcmp() : base_point(0, 0) {}
    argcmp(point<T> p) : base_point(p) {}
    bool operator()(const point<T> &p1, const point<T> &p2) const
    {
        auto a = p1 - base_point, b = p2 - base_point;
        const auto quad = [](const point<T> &p)
        {
            if (p.y < -eps)
                return 1;
            if (p.y > eps)
                return 4;
            if (p.x < -eps)
                return 5;
            if (p.x > eps)
                return 3;
            return 2;
        };
        const int qa = quad(a), qb = quad(b);
        if (qa != qb)
            return qa < qb;
        const auto t = a ^ b;
        // 不同长度的向量需要分开
        if (abs(t) <= eps)
            return a * a < b * b - eps;
        return t > eps;
    }
};

int n, k;
point<int> arr[max_len];

void sol()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].x >> arr[i].y;
    }

    sort(arr, arr + n, argcmp(point<int>(0, 0)));

    double ans = 0;
    for (int pbeg = 0; pbeg < n; pbeg++)
    {
        int pend = (pbeg + k) % n;
        if (pend == pbeg)
        {
            ans = 2 * PI;
            break;
        }
        auto end_ang = atan2(arr[pend].y, arr[pend].x);
        auto beg_ang = atan2(arr[pbeg].y, arr[pbeg].x);
        if (pend < pbeg)
        {
            end_ang += PI * 2;
        }

        ans = max(ans, end_ang - beg_ang);
    }
    cout << fixed << setprecision(10) << ans << "\n";
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
    {
        sol();
    }
}
```

## 凸包

### 定义

#### 凸多边形

凸多边形是指所有内角大小都在 $[0, \pi]$ 范围内的 **简单多边形** 。

#### 凸包

能包含所有给定点的最小凸多边形叫做凸包。

## 旋转卡壳

### 引入

旋转卡壳算法在凸包算法的基础上，
可以在线性时间内求解如凸包直径、
最小矩形覆盖等和凸包性质相关的问题

### 例题 [Trash Removal](https://codeforces.com/gym/101175/problem/K)

#### 题意

有一个多边形的垃圾，可以旋转任意角度。
当被丢进垃圾筒时，会竖直下落。

需要计算出，允许垃圾通过的最小垃圾桶宽度。

#### 思路

求出多边形的凸包，然后用旋转卡壳求出凸包的
最小的宽度。

只需要在枚举点的时候，计算每个点距离最远的边的距离，
然后取最小值。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define eps 1e-7
#define max_len 200
constexpr long double PI = 3.1415926535897932384l;

// 点与向量
template <typename T>
struct point
{
    T x, y;
    point() {}
    point(T _x, T _y) { x = _x, y = _y; }
    bool operator==(const point &a) const { return (abs(x - a.x) <= eps && abs(y - a.y) <= eps); }
    bool operator<(const point &a) const
    {
        if (abs(x - a.x) <= eps)
            return y < a.y - eps;
        return x < a.x - eps;
    }
    bool operator>(const point &a) const { return !(*this < a || *this == a); }
    point operator+(const point &a) const { return {x + a.x, y + a.y}; }
    point operator-(const point &a) const { return {x - a.x, y - a.y}; }
    point operator-() const { return {-x, -y}; }
    point operator*(const T k) const { return {k * x, k * y}; }
    point operator/(const T k) const { return {x / k, y / k}; }
    T operator*(const point &a) const { return x * a.x + y * a.y; } // 点积
    T operator^(const point &a) const { return x * a.y - y * a.x; } // 叉积，注意优先级

    // to-left 测试
    int toleft(const point &a) const // 1表示在左边 0表示在线上 -1表示在右边
    {
        const auto t = (*this) ^ a;
        return (t > eps) - (t < -eps);
    }

    T len2() const { return (*this) * (*this); }                  // 向量长度的平方
    T dis2(const point &a) const { return (a - (*this)).len2(); } // 两点距离的平方

    long double len() const { return sqrtl(len2()); }                // 向量长度
    long double dis(const point &a) const { return sqrtl(dis2(a)); } // 两点距离
};
using Point = point<int>;

template <typename T>
struct line
{
    point<T> p, v; // p 为直线上一点，v 为方向向量
    line() = default;
    line(Point p, Point v) : p(p), v(v) {}

    double dis(const point<T> &a) const { return abs(v ^ (a - p)) /
                                                 v.len(); }
};

template <typename T>
struct polygon
{
    vector<point<T>> p;
    // 以逆时针顺序存储
    polygon() = default;
    polygon(vector<point<T>> _p) : p(_p) {}
    size_t nxt(const size_t i) const { return i == p.size() - 1 ? 0 : i + 1; }
    size_t pre(const size_t i) const { return i == 0 ? p.size() - 1 : i - 1; }
};

template <typename T>
struct convex : polygon<T>
{
    // 旋转卡壳
    // 最小的宽度
    long double rotcaliper_min() const
    {
        const auto &p = this->p;
        if (p.size() == 1 || p.size() == 2)
            return 0;
        const auto area = [](const point<T> &u, const point<T> &v, const point<T> &w)
        { return (w - u) ^ (w - v); };
        double ans = 1e9;
        for (size_t i = 0, j = 1; i < p.size(); i++)
        {
            const auto nxti = this->nxt(i);
            line<int> l = line<int>(p[i], p[nxti] - p[i]);
            double tmpans = l.dis(p[j]);
            while (area(p[this->nxt(j)], p[i], p[nxti]) >= area(p[j], p[i],
                                                                p[nxti]))
            {
                j = this->nxt(j);
                tmpans = max(tmpans, l.dis(p[j]));
            }
            ans = min(ans, tmpans);
        }
        return ans;
    }
};
using Convex = convex<int>;

Convex convexhull(vector<Point> p)
{
    vector<Point> st;
    if (p.empty())
        return Convex{st};
    sort(p.begin(), p.end());
    const auto check = [](const vector<Point> &st, const Point &u)
    {
        const auto back1 = st.back(), back2 = *prev(st.end(), 2);
        return (back1 - back2).toleft(u - back2) <= 0;
    };
    for (const Point &u : p)
    {
        while (st.size() > 1 && check(st, u))
            st.pop_back();
        st.push_back(u);
    }
    size_t k = st.size();
    p.pop_back();
    reverse(p.begin(), p.end());
    for (const Point &u : p)
    {
        while (st.size() > k && check(st, u))
            st.pop_back();
        st.push_back(u);
    }
    st.pop_back();
    return Convex{st};
}

double sol(int N)
{
    vector<Point> poi_vec;
    for (int i = 0; i < N; i++)
    {
        int x, y;
        cin >> x >> y;
        poi_vec.push_back(Point(x, y));
    }
    auto convex_hull = convexhull(poi_vec);
    auto ans = convex_hull.rotcaliper_min();
    return ans;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int ind = 0;
    while (true)
    {
        ind++;
        int N;
        cin >> N;
        if (N == 0)
        {
            break;
        }
        else
        {
            auto ans = sol(N);
            cout << "Case " << ind << ": "
                 << fixed << setprecision(2) << ans + 0.005 << "\n";
        }
    }
}
```

## 参考

* https://oi-wiki.org
