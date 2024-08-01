#include <bits/stdc++.h>
using namespace std;
#define max_len 100100

int inorder[max_len];
int postorder[max_len];

int nodei_inorder[max_len];

int ans_nodei = -1;
int ans_sum = -1;

struct tree_node
{
    int lch, rch;
} bintree[max_len];

int N;

bool is_end = false;

void get_num(string &str, int *arr)
{
    N = 0;
    int num = 0;
    for (auto c : str)
    {
        if (c == ' ')
        {
            arr[N] = num;
            num = 0;
            N++;
        }
        else
        {
            num *= 10;
            num += (c - '0');
        }
    }
    if (str.back() != ' ')
    {
        arr[N] = num;
        N++;
    }
}

void input_data()
{
    ans_nodei = ans_sum = -1;
    string str;
    if (getline(cin, str))
    {
        get_num(str, inorder);

        getline(cin, str);
        get_num(str, postorder);

        for (int i = 0; i < N; i++)
        {
            nodei_inorder[inorder[i]] = i;
        }
        for (int i = 0; i < max_len; i++)
        {
            bintree[i] = {};
        }
    }
    else
    {
        is_end = true;
    }
}

void build_tree(int in_l, int in_r, int post_l, int post_r)
{
    if (in_l != in_r)
    {
        int root_i = postorder[post_r];
        bintree[root_i].lch = 0;
        bintree[root_i].rch = 0;

        int root_inorder = nodei_inorder[root_i];

        int ltree_size = root_inorder - in_l;
        int rtree_size = in_r - root_inorder;

        if (ltree_size != 0)
        {
            int lch_i = postorder[post_l + ltree_size - 1];
            bintree[root_i].lch = lch_i;
            build_tree(in_l, in_l + ltree_size - 1,
                       post_l, post_l + ltree_size - 1);
        }
        if (rtree_size != 0)
        {
            int rch_i = postorder[post_r - 1];
            bintree[root_i].rch = rch_i;

            build_tree(in_l + ltree_size + 1, in_r,
                       post_l + ltree_size, post_r - 1);
        }
    }
}

void update_ans(int ni, int sum)
{
    if (bintree[ni].lch == 0 &&
        bintree[ni].rch == 0)
    {
        if (ans_nodei == -1 ||
            (ans_sum > sum) ||
            (ans_sum == sum && ni < ans_nodei))
        {
            ans_nodei = ni;
            ans_sum = sum;
        }
    }
}

void dfs(int ri, int sum)
{
    if (ri == 0)
        return;
    sum += ri;
    update_ans(ri, sum);
    dfs(bintree[ri].lch, sum);
    dfs(bintree[ri].rch, sum);
}

void sol()
{
    input_data();
    if (is_end == false)
    {
        build_tree(0, N - 1, 0, N - 1);
        dfs(postorder[N - 1], 0);
        cout << ans_nodei << "\n";
    }
}
int32_t main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (is_end == false)
    {
        sol();
    }
    return 0;
}