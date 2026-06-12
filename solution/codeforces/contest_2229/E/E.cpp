#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define max_len 200010

#define mod_n 998244353
#define mod(x) ((x) % mod_n)

struct Mint
{
    int val;
    Mint() = default;
    Mint(int v) : val(mod(v)) {}
    Mint operator+(const Mint &r) const
    {
        return mod(0ll + val + r.val);
    }
    Mint operator-(const Mint &r) const
    {
        return mod(mod_n + val - r.val);
    }
    Mint &operator+=(const Mint &r)
    {
        val = mod(0ll + val + r.val);
        return *this;
    }
    Mint &operator-=(const Mint &r)
    {
        val = mod(0ll + mod_n + val - r.val);
        return *this;
    }
    Mint operator*(const Mint &r) const
    {
        return mod(1ll * val * r.val);
    }
};

struct NodeTag
{
    Mint add;

    NodeTag() = default;
    NodeTag(Mint _add) : add(_add) {}

    // 先应用当前tag，再应用other
    void compose(const NodeTag &other)
    {
        add += other.add;
    }
};

struct NodeInfo
{
    Mint sum;

    NodeInfo() = default;
    NodeInfo(Mint _sum) : sum(_sum) {}

    static NodeInfo merge(const NodeInfo &a, const NodeInfo &b)
    {
        NodeInfo res(
            a.sum + b.sum);
        return res;
    }

    NodeInfo &apply(const NodeTag &t, Mint len)
    {
        sum += (t.add * len);
        return *this;
    }
};

// 初始化数组
// 区间加
// 求区间和
class SegmentTree
{
#define Lch(ind) ((ind) * 2)
#define Rch(ind) ((ind) * 2 + 1)
    struct tree_node
    {
        NodeInfo info;
        NodeTag tag;
    } node_arr[max_len * 4];

    int ind_L, ind_R;

    void push_down(int now_i, int l, int r)
    {
        int mid = (l + r) / 2;
        auto &tag = node_arr[now_i].tag;

        node_arr[Lch(now_i)].info.apply(tag, mid - l + 1);
        node_arr[Rch(now_i)].info.apply(tag, r - mid);

        node_arr[Lch(now_i)].tag.compose(tag);
        node_arr[Rch(now_i)].tag.compose(tag);

        tag = NodeTag();
    }

    void push_up(int now_i, int l, int r)
    {
        node_arr[now_i].info =
            NodeInfo::merge(node_arr[Lch(now_i)].info, node_arr[Rch(now_i)].info)
                .apply(node_arr[now_i].tag, r - l + 1);
    }

    void build_tree(int now_i, int l, int r)
    {
        if (l == r)
        {
            node_arr[now_i].info = NodeInfo();
            node_arr[now_i].tag = NodeTag();
        }
        else
        {
            node_arr[now_i].tag = NodeTag();

            int mid = (l + r) / 2;
            build_tree(Lch(now_i), l, mid);
            build_tree(Rch(now_i), mid + 1, r);
            push_up(now_i, l, r);
        }
    }

    void range_update(int now_i, int l, int r, int cl, int cr, const NodeTag &t)
    {
        if (l == cl && r == cr)
        {
            node_arr[now_i].info.apply(t, cr - cl + 1);
            node_arr[now_i].tag.compose(t);
        }
        else
        {
            push_down(now_i, l, r);

            int mid = (l + r) / 2;
            if (cr <= mid)
            {
                range_update(Lch(now_i), l, mid, cl, cr, t);
            }
            else if (cl > mid)
            {
                range_update(Rch(now_i), mid + 1, r, cl, cr, t);
            }
            else
            {
                range_update(Lch(now_i), l, mid, cl, mid, t);
                range_update(Rch(now_i), mid + 1, r, mid + 1, cr, t);
            }

            push_up(now_i, l, r);
        }
    }

    NodeInfo query(int now_i, int l, int r, int ql, int qr)
    {
        if (l == ql && r == qr)
        {
            return node_arr[now_i].info;
        }
        else
        {
            int mid = (l + r) / 2;
            int len = qr - ql + 1;

            if (qr <= mid)
            {
                return query(Lch(now_i), l, mid, ql, qr).apply(node_arr[now_i].tag, len);
            }
            else if (ql > mid)
            {
                return query(Rch(now_i), mid + 1, r, ql, qr).apply(node_arr[now_i].tag, len);
            }
            else
            {
                auto lv = query(Lch(now_i), l, mid, ql, mid);
                auto rv = query(Rch(now_i), mid + 1, r, mid + 1, qr);
                return NodeInfo::merge(lv, rv).apply(node_arr[now_i].tag, len);
            }
        }
    }

public:
    void build_tree(int l, int r)
    {
        ind_L = l, ind_R = r;
        build_tree(1, ind_L, ind_R);
    }

    void range_update(int cl, int cr, const NodeTag &t)
    {
        range_update(1, ind_L, ind_R, cl, cr, t);
    }

    NodeInfo query(int ql, int qr)
    {
        return query(1, ind_L, ind_R, ql, qr);
    }

    void modify_to0(int ind)
    {
        auto sum = query(ind, ind).sum;
        range_update(ind, ind, NodeTag{-sum.val});
    }
};

struct tree_node
{
    vector<int> linked;

    int fa;
    vector<int> child;

    bool is_vis;
    int subtree_max;
} node_arr[max_len];

void linked_treenode(int u, int v)
{
    node_arr[u].linked.push_back(v);
    node_arr[v].linked.push_back(u);
}

Mint dp_arr[max_len];
SegmentTree dp_suf;

int N;

void init_data(int n)
{
    for (int i = 0; i < n + 10; i++)
    {
        node_arr[i] = {};
        dp_arr[i] = {};
    }
    dp_suf.build_tree(1, N);
}

void dfs1(int ri, int fa)
{
    node_arr[ri].fa = fa;
    node_arr[ri].child = {};
    int subtree_max = ri;
    for (auto lk : node_arr[ri].linked)
    {
        if (lk != fa)
        {
            node_arr[ri].child.push_back(lk);
            dfs1(lk, ri);
            subtree_max = max(subtree_max, node_arr[lk].subtree_max);
        }
    }
    node_arr[ri].subtree_max = subtree_max;
}

int get_ans()
{
    int max_leaf = 0;
    for (int i = 1; i <= N; i++)
    {
        if (node_arr[i].child.size() == 0)
            max_leaf = i;
    }

    vector<int> root_ch_subtree_max_idx;
    for (auto ch : node_arr[N].child)
    {
        root_ch_subtree_max_idx.push_back(node_arr[ch].subtree_max);
    }
    sort(root_ch_subtree_max_idx.begin(), root_ch_subtree_max_idx.end(), greater());
    int largest_2nd_idx = 0;
    if (root_ch_subtree_max_idx.size() >= 2)
    {
        largest_2nd_idx = root_ch_subtree_max_idx[1];
    }

    if (largest_2nd_idx == 0)
        return 1;

    dp_suf.range_update(N, N, NodeTag(1));
    set<int> leaf_set = {N};

    for (int i = N - 1; i >= max_leaf; i--)
    {
        if (node_arr[i].is_vis == false)
        {
            node_arr[i].is_vis = true;
            int fa = node_arr[i].fa;
            while (fa != -1)
            {
                if (leaf_set.count(fa))
                {
                    leaf_set.erase(fa);
                }

                dp_suf.modify_to0(fa);

                if (node_arr[fa].is_vis == true)
                    break;
                node_arr[fa].is_vis = true;
                fa = node_arr[fa].fa;
            }
            leaf_set.insert(i);
            auto val = dp_suf.query(i + 1, N).sum;

            if (leaf_set.size() == 1)
            {
                val = 1;
            }
            else if (largest_2nd_idx < i)
            {
                val = val + 1;
            }

            dp_suf.range_update(i, i, NodeTag(val));
            dp_arr[i] = val;
        }
    }
    Mint ans = dp_arr[max_leaf].val;
    return ans.val;
}

void sol()
{
    cin >> N;
    init_data(N);
    for (int i = 1; i < N; i++)
    {
        int u, v;
        cin >> u >> v;
        linked_treenode(u, v);
    }
    dfs1(N, -1);

    int ans = get_ans();
    cout << ans << "\n";
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
