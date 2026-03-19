#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define max_len 500010

struct tree_node
{
    vector<int> linked;
} node_arr[max_len];

int N, K, V;

void init_data(int n)
{
    for (int i = 0; i < n + 10; i++)
    {
        node_arr[i] = {};
    }
}

void link_node(int u, int v)
{
    node_arr[u].linked.push_back(v);
    node_arr[v].linked.push_back(u);
}

int get_nearest_leaf_dis(int ri, int fa)
{
    if (node_arr[ri].linked.size() == 1)
        return 0;

    vector<int> nearest_leaf_dis;
    for (auto ch : node_arr[ri].linked)
    {
        if (ch != fa)
        {
            int dis = get_nearest_leaf_dis(ch, ri);
            nearest_leaf_dis.push_back(dis + 1);
        }
    }
    sort(nearest_leaf_dis.begin(), nearest_leaf_dis.end());

    if (nearest_leaf_dis.size() == 1)
    {
        return nearest_leaf_dis[0];
    }
    else
    {
        int d1 = nearest_leaf_dis[0], d2 = nearest_leaf_dis[1];
        if (d1 + d2 - 2 < K)
        {
            return 0;
        }
        else
        {
            return d1;
        }
    }
}

void sol()
{
    cin >> N >> K >> V;
    init_data(N);

    for (int i = 1; i < N; i++)
    {
        int u, v;
        cin >> u >> v;
        link_node(u, v);
    }

    int dis = get_nearest_leaf_dis(V, -1);

    if (dis == 0)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
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
