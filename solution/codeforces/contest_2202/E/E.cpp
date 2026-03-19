#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define max_len 300010
#define mod_n 998244353
#define mod(x) ((x) % mod_n)

class Mint
{
    int val;

public:
    Mint() = default;
    Mint(int _v) : val(_v) {};

    void operator+=(int v) { val = mod(val + v); }
    void operator-=(int v) { val = mod(mod_n + mod(val - v)); }
    void operator*=(int v) { val = mod(val * v); }

    Mint operator+(int v) const { return mod(val + v); }
    Mint operator-(int v) const { return mod(mod_n + mod(val - v)); }
    Mint operator*(int v) const { return mod(val * v); }

    operator int() { return mod(val); }
};

template <typename T>
class SegmentTree
{
#define Lch(ind) ((ind) * 2)
#define Rch(ind) ((ind) * 2 + 1)
    struct tree_node
    {
        T sum;
        T lazy;
    } node_arr[max_len * 4];

    int ind_L, ind_R;

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

    void build_tree(int now_i, int l, int r)
    {
        if (l == r)
        {
            node_arr[now_i].sum = 0;
            node_arr[now_i].lazy = 0;
        }
        else
        {
            node_arr[now_i].lazy = 0;

            int mid = (l + r) / 2;
            build_tree(Lch(now_i), l, mid);
            build_tree(Rch(now_i), mid + 1, r);
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

public:
    void build_tree(int l, int r)
    {
        ind_L = l, ind_R = r;
        build_tree(1, ind_L, ind_R);
    }

    void add_val(int cl, int cr, int d)
    {
        add_val(1, ind_L, ind_R, cl, cr, d);
    }

    int query_sum(int ql, int qr)
    {
        return query_sum(1, ind_L, ind_R, ql, qr);
    }
};

Mint qpow(Mint n, int x)
{
    if (x == 0)
        return 1;
    else if (x == 1)
        return n;
    else if (x % 2 == 0)
        return qpow(n * n, x / 2);
    else
        return n * qpow(n * n, x / 2);
}

int N;
string str;

SegmentTree<Mint> endwith_Lparen, endwith_Rparen;
int str_pre[max_len];

int get_ans()
{
    str_pre[0] = 1;
    for (int i = 1; i < N; i++)
    {
        if (str[i] == '(')
        {
            str_pre[i] = str_pre[i - 1] + 1;
        }
        else
        {
            str_pre[i] = str_pre[i - 1] - 1;
        }
    }

    int pre_all_ge2_L = 0;
    endwith_Lparen.add_val(0, 0, 1);
    for (int i = 1; i < N; i++)
    {
        if (str_pre[i - 1] < 2)
        {
            pre_all_ge2_L = i;
        }
        Mint cnt = 1;

        cnt += endwith_Rparen.query_sum(0, i - 1);
        if (pre_all_ge2_L <= i - 1)
        {
            cnt += endwith_Lparen.query_sum(pre_all_ge2_L, i - 1);
        }

        if (str[i] == '(')
        {
            endwith_Lparen.add_val(i, i, cnt);
        }
        else
        {
            endwith_Rparen.add_val(i, i, cnt);
        }
    }

    Mint ans = 0;
    pre_all_ge2_L = 0;
    for (int i = 0; i < N; i++)
    {
        if (str_pre[i - 1] < 2)
        {
            pre_all_ge2_L = i;
        }
        if (str[i] == '(')
        {
            ans += qpow(2, i);
        }
        else
        {
            ans += 1;
            if (i != 0)
            {
                ans += endwith_Rparen.query_sum(0, i - 1);
                if (pre_all_ge2_L <= i - 1)
                {
                    ans += endwith_Lparen.query_sum(pre_all_ge2_L, i - 1);
                }
            }
        }
    }
    return int(ans);
}

void sol()
{
    cin >> N >> str;
    endwith_Lparen.build_tree(0, N + 10);
    endwith_Rparen.build_tree(0, N + 10);
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