#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<int> z_func(const string_view &str)
{
    int len = str.size();
    vector<int> z(len, 0);
    z[0] = 0;
    int l = 0, r = 0;
    for (int i = 1; i < len; i++)
    {
        if (z[i - l] < r - i + 1)
        {
            z[i] = z[i - l];
        }
        else
        {
            z[i] = max<int>(r - i + 1, 0);
            while (i + z[i] < len && str[z[i]] == str[i + z[i]])
            {
                z[i]++;
            }
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

int n, q;
string str;
vector<int> z;

// ind, z[i]
vector<pair<int, int>> stk;

int get_ans(int l, int r)
{
    stk.clear();

    int len = r - l + 1;
    z = z_func(string_view(str).substr(l, len));
    z[0] = len;
    stk.push_back({0, len});
    int ans = 1;
    for (int i = 1; i < len; i++)
    {
        while (true)
        {
            auto [ind, z_i] = stk.back();
            if (ind + z_i - 1 >= i ||
                (ind + z_i == i && z[i] != 0))
                break;
            else
                stk.pop_back();
        }
        if (z[i] != 0)
            stk.push_back({i, z[i]});
        ans += stk.size();
    }
    return ans;
}

void sol()
{
    cin >> n >> q;
    cin >> str;
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        int ans = get_ans(l - 1, r - 1);
        cout << ans << "\n";
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