#include <bits/stdc++.h>
using namespace std;
#define max_len 1000010
struct tree_node
{
    int lch, rch;
} tree_arr[max_len];

int N;

int get_depth(int root_i)
{
    if (root_i == 0)
    {
        return 0;
    }
    else
    {
        return 1 + max(get_depth(tree_arr[root_i].lch),
                       get_depth(tree_arr[root_i].rch));
    }
}

void input_data()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> tree_arr[i].lch >> tree_arr[i].rch;
    }
}

void sol()
{
    input_data();
    cout << get_depth(1) << "\n";
}

int main()
{
    sol();
}