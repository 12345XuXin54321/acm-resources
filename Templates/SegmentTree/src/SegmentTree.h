#define max_len 100010

// 初始化数组
// 区间加
// 求区间和
struct SegmentTree
{
#define Lch(ind) ((ind) * 2)
#define Rch(ind) ((ind) * 2 + 1)
    struct tree_node
    {
        int sum;
        int lazy;
    } node_arr[max_len * 4];

    void push_down(int now_i, int l, int r)
    {
        int mid = (l + r) / 2;
        node_arr[Lch(now_i)].sum += node_arr[now_i].lazy * (mid - l + 1);
        node_arr[Lch(now_i)].lazy += node_arr[now_i].lazy;

        node_arr[Rch(now_i)].sum += node_arr[now_i].lazy * (r - mid);
        node_arr[Rch(now_i)].lazy += node_arr[now_i].lazy;

        node_arr[now_i].lazy = 0;
    }

    void push_up(int now_i, int l, int r)
    {
        node_arr[now_i].sum = node_arr[Lch(now_i)].sum +
                              node_arr[Rch(now_i)].sum +
                              node_arr[now_i].lazy * (r - l + 1);
    }

    void build_tree(int now_i, int l, int r, int *arr)
    {
        if (l == r)
        {
            node_arr[now_i].sum = arr[l];
            node_arr[now_i].lazy = 0;
        }
        else
        {
            node_arr[now_i].lazy = 0;

            int mid = (l + r) / 2;
            build_tree(Lch(now_i), l, mid, arr);
            build_tree(Rch(now_i), mid + 1, r, arr);
            push_up(now_i, l, r);
        }
    }

    void add_val(int now_i, int l, int r, int cl, int cr, int d)
    {
        if (l == cl && r == cr)
        {
            node_arr[now_i].sum += d * (r - l + 1);
            node_arr[now_i].lazy += d;
        }
        else
        {
            push_down(now_i, l, r);

            int mid = (l + r) / 2;
            if (cr <= mid)
            {
                add_val(Lch(now_i), l, mid, cl, cr, d);
            }
            else if (cl > mid)
            {
                add_val(Rch(now_i), mid + 1, r, cl, cr, d);
            }
            else
            {
                add_val(Lch(now_i), l, mid, cl, mid, d);
                add_val(Rch(now_i), mid + 1, r, mid + 1, cr, d);
            }

            push_up(now_i, l, r);
        }
    }

    int query_sum(int now_i, int l, int r, int ql, int qr)
    {
        if (l == ql && r == qr)
        {
            return node_arr[now_i].sum;
        }
        else
        {
            int mid = (l + r) / 2;
            if (qr <= mid)
            {
                return query_sum(Lch(now_i), l, mid, ql, qr) +
                       node_arr[now_i].lazy * (qr - ql + 1);
            }
            else if (ql > mid)
            {
                return query_sum(Rch(now_i), mid + 1, r, ql, qr) +
                       node_arr[now_i].lazy * (qr - ql + 1);
            }
            else
            {
                int lv = query_sum(Lch(now_i), l, mid, ql, mid);
                int rv = query_sum(Rch(now_i), mid + 1, r, mid + 1, qr);
                return (lv + rv) + node_arr[now_i].lazy * (qr - ql + 1);
            }
        }
    }
};