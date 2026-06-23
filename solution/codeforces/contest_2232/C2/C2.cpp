#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int n, x, s;
string str;

int get_cnt(int A_as_I)
{
    int ans = 0;
    int tab_void = x;
    int seat_cnt = 0;
    for (auto ch : str)
    {
        if (ch == 'I')
        {
            if (tab_void > 0)
            {
                tab_void--;
                ans++;
                seat_cnt += (s - 1);
            }
        }
        else if (ch == 'E')
        {
            if (seat_cnt > 0)
            {
                seat_cnt--;
                ans++;
            }
        }
        else if (ch == 'A')
        {
            if (A_as_I > 0)
            {
                A_as_I--;
                if (tab_void > 0)
                {
                    tab_void--;
                    ans++;
                    seat_cnt += (s - 1);
                }
            }
            else
            {
                if (seat_cnt > 0)
                {
                    seat_cnt--;
                    ans++;
                }
            }
        }
    }
    return ans;
}

int get_ans()
{
    int acnt = 0;
    for (auto ch : str)
        acnt += (ch == 'A');

    int l = 0, r = acnt - 1;
    while (l + 1 < r)
    {
        int mid = (l + r) / 2;

        int v1 = get_cnt(mid);
        int v2 = get_cnt(mid + 1);

        if (v1 >= v2)
        {
            r = mid;
        }
        else
        {
            l = mid;
        }
    }

    int ans1 = get_cnt(l);
    int ans2 = get_cnt(l + 1);
    int ans3 = get_cnt(r);
    int ans4 = get_cnt(r + 1);
    return max({ans1, ans2, ans3, ans4});
}

void sol()
{
    cin >> n >> x >> s;
    cin >> str;

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
