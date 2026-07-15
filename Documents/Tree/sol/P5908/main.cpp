#include <bits/stdc++.h>
using namespace std;
#define max_len 100010
struct tree_node
{
    // node, len
    list<int> links;
} node_arr[max_len];

int d, N;

int dfs(int root_i, int from_i, int dis)
{
    int can_vis = (root_i != 1);
    for (auto ch_i : node_arr[root_i].links)
    {
        if (ch_i != from_i && dis + 1 <= d)
        {
            can_vis += dfs(ch_i, root_i, dis + 1);
        }
    }
    return can_vis;
}

void sol()
{
    cin >> N >> d;
    for (int i = 1; i < N; i++)
    {
        int u, v;
        cin >> u >> v;
        node_arr[u].links.push_back(v);
        node_arr[v].links.push_back(u);
    }
    cout << dfs(1, -1, 0) << "\n";
}

int main()
{
    sol();
}