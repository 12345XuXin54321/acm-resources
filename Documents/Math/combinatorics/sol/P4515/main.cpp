#include <bits/stdc++.h>
using namespace std;
struct triangle
{
    int64_t x, y, r;
    triangle() {}
    triangle(int xx, int yy, int rr)
    {
        x = xx, y = yy, r = rr;
    }
    double area()
    {
        return r * r / 2.0;
    }
} triangle_arr[20];

triangle triangle_merge(triangle &l, triangle &r)
{
    if (r.x <= l.x)
    {
        if (r.y >= l.y)
        {
            if (r.y - l.y >= l.r || l.x - r.x >= r.r)
            {
                return triangle(0, 0, 0);
            }
            else // r.y - l.y < l.r && l.x - r.x < r.r
            {
                return triangle(l.x, r.y,
                                min(r.r - (l.x - r.x),
                                    l.r - (r.y - l.y)));
            }
        }
        else // r.y <= l.y
        {
            int64_t dx = l.x - r.x, dy = l.y - r.y;
            if (dx >= 0 && dy >= 0 && r.r - dx - dy > 0)
            {
                return triangle(l.x, l.y,
                                min(r.r - dx - dy, l.r));
            }
            else
            {
                return triangle(0, 0, 0);
            }
        }
    }
    else
        return triangle_merge(r, l);
}

void sol()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >>
            triangle_arr[i].x >>
            triangle_arr[i].y >>
            triangle_arr[i].r;
    }
    // {三角形的交集}, 交集
    queue<pair<list<int>, triangle>> que;
    double sum = 0;

    for (int i = 0; i < N; i++)
    {
        sum += triangle_arr[i].area();
        que.push(make_pair(list({i}), triangle_arr[i]));
    }

    while (que.size() != 0)
    {
        auto que_front = que.front();
        que.pop();
        int cnt = que_front.first.size();
        assert(cnt > 0);
        double b = ((cnt + 1) % 2 == 0) ? -1 : 1;

        int i = que_front.first.back() + 1;
        for (; i < N; i++)
        {
            auto utri = triangle_merge(que_front.second, triangle_arr[i]);
            if (utri.r != 0)
            {
                auto nxt_list = que_front.first;
                nxt_list.push_back(i);
                que.push(make_pair(nxt_list, utri));
                sum += (b * utri.area() * (1LL << cnt));
            }
        }
    }
    printf("%.1lf\n", sum);
}

int main()
{
    sol();
}