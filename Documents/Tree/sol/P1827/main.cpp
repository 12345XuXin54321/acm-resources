#include <bits/stdc++.h>
using namespace std;

#define max_len 100

struct tree_node
{
    int l, r;
    char c;
} bit_tree[max_len];

string preorder, inorder;

void input_data()
{
    cin >> inorder >> preorder;
    for (int i = 1; i <= 26; i++)
    {
        bit_tree[i].c = 'A' + i - 1;
    }
}

int char_to_ind(char c)
{
    return c - 'A' + 1;
}

void build_tree(int pre_l, int pre_r, int in_l, int in_r)
{
    if (pre_r - pre_l == 0)
    {
        return;
    }
    else
    {
        char rootch = preorder[pre_l];
        if (inorder[in_l] != rootch)
        {
            int lch_in_r = in_l;

            while (inorder[lch_in_r + 1] != rootch)
            {
                lch_in_r++;
            }

            char lch = preorder[pre_l + 1];

            bit_tree[char_to_ind(rootch)].l = char_to_ind(lch);

            int ltree_len = (lch_in_r - in_l + 1);

            build_tree(pre_l + 1, pre_l + ltree_len, in_l, in_l + ltree_len - 1);

            if (pre_r - pre_l > ltree_len)
            {
                int rch_pre_l = pre_l + 1 + ltree_len;
                char rch = preorder[rch_pre_l];
                bit_tree[char_to_ind(rootch)].r = char_to_ind(rch);

                build_tree(rch_pre_l, pre_r, in_l + ltree_len + 1, in_r);
            }
        }
        else
        {
            int rch = preorder[pre_l + 1];
            bit_tree[char_to_ind(rootch)].r = char_to_ind(rch);
            build_tree(pre_l + 1, pre_r, in_l + 1, in_r);
        }
    }
}

void dfs(int i)
{
    if (i != 0)
    {
        dfs(bit_tree[i].l);
        dfs(bit_tree[i].r);
        cout << bit_tree[i].c;
    }
}

void sol()
{
    input_data();
    build_tree(0, preorder.size() - 1, 0, inorder.size() - 1);
    dfs(char_to_ind(preorder[0]));
    cout << "\n";
}

int main()
{
    sol();
}