#include <bits/stdc++.h>
using namespace std;
#define max_len 200
struct tree_node
{
    int64_t lch, rch;
    int64_t fa;
    int64_t val;
} node_arr[max_len];

int N;

void input_data()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int64_t val, lc, rc;
        cin >> val >> lc >> rc;
        node_arr[i + 1].val = val;
        node_arr[i + 1].lch = lc;
        node_arr[i + 1].rch = rc;

        if (lc != 0)
            node_arr[lc].fa = i + 1;
        if (rc != 0)
            node_arr[rc].fa = i + 1;
    }
}

int64_t get_val(int root_i, int from_i, int64_t lay)
{
    // cout << root_i << " " << from_i << " " << lay << endl;
    if (root_i == 0)
    {
        return 0;
    }
    else
    {
        int64_t ch_val = 0;
        if (node_arr[root_i].fa != from_i)
        {
            ch_val += get_val(node_arr[root_i].fa,
                              root_i, lay + 1);
        }
        if (node_arr[root_i].lch != from_i)
        {
            ch_val += get_val(node_arr[root_i].lch,
                              root_i, lay + 1);
        }
        if (node_arr[root_i].rch != from_i)
        {
            ch_val += get_val(node_arr[root_i].rch,
                              root_i, lay + 1);
        }
        return ch_val + node_arr[root_i].val * lay;
    }
}

void sol()
{
    input_data();
    int64_t min_val = get_val(1, -1, 0);
    for (int i = 1; i < N; i++)
    {
        min_val = min(min_val, get_val(i + 1, -1, 0));
    }
    cout << min_val << "\n";
}

int32_t main()
{
    sol();
}