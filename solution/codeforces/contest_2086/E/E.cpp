#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define dig_len 45
#define max_sum (dig_len * 3 + 5)
// dig ind, sum, is leq, not zero end is 4
int dp_arr[dig_len][max_sum][2][2];

vector<int> trans_num(int x)
{
    // 0b0101 = 0x5
    int dign = 0x5555'5555'5555'5555LL;
    vector<int> digcnt;
    while (dign > 0)
    {
        digcnt.push_back(x / dign);
        x %= dign;
        dign /= 4;
    }
    reverse(digcnt.begin(), digcnt.end());
    return digcnt;
}

void init_dp()
{
    for (int i = 0; i < dig_len; i++)
    {
        for (int j = 0; j < max_sum; j++)
        {
            dp_arr[i][j][0][0] = 0;
            dp_arr[i][j][0][1] = 0;
            dp_arr[i][j][1][0] = 0;
            dp_arr[i][j][1][1] = 0;
        }
    }
}

int get_cnt(int x, int need_sum)
{
    auto digc = trans_num(x);

    for (int ind = 0; ind < digc.size(); ind++)
    {
        for (int s = 0; s < max_sum; s++)
        {
            dp_arr[ind][s][0][0] = 0;
            dp_arr[ind][s][0][1] = (s == 4);
            dp_arr[ind][s][1][0] = 0;
            dp_arr[ind][s][1][1] = (s == 4 && digc[ind] == 4);

            if (ind > 0)
            {
                for (int dig = 0; dig <= min(s, int(3)); dig++)
                {
                    dp_arr[ind][s][0][0] += dp_arr[ind - 1][s - dig][0][0];

                    if (dig < digc[ind])
                    {
                        dp_arr[ind][s][1][0] += dp_arr[ind - 1][s - dig][0][0];

                        dp_arr[ind][s][1][1] += dp_arr[ind - 1][s - dig][0][1];
                    }
                    else if (dig == digc[ind])
                    {
                        dp_arr[ind][s][1][0] += dp_arr[ind - 1][s - dig][1][0];

                        dp_arr[ind][s][1][1] += dp_arr[ind - 1][s - dig][1][1];
                    }

                    dp_arr[ind][s][0][1] += dp_arr[ind - 1][s - dig][0][1];
                }
            }
            else if (s <= 3)
            {
                dp_arr[ind][s][0][0] += 1;

                if (s <= digc[ind])
                    dp_arr[ind][s][1][0] += 1;
            }
        }
    }
    int sum = 0;
    for (int dig = 0; dig < min(digc.back(), int(3)); dig++)
    {
        sum += dp_arr[digc.size() - 1][need_sum][0][0];
        sum += dp_arr[digc.size() - 1][need_sum][0][1];
    }
    sum += dp_arr[digc.size() - 1][need_sum][1][0];
    sum += dp_arr[digc.size() - 1][need_sum][1][1];
    return sum;
}
void sol()
{
    int l, r, k;
    cin >> l >> r >> k;
    k = min(int(max_sum - 1), k);
    int lc = get_cnt(l - 1, k);
    int rc = get_cnt(r, k);
    cout << rc - lc << "\n";
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
