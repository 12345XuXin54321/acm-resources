#include <bits/stdc++.h>

using namespace std;

#define max_len 100010

struct NodeTag
{
    int add;

    NodeTag() = default;
    NodeTag(int _add) : add(_add) {}

    // 先应用当前tag，再应用other
    void compose(const NodeTag &other)
    {
        add += other.add;
    }
};

struct NodeInfo
{
    int sum;
    int max_val, min_val;

    NodeInfo() = default;
    NodeInfo(int _val) : sum(_val), max_val(_val), min_val(_val) {}

    static NodeInfo merge(const NodeInfo &a, const NodeInfo &b)
    {
        NodeInfo res;
        res.sum = a.sum + b.sum;
        res.max_val = max(a.max_val, b.max_val);
        res.min_val = min(a.min_val, b.min_val);
        return res;
    }

    NodeInfo &apply(const NodeTag &t, int len)
    {
        max_val += t.add;
        min_val += t.add;
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

    void build_tree(int now_i, int l, int r, int *arr)
    {
        if (l == r)
        {
            node_arr[now_i].info = NodeInfo(arr[l]);
            node_arr[now_i].tag = NodeTag();
        }
        else
        {
            node_arr[now_i].tag = NodeTag();

            int mid = (l + r) / 2;
            build_tree(Lch(now_i), l, mid, arr);
            build_tree(Rch(now_i), mid + 1, r, arr);
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
    void build_tree(int l, int r, int *arr)
    {
        ind_L = l, ind_R = r;
        build_tree(1, ind_L, ind_R, arr);
    }

    void range_update(int cl, int cr, const NodeTag &t)
    {
        range_update(1, ind_L, ind_R, cl, cr, t);
    }

    NodeInfo query(int ql, int qr)
    {
        return query(1, ind_L, ind_R, ql, qr);
    }
};