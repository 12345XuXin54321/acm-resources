#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int N;
string str;

bool check_str(string split_str)
{
    int cnt_continue_0 = 0;
    int cnt_free_0 = 0;
    int cnt_need_march_0 = 0;
    for (auto ch : split_str)
    {
        if (ch == '0')
        {
            cnt_continue_0++;
            if (cnt_continue_0 == 1)
            {
                cnt_need_march_0++;
            }
            else if (cnt_continue_0 > 1)
            {
                cnt_free_0++;
                cnt_need_march_0 = 0;
            }
        }
        else
        {
            cnt_continue_0 = 0;
        }
    }
    if (cnt_free_0 == 0)
    {
        return cnt_need_march_0 % 2 == 0;
    }
    else
    {
        return true;
    }
}

bool get_ans()
{
    string tmp_str;
    for (auto ch : str)
    {
        if (ch == '1')
        {
            if (tmp_str.size() != 0)
            {
                if (tmp_str.back() == '1')
                {
                    tmp_str.pop_back();
                    auto ret = check_str(tmp_str);
                    if (ret == false)
                        return false;
                    tmp_str = "";
                }
                else
                {
                    tmp_str.push_back(ch);
                }
            }
        }
        else
        {
            tmp_str.push_back(ch);
        }
    }
    if (tmp_str.size() != 0)
    {
        if (tmp_str.back() == '1')
            tmp_str.pop_back();

        return check_str(tmp_str);
    }
    else
    {
        return true;
    }
}

void sol()
{
    cin >> N >> str;
    if (str[0] == '0')
        str = "00" + str;
    if (str.back() == '0')
        str = str + "00";

    auto ret = get_ans();
    if (ret)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
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
