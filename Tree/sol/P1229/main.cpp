#include <bits/stdc++.h>
using namespace std;
string preorder, postorder;
int64_t get_ans(int pre_l, int pre_r, int post_l, int post_r)
{
    if (pre_r - pre_l + 1 == 1)
    {
        return 1;
    }
    if (pre_r - pre_l != post_r - post_l)
    {
        return 0;
    }

    char rootch = preorder[pre_l];
    if (rootch != postorder[post_r])
    {
        return 0;
    }

    int64_t sum = 0;

    {
        char lch = preorder[pre_l + 1];
        int lch_post_r = post_l;
        while (postorder[lch_post_r] != lch && lch_post_r < post_r - 1)
        {
            lch_post_r++;
        }
        if (postorder[lch_post_r] == lch)
        {
            // | root | l |
            // | l | root |
            if (lch_post_r == post_r - 1)
            {
                sum += get_ans(pre_l + 1, pre_r, post_l, post_r - 1);
            }
            // | root | l | r |
            // | l | r | root |
            else
            {
                char rch = postorder[post_r - 1];
                int rch_pre_l = pre_l + 1;
                while (preorder[rch_pre_l] != rch && rch_pre_l < pre_r)
                {
                    rch_pre_l++;
                }
                if (preorder[rch_pre_l] == rch)
                    sum += get_ans(pre_l + 1, rch_pre_l - 1, post_l, lch_post_r) *
                           get_ans(rch_pre_l, pre_r, lch_post_r + 1, post_r - 1);
            }
        }
    }

    // | root | r |
    // | r | root |
    if (preorder[pre_l + 1] == postorder[post_r - 1])
    {
        sum += get_ans(pre_l + 1, pre_r, post_l, post_r - 1);
    }

    return sum;
}
void sol()
{
    cin >> preorder >> postorder;
    cout << get_ans(0, preorder.size() - 1, 0, postorder.size() - 1) << "\n";
}
int main()
{
    sol();
}