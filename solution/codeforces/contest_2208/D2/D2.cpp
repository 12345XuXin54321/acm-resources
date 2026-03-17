#include <bits/stdc++.h>
using namespace std;

#define max_len 8010

struct DSU
{
    int fa_arr[max_len];
    int size;
    int component_cnt;
    void init(int n)
    {
        size = component_cnt = n;
        for (int i = 0; i < n; i++)
        {
            fa_arr[i] = i;
        }
    }
    int qry_fa(int u)
    {
        if (u == fa_arr[u])
            return u;
        auto fa = qry_fa(fa_arr[u]);
        fa_arr[u] = fa;
        return fa;
    }
    bool merge(int u, int v)
    {
        int fa1 = qry_fa(u), fa2 = qry_fa(v);
        if (fa1 != fa2)
        {
            fa_arr[fa2] = fa1;
            component_cnt--;
            return true;
        }
        else
        {
            return false;
        }
    }
} node_dsu;

struct tree_node
{
    int reachable_cnt;
    vector<int> can_reach_nodes;
    vector<int> children;
} node_arr[max_len];

bitset<max_len> can_reach_arr[max_len];
vector<int> sorted_node;
bool is_visited_arr[max_len];

bitset<max_len> str_arr[max_len];
int N;

inline bool cmp_reachable_cnt(const int &a, const int &b)
{
    return node_arr[a].reachable_cnt > node_arr[b].reachable_cnt;
}

bool dfs_get_children(int ri)
{
    if (is_visited_arr[ri] == true)
    {
        return true;
    }

    is_visited_arr[ri] = true;

    for (int i = 0; i < N; i++)
    {
        if (i != ri && str_arr[ri][i] == true)
        {
            node_arr[ri].can_reach_nodes.push_back(i);
        }
    }

    sort(node_arr[ri].can_reach_nodes.begin(),
         node_arr[ri].can_reach_nodes.end(), cmp_reachable_cnt);

    can_reach_arr[ri][ri] = true;

    for (auto nxt : node_arr[ri].can_reach_nodes)
    {
        if (ri != nxt &&
            can_reach_arr[ri][nxt] == false)
        {
            node_arr[ri].children.push_back(nxt);
            if (node_dsu.merge(ri, nxt) == false)
                return false;

            if (dfs_get_children(nxt) == false)
                return false;

            can_reach_arr[ri] |= can_reach_arr[nxt];
        }
    }
    if (can_reach_arr[ri] != str_arr[ri])
    {
        return false;
    }

    return true;
}

void init_data(int n)
{
    for (int i = 0; i < n + 10; i++)
    {
        node_arr[i] = {};
        is_visited_arr[i] = {};
        can_reach_arr[i] = 0;
    }
    node_dsu.init(n);
}

bool get_ans()
{
    sorted_node = vector<int>(N);
    for (int i = 0; i < N; i++)
    {
        sorted_node[i] = i;
    }
    sort(sorted_node.begin(), sorted_node.end(), cmp_reachable_cnt);

    for (auto ri : sorted_node)
    {
        if (is_visited_arr[ri] == true)
            continue;

        if (dfs_get_children(ri) == false)
            return false;
    }

    return node_dsu.component_cnt == 1;
}

void sol()
{
    cin >> N;
    init_data(N);
    string str;
    for (int i = 0; i < N; i++)
    {
        cin >> str;
        reverse(str.begin(), str.end());
        str_arr[i] = bitset<max_len>(str);
        node_arr[i].reachable_cnt = str_arr[i].count();
    }
    if (get_ans())
    {
        cout << "Yes\n";
        for (int i = 0; i < N; i++)
        {
            sort(node_arr[i].children.begin(), node_arr[i].children.end());
            for (auto ch : node_arr[i].children)
            {
                cout << i + 1 << " " << ch + 1 << "\n";
            }
        }
    }
    else
    {
        cout << "No\n";
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
