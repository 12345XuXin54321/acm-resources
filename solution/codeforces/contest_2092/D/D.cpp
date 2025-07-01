#include <bits/stdc++.h>
using namespace std;
#define int int64_t

// T:0, I:1, L:2
int ch2ind(char c)
{
    if (c == 'T')
        return 0;
    else if (c == 'I')
        return 1;
    else
        return 2;
}
char ind2ch(int ind)
{
    return "TIL"[ind];
}

int get_other(int i1, int i2)
{
    for (int i = 0; i < 2; i++)
    {
        if (i != i1 && i != i2)
        {
            return i;
        }
    }
    return 2;
}

int chcntarr[5];
int N;
string str;

vector<int> ans_vec;

void preduce()
{
    for (int i = 0; i < 3; i++)
    {
        if (chcntarr[i] == 0)
        {
            string tmpstr;
            for (int pi = 0; pi < str.size(); pi++)
            {
                tmpstr.push_back(str[pi]);
                if (pi + 1 < str.size() &&
                    str[pi] != str[pi + 1] &&
                    (ch2ind(str[pi]) == i || ch2ind(str[pi + 1]) == i))
                {
                    int ot = get_other(ch2ind(str[pi]), ch2ind(str[pi + 1]));
                    ans_vec.push_back(pi);
                    chcntarr[ot]++;
                    tmpstr.push_back(ind2ch(ot));
                    for (int j = pi + 1; j < str.size(); j++)
                    {
                        tmpstr.push_back(str[j]);
                    }
                    str = tmpstr;
                    return;
                }
            }
        }
    }
}

bool check()
{
    preduce();

    for (int i = 0; i < 3; i++)
    {
        if (chcntarr[i] == 0)
        {
            for (int pi = 0; pi < str.size() - 1; pi++)
            {
                if (str[pi] == str[pi + 1])
                    continue;
                if (ch2ind(str[pi]) == i || ch2ind(str[pi + 1]) == i)
                    continue;

                int bef_cnt = chcntarr[ch2ind(str[pi])];
                int aft_cnt = chcntarr[ch2ind(str[pi + 1])];

                ans_vec.push_back(pi);
                for (int j = 1; j <= 2 * aft_cnt; j++)
                {
                    ans_vec.push_back(pi + j);
                }
                for (int j = 0; j < 2 * bef_cnt; j++)
                {
                    ans_vec.push_back(pi);
                }
                ans_vec.pop_back();
                return true;
            }
        }
    }
    return false;
}

void sol()
{
    for (int i = 0; i < 3; i++)
    {
        chcntarr[i] = 0;
    }
    ans_vec.clear();

    cin >> N >> str;

    for (auto c : str)
    {
        chcntarr[ch2ind(c)]++;
    }

    int min_cnt = min({chcntarr[0], chcntarr[1], chcntarr[2]});
    int max_cnt = max({chcntarr[0], chcntarr[1], chcntarr[2]});
    if (min_cnt == max_cnt)
    {
        cout << "0\n";
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            chcntarr[i] -= min_cnt;
        }

        if (check())
        {
            cout << ans_vec.size() << "\n";
            for (auto val : ans_vec)
            {
                cout << val + 1 << "\n";
            }
        }
        else
        {
            cout << "-1\n";
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