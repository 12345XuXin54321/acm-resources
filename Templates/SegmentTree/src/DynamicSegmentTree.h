#include <bits/stdc++.h>

using namespace std;

// 区间加
// 求区间和
class DynamicSegmentTree
{
    struct tree_node
    {
        int sum;
        int lazy;

        int64_t l, r;
        int lch = -1, rch = -1;

        int get_mid() const
        {
            return (l + r) / 2;
        }
    };

    vector<tree_node> node_arr;
    static constexpr int64_t ind_L = -1e9, ind_R = 1e9;

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
            node_arr[lch].l = node_arr[now_i].l;
            node_arr[lch].r = node_arr[now_i].get_mid();
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
            node_arr[rch].l = node_arr[now_i].get_mid() + 1;
            node_arr[rch].r = node_arr[now_i].r;
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

    void push_down(int now_i)
    {
        int l = node_arr[now_i].l;
        int r = node_arr[now_i].r;
        int mid = node_arr[now_i].get_mid();
        node_arr[Lch(now_i)].sum += node_arr[now_i].lazy * (mid - l + 1);
        node_arr[Lch(now_i)].lazy += node_arr[now_i].lazy;

        node_arr[Rch(now_i)].sum += node_arr[now_i].lazy * (r - mid);
        node_arr[Rch(now_i)].lazy += node_arr[now_i].lazy;

        node_arr[now_i].lazy = 0;
    }

    void push_up(int now_i)
    {
        int l = node_arr[now_i].l;
        int r = node_arr[now_i].r;
        int lv = 0, rv = 0;
        if (has_Lch(now_i))
            lv = node_arr[Lch(now_i)].sum;
        if (has_Rch(now_i))
            rv = node_arr[Rch(now_i)].sum;
        node_arr[now_i].sum = lv + rv +
                              node_arr[now_i].lazy * (r - l + 1);
    }

    void add_val(int now_i, int cl, int cr, int d)
    {
        int l = node_arr[now_i].l;
        int r = node_arr[now_i].r;
        if (l == cl && r == cr)
        {
            node_arr[now_i].sum += d * (r - l + 1);
            node_arr[now_i].lazy += d;
        }
        else
        {
            push_down(now_i);

            int mid = node_arr[now_i].get_mid();
            if (cr <= mid)
            {
                add_val(Lch(now_i), cl, cr, d);
            }
            else if (cl > mid)
            {
                add_val(Rch(now_i), cl, cr, d);
            }
            else
            {
                add_val(Lch(now_i), cl, mid, d);
                add_val(Rch(now_i), mid + 1, cr, d);
            }

            push_up(now_i);
        }
    }

    int query_sum(int now_i, int ql, int qr)
    {
        int l = node_arr[now_i].l;
        int r = node_arr[now_i].r;
        if (l == ql && r == qr)
        {
            return node_arr[now_i].sum;
        }
        else
        {
            int mid = node_arr[now_i].get_mid();
            if (qr <= mid)
            {
                int lv = 0;
                if (has_Lch(now_i))
                    lv = query_sum(Lch(now_i), ql, qr);
                return lv + node_arr[now_i].lazy * (qr - ql + 1);
            }
            else if (ql > mid)
            {
                int rv = 0;
                if (has_Rch(now_i))
                    rv = query_sum(Rch(now_i), ql, qr);
                return rv + node_arr[now_i].lazy * (qr - ql + 1);
            }
            else
            {
                int lv = 0, rv = 0;
                if (has_Lch(now_i))
                    lv = query_sum(Lch(now_i), ql, mid);
                if (has_Rch(now_i))
                    rv = query_sum(Rch(now_i), mid + 1, qr);
                return (lv + rv) + node_arr[now_i].lazy * (qr - ql + 1);
            }
        }
    }

public:
    void init()
    {
        node_arr.clear();
        int root_i = create_new_node();
        node_arr[root_i].l = ind_L;
        node_arr[root_i].r = ind_R;
    }

    void add_val(int cl, int cr, int d)
    {
        add_val(0, cl, cr, d);
    }

    int query_sum(int ql, int qr)
    {
        return query_sum(0, ql, qr);
    }
};