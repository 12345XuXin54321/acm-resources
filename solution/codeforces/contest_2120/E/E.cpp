#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define max_len 200010
int N, k;
int arr[max_len];

int sum_arr[max_len];
int pre_sum[max_len];

int sum_1_N(int val)
{
    return val * (val + 1) / 2;
}

int get_interval_sum(int l, int r)
{
    int lv = (l == 0 ? 0 : pre_sum[l - 1]);
    int rv = pre_sum[r];
    return rv - lv;
}

int get_sum_with_remainder(int cnt, int base_len, int remainder)
{
    int ave_add = remainder / cnt;
    int add1cnt = remainder % cnt;
    int ans = add1cnt * sum_1_N(base_len + ave_add + 1);
    ans += (cnt - add1cnt) * sum_1_N(base_len + ave_add);
    return ans;
}

int mv_max_cnt(int cnt)
{
    int will_mv = 0;
    int base_len = arr[0];
    int mv_cnt = 0;
    int remainder = 0;
    for (int i = 1; i < N; i++)
    {
        int add = i * (arr[i - 1] - arr[i]);
        base_len = arr[i];
        mv_cnt = i;
        if (will_mv <= cnt && will_mv + add >= cnt)
        {
            remainder = will_mv + add - cnt;
            break;
        }
        else
        {
            will_mv += add;
        }
    }
    int ans = 0;
    ans += get_sum_with_remainder(mv_cnt, base_len, remainder);

    int void_cnt = 0;
    base_len = arr[N - 1];
    int mv_beg_r = N - 1;
    for (int i = N - 1; i >= mv_cnt; i--)
    {
        int add = (N - i) * (arr[i - 1] - arr[i]);
        mv_beg_r = i;
        base_len = arr[i];
        remainder = cnt - void_cnt;
        if (void_cnt <= cnt && void_cnt + add >= cnt)
        {
            break;
        }
        else
        {
            void_cnt += add;
        }
    }
    ans += get_sum_with_remainder(N - mv_beg_r, base_len, remainder);
    if (mv_cnt < mv_beg_r)
        ans += get_interval_sum(mv_cnt, mv_beg_r - 1);
    ans += k * cnt;
    return ans;
}

int get_ans()
{
    if (N == 1)
    {
        return sum_1_N(arr[0]);
    }
    int l = 0, r = 0;
    for (int i = 0; i < N - 1; i++)
    {
        r += arr[i] - arr[N - 1];
    }

    while (l + 3 < r)
    {
        int mid = (l + r) / 2;
        int lmid = (l + mid) / 2;
        int rmid = (r + mid) / 2;
        int vl = mv_max_cnt(lmid);
        int vm = mv_max_cnt(mid);
        int vr = mv_max_cnt(rmid);
        int min_v = min({vl, vm, vr});
        if (vl == min_v)
        {
            r = mid;
        }
        else if (vm == min_v)
        {
            l = lmid, r = rmid;
        }
        else
        {
            l = mid;
        }
    }
    int ans = mv_max_cnt(l);
    for (int i = l + 1; i <= r; i++)
    {
        ans = min(ans, mv_max_cnt(i));
    }

    return ans;
}

void sol()
{
    cin >> N >> k;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    // big ... smail
    sort(arr, arr + N, greater());

    for (int i = 0; i < N; i++)
    {
        sum_arr[i] = sum_1_N(arr[i]);
        pre_sum[i] = (i == 0 ? 0 : pre_sum[i - 1]);
        pre_sum[i] += sum_arr[i];
    }

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