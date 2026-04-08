#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define max_len 200010

int arr[max_len];
int diff_arr[max_len];
int special_idx[max_len];
int n, k;

int get_ans()
{
    int last_idx = 0;
    vector<int> vec;
    int sum = 0;
    for (int i = 0; i <= k; i++)
    {
        int cnt = 0;
        for (int j = last_idx; j <= special_idx[i]; j++)
        {
            cnt += (diff_arr[j] == 1);
        }
        vec.push_back(cnt);
        last_idx = special_idx[i] + 1;
        sum += cnt;
    }
    sort(vec.begin(), vec.end(), greater());
    if (vec[0] * 2 > sum)
    {
        return vec[0];
    }
    else
    {
        return sum / 2;
    }
}

void sol()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < k; i++)
    {
        cin >> special_idx[i];
        special_idx[i]--;
    }

    special_idx[k] = n;
    diff_arr[0] = (arr[0] ^ arr[special_idx[0]]);
    for (int i = 1; i < n; i++)
    {
        diff_arr[i] = (arr[i - 1] ^ arr[i]);
    }
    diff_arr[n] = (arr[n - 1] ^ arr[special_idx[0]]);

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