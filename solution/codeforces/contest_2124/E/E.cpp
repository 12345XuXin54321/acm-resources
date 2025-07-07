#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define max_len 50010
int arr[max_len];
int pre_arr[max_len];

int get_range_sum(int l, int r)
{
    int lv = 0, rv = pre_arr[r];
    if (l != 0)
        lv = pre_arr[l - 1];
    return rv - lv;
}

struct ans_info
{
    int l, r;
};

vector<ans_info> ans_vec;
int range_l, range_lend, range_r;
int left_alloc, right_alloc;
int N;

bool get_ans(int l, int r, int need_sub)
{
    if (l == r)
    {
        return false;
    }
    int first_range_end = l;
    int min_diff = max_len * 1e12;
    int range1 = 0, range2 = 0;
    for (int i = l; i <= r; i++)
    {
        range1 = get_range_sum(l, i);
        range2 = get_range_sum(i + 1, r);
        if (abs(range1 - range2) < min_diff)
        {
            first_range_end = i;
            min_diff = abs(range1 - range2);
        }
    }
    range1 = get_range_sum(l, first_range_end);
    range2 = get_range_sum(first_range_end + 1, r);
    if (min_diff <= need_sub)
    {
        if ((need_sub - min_diff) % 2 == 1)
            return false;
        else // ok
        {
            range_l = l, range_lend = first_range_end, range_r = r;
            left_alloc = right_alloc = (need_sub - min_diff) / 2;
            if (range1 > range2)
            {
                left_alloc += min_diff;
            }
            else
            {
                right_alloc += min_diff;
            }
            return true;
        }
    }
    else
    {
        int ret = false;
        if (range1 > range2)
        {
            ans_vec.push_back({first_range_end + 1, r});
            ret = get_ans(l, first_range_end, range2 + need_sub);
        }
        else
        {
            ans_vec.push_back({l, first_range_end});
            ret = get_ans(first_range_end + 1, r, range1 + need_sub);
        }
        return ret;
    }
}

void ans_add(vector<int> &vec, int cnt)
{
    for (int i = range_l; i <= range_lend; i++)
    {
        int subcnt = min({left_alloc, arr[i], cnt});
        vec[i] = subcnt;
        left_alloc -= subcnt;
        arr[i] -= subcnt;
        cnt -= subcnt;
        if (left_alloc == 0 || cnt == 0)
            break;
    }
    for (int i = range_lend + 1; i <= range_r; i++)
    {
        int subcnt = min({right_alloc, arr[i], cnt});
        vec[i] = subcnt;
        right_alloc -= subcnt;
        arr[i] -= subcnt;
        cnt -= subcnt;
        if (right_alloc == 0 || cnt == 0)
            break;
    }
}

void print_vec(vector<int> &vec)
{
    for (int i = 0; i < N; i++)
    {
        cout << vec[i] << " \n"[i == N - 1];
    }
}

void print_ans()
{
    int pn = ans_vec.size() + 1;
    cout << pn << "\n";
    for (auto [l, r] : ans_vec)
    {
        vector<int> vec(N, 0);
        ans_add(vec, get_range_sum(l, r));
        for (int i = l; i <= r; i++)
        {
            vec[i] = arr[i];
        }
        print_vec(vec);
    }
    vector<int> vec(N, 0);
    for (int i = range_l; i <= range_r; i++)
    {
        vec[i] = arr[i];
    }
    print_vec(vec);
}

void sol()
{
    ans_vec.clear();
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
        pre_arr[i] = arr[i];
        if (i != 0)
            pre_arr[i] += pre_arr[i - 1];
    }
    if (get_ans(0, N - 1, 0))
    {
        print_ans();
    }
    else
    {
        cout << "-1\n";
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