#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define max_len 200010
#define INF (0x3f3f3f3f)

int N;
struct arr_t
{
    int arr[max_len];
    int min_val_0toi[max_len];
    int max_val_itoN[max_len];
    void input()
    {
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }
        min_val_0toi[0] = arr[0];
        for (int i = 1; i < N; i++)
        {
            min_val_0toi[i] = min(min_val_0toi[i - 1], arr[i]);
        }
        max_val_itoN[N - 1] = arr[N - 1];
        for (int i = N - 2; i >= 0; i--)
        {
            max_val_itoN[i] = max(max_val_itoN[i + 1], arr[i]);
        }
    }
};

arr_t arr_player;
arr_t arr_dealer;

bool check(int front_cnt)
{
    int end_cnt = N - front_cnt;
    int ti_val = -1;
    if (end_cnt != 0)
    {
        ti_val = arr_player.max_val_itoN[front_cnt];
    }
    int will_ti = -1;
    if (front_cnt != 0)
    {
        will_ti = arr_player.min_val_0toi[front_cnt - 1];
    }

    int pmy = 0, pdealer = 0;
    while (pmy <= min(front_cnt, N - 1) && pdealer <= min(end_cnt, N - 1))
    {
        if (arr_player.arr[pmy] > arr_dealer.arr[pdealer])
        {
            pmy++;
        }
        else if (arr_player.arr[pmy] == will_ti && ti_val > arr_dealer.arr[pdealer])
        {
            pmy++;
        }
        else
        {
            pdealer++;
        }
    }
    if (pmy >= front_cnt)
        return true;
    else
        return false;
}

int get_ans()
{
    int l = 0, r = N;
    while (l + 1 < r)
    {
        int mid = (l + r) / 2;
        if (check(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    if (check(r))
    {
        return r;
    }
    else
    {
        return l;
    }
}

void sol()
{
    cin >> N;
    arr_player.input();
    arr_dealer.input();

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