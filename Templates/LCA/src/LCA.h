#include <bits/stdc++.h>
using namespace std;

#define max_len 500010

class LCA
{
    struct tree_node
    {
        vector<int> connected_nodes;
        vector<int> parents;
        int dep;
    } node_arr[max_len];

    int root_ind;
    vector<int> dfs_nodes;
    void dfs(int ni)
    {
        int len = dfs_nodes.size();
        for (int i = 1; i <= len; i *= 2)
        {
            node_arr[ni].parents.push_back(dfs_nodes[len - i]);
        }
        node_arr[ni].dep = len;

        int fa = -1;
        if (dfs_nodes.size() != 0)
        {
            fa = dfs_nodes.back();
        }

        dfs_nodes.push_back(ni);

        for (auto ch : node_arr[ni].connected_nodes)
        {
            if (ch != fa)
                dfs(ch);
        }

        dfs_nodes.pop_back();
    }

public:
    void link_node(int u, int v)
    {
        node_arr[u].connected_nodes.push_back(v);
        node_arr[v].connected_nodes.push_back(u);
    }

    void preprocessing(int root_i)
    {
        root_ind = root_i;
        dfs(root_i);
    }

    int lca(int u, int v)
    {
        if (node_arr[u].dep < node_arr[v].dep)
        {
            swap(u, v);
        }

        // dep(u) >= dep(v)
        while (node_arr[u].dep > node_arr[v].dep)
        {
            for (int i = node_arr[u].parents.size() - 1; i >= 0; i--)
            {
                int u_parent = node_arr[u].parents[i];
                if (node_arr[u_parent].dep >= node_arr[v].dep)
                {
                    u = u_parent;
                    break;
                }
            }
        }

        // dep(u) == dep(v)
        while (u != v)
        {
            if (node_arr[u].parents.front() ==
                node_arr[v].parents.front())
            {
                u = v = node_arr[u].parents.front();
                break;
            }

            int len = node_arr[u].parents.size();

            for (int i = len - 1; i >= 0; i--)
            {
                if (node_arr[u].parents[i] !=
                    node_arr[v].parents[i])
                {
                    u = node_arr[u].parents[i];
                    v = node_arr[v].parents[i];
                    break;
                }
            }
        }
        return u;
    }
};

