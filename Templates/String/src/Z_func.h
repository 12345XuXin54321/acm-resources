#include <bits/stdc++.h>

using namespace std;

vector<int> z_func(const string &str)
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
            z[i] = max(r - i + 1, 0);
            while (i + z[i] < len && str[z[i]] == str[i + z[i]])
            {
                z[i]++;
            }
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}