#include <bits/stdc++.h>

using namespace std;

#define int int64_t

// 区间加
// 求区间和
class PersistentSegmentTree
{
    struct tree_node
    {
        int sum;
        int lazy;

        int lch = -1, rch = -1;
    };

    vector<tree_node> node_arr;
    int64_t ind_L = -1e9, ind_R = 1e9;
    vector<int> versions;

    int create_new_node()
    {
        node_arr.push_back(tree_node());
        return node_arr.size() - 1;
    }

    int Lch(int now_i)
    {
        int lch = node_arr[now_i].lch;
        if (lch == -1)
        {
            lch = create_new_node();
            node_arr[now_i].lch = lch;
        }
        return lch;
    }
    int Rch(int now_i)
    {
        int rch = node_arr[now_i].rch;
        if (rch == -1)
        {
            rch = create_new_node();
            node_arr[now_i].rch = rch;
        }
        return rch;
    }
    bool has_Lch(const int now_i) const
    {
        return node_arr[now_i].lch != -1;
    }
    bool has_Rch(const int now_i) const
    {
        return node_arr[now_i].rch != -1;
    }

    void build_tree(int now_i, int64_t l, int64_t r)
    {
        if (l == r)
        {
            node_arr[now_i].sum = 0;
        }
        else
        {
            auto mid = (l + r) / 2;
            build_tree(Lch(now_i), l, mid);
            build_tree(Rch(now_i), mid + 1, r);
            node_arr[now_i].sum =
                node_arr[Lch(now_i)].sum + node_arr[Rch(now_i)].sum;
        }
    }

    int copy(int src)
    {
        int dest = create_new_node();
        node_arr[dest] = node_arr[src];
        return dest;
    }

    int add_val(int now_i, int64_t l, int64_t r, int cl, int cr, int d)
    {
        now_i = copy(now_i);
        if (l == cl && r == cr)
        {
            node_arr[now_i].lazy += d;
        }
        else
        {
            int64_t mid = (l + r) / 2;
            node_arr[now_i].sum += (cr - cl + 1) * d;
            if (cr <= mid)
            {
                node_arr[now_i].lch = add_val(Lch(now_i), l, mid, cl, cr, d);
            }
            else if (cl > mid)
            {
                node_arr[now_i].rch = add_val(Rch(now_i), mid + 1, r, cl, cr, d);
            }
            else
            {
                node_arr[now_i].lch = add_val(Lch(now_i), l, mid, cl, mid, d);
                node_arr[now_i].rch = add_val(Rch(now_i), mid + 1, r, mid + 1, cr, d);
            }
        }
        return now_i;
    }

    int query_sum(int now_i, int64_t l, int64_t r, int ql, int qr)
    {
        if (l == ql && r == qr)
        {
            return node_arr[now_i].sum +
                   (qr - ql + 1) * node_arr[now_i].lazy;
        }
        else
        {
            int64_t mid = (l + r) / 2;
            int sum = node_arr[now_i].lazy * (qr - ql + 1);
            if (qr <= mid)
            {
                if (has_Lch(now_i))
                    sum += query_sum(Lch(now_i), l, mid, ql, qr);
            }
            else if (ql > mid)
            {
                if (has_Rch(now_i))
                    sum += query_sum(Rch(now_i), mid + 1, r, ql, qr);
            }
            else
            {
                if (has_Lch(now_i))
                    sum += query_sum(Lch(now_i), l, mid, ql, mid);
                if (has_Rch(now_i))
                    sum += query_sum(Rch(now_i), mid + 1, r, mid + 1, qr);
            }
            return sum;
        }
    }

public:
    int init(int l, int r)
    {
        node_arr.clear();
        versions.clear();
        int root_i = create_new_node();
        versions.push_back(root_i);
        ind_L = l, ind_R = r;
        build_tree(root_i, ind_L, ind_R);
        return root_i;
    }

    int add_val(int ver, int cl, int cr, int d)
    {
        int new_ver = add_val(versions[ver], ind_L, ind_R, cl, cr, d);
        versions.push_back(new_ver);
        return versions.size() - 1;
    }

    int query_sum(int ver, int ql, int qr)
    {
        return query_sum(versions[ver], ind_L, ind_R, ql, qr);
    }
};

PersistentSegmentTree segtree;

void sol()
{
    int N, M;
    int Q;
    cin >> N >> M >> Q;
    vector<int> ver_arr(N + 10);
    ver_arr[0] = segtree.init(1, M);
    for (int i = 1; i <= N; i++)
    {
        ver_arr[i] = segtree.add_val(ver_arr[0], 1, M, 0);
    }
    for (int i = 0; i < Q; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x, y;
            cin >> x >> y;
            ver_arr[x] = segtree.add_val(ver_arr[y], 1, M, 0);
        }
        else if (op == 2)
        {
            int x, y, z;
            cin >> x >> y >> z;
            int val = segtree.query_sum(ver_arr[x], y, y);
            ver_arr[x] = segtree.add_val(ver_arr[x], y, y, z - val);
        }
        else
        {
            int x, l, r;
            cin >> x >> l >> r;
            int ans = segtree.query_sum(ver_arr[x], l, r);
            cout << ans << "\n";
        }
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        sol();
    }
}