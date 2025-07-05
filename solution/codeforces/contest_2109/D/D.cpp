#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define max_len 200010
#define INF (int(1e12))
int N;

struct node
{
    vector<int> linked;
} node_arr[max_len];

void link_node(int u, int v)
{
    node_arr[u].linked.push_back(v);
    node_arr[v].linked.push_back(u);
}

int odd_dis[max_len], even_dis[max_len];

void init_dis()
{
    for (int i = 0; i < N + 10; i++)
    {
        odd_dis[i] = even_dis[i] = INF;
    }
}
void init_node()
{
    for (int i = 0; i < N + 10; i++)
    {
        node_arr[i] = {};
    }
}

void dij()
{
    init_dis();
    // dis, ni
    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    pq.push({0, 1});

    while (pq.size() != 0)
    {
        auto [dis, ni] = pq.top();
        pq.pop();

        if (dis % 2 == 0)
        {
            if (even_dis[ni] != INF)
            {
                continue;
            }
            even_dis[ni] = dis;

            for (auto lk : node_arr[ni].linked)
            {
                if (odd_dis[lk] == INF)
                {
                    pq.push({dis + 1, lk});
                }
            }
        }
        else
        {
            if (odd_dis[ni] != INF)
            {
                continue;
            }
            odd_dis[ni] = dis;
            for (auto lk : node_arr[ni].linked)
            {
                if (even_dis[lk] == INF)
                {
                    pq.push({dis + 1, lk});
                }
            }
        }
    }
}

int Aarr[max_len];
int max_odd, max_ev;
// odd -> 1, 3, ..., val
// eve -> 0, 2, ..., val

void sol()
{
    int m, l;
    cin >> N >> m >> l;
    init_node();
    max_odd = -1, max_ev = -1;
    int min_odd = INF, min_ev = INF;
    int sum = 0;
    for (int i = 0; i < l; i++)
    {
        cin >> Aarr[i];
        sum += Aarr[i];
        if (Aarr[i] % 2 == 0)
        {
            min_ev = min(min_ev, Aarr[i]);
        }
        else
        {
            min_odd = min(min_odd, Aarr[i]);
        }
    }

    if (sum % 2 == 0)
    {
        max_ev = sum;
        if (min_odd != INF)
        {
            max_odd = sum - min_odd;
        }
        else
        {
            max_odd = -1;
        }
    }
    else
    {
        max_odd = sum;
        max_ev = sum - min_odd;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        link_node(u, v);
    }
    dij();

    for (int i = 1; i <= N; i++)
    {
        int flag = 0;
        if (odd_dis[i] != INF && max_odd >= odd_dis[i])
        {
            flag = 1;
        }
        if (even_dis[i] != INF && max_ev >= even_dis[i])
        {
            flag = 1;
        }
        cout << flag;
    }
    cout << "\n";
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