#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define max_len 200010

#define FROM_LEFT 0
#define FROM_RIGHT 1

int n, k;

#define mod(x) ((k + ((x) % k)) % k)
#define bian_len (int(1e15) + 5)

int pos_arr[max_len];
int delay_arr[max_len];

struct tree_node
{
    int pnxt[2];
} node_arr[max_len];

// from left, right
bool is_can_leave[max_len][2];
map<int, vector<int>> pdetay_from_left;
map<int, vector<int>> pdetay_from_right;

void init_data(int N)
{
    for (int i = 0; i < N + 10; i++)
    {
        node_arr[i] = {-1, -1};
        is_can_leave[i][0] = is_can_leave[i][1] = false;
    }
}

void init_pnxt()
{
    pdetay_from_left.clear();
    pdetay_from_right.clear();
    // detay, lastind
    for (int i = 0; i < n; i++)
    {
        // time 0, l*k+de
        int de = mod(pos_arr[i] - delay_arr[i]);
        if (pdetay_from_left.count(de) != 0)
        {
            int last_ind = pdetay_from_left[de].back();
            node_arr[last_ind].pnxt[FROM_RIGHT] = i;
        }
        pdetay_from_left[de].push_back(i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        // time 0, l*k+de
        int de = k - mod(pos_arr[i] + delay_arr[i]);
        if (pdetay_from_right.count(de) != 0)
        {
            int last_ind = pdetay_from_right[de].back();
            node_arr[last_ind].pnxt[FROM_LEFT] = i;
        }
        pdetay_from_right[de].push_back(i);
    }
}

// from left, right
bool is_vis[max_len][2];
bool is_in_dfs[max_len][2];
void init_vis(int N)
{
    for (int i = 0; i < N + 10; i++)
    {
        is_vis[i][0] = is_vis[i][1] = false;
        is_in_dfs[i][0] = is_in_dfs[i][1] = false;
    }
}
// face 0:l, 1:r
bool dfs_can_leave(int ind, bool face)
{
    int ans = false;
    if (is_in_dfs[ind][face] == true)
    {
        ans = false;
    }
    else
    {
        is_in_dfs[ind][face] = true;
        if (is_vis[ind][face] == true)
        {
            ans = is_can_leave[ind][face];
        }
        else
        {
            is_vis[ind][face] = true;
            if (node_arr[ind].pnxt[face] == -1)
            {
                ans = true;
            }
            else
            {
                ans = dfs_can_leave(node_arr[ind].pnxt[face], !face);
            }
        }
        is_in_dfs[ind][face] = false;
    }
    is_can_leave[ind][face] = ans;
    return ans;
}

int find_aft_same_ind(int pos, vector<int> &vec)
{
    if (vec.size() == 0 || pos > pos_arr[vec.back()])
    {
        return vec.size();
    }
    else
    {
        int l = 0, r = vec.size() - 1;
        while (l + 1 < r)
        {
            int mid = (l + r) / 2;
            if (pos_arr[vec[mid]] >= pos)
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }
        if (pos_arr[vec[l]] >= pos)
        {
            return l;
        }
        else
        {
            return r;
        }
    }
}

void sol()
{
    cin >> n >> k;
    init_data(n);
    for (int i = 0; i < n; i++)
    {
        cin >> pos_arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> delay_arr[i];
    }
    init_pnxt();
    init_vis(n);
    for (int i = 0; i < n; i++)
    {
        for (int f = 0; f <= 1; f++)
        {
            if (is_vis[i][f] == false)
            {
                dfs_can_leave(i, f);
            }
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int ai;
        cin >> ai;
        int de = ai % k;
        int aft = find_aft_same_ind(ai, pdetay_from_left[de]);

        if (aft >= pdetay_from_left[de].size())
        {
            cout << "YES\n";
        }
        else
        {
            if (is_can_leave[pdetay_from_left[de][aft]][0])
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
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