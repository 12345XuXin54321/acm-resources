#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int N;

int qry(int n1, int n2)
{
    cout << "? " << n1 << " " << n2 << endl;
    int ret;
    cin >> ret;
    if (ret == -1)
        exit(-1);
    return ret;
}

void print_ans(int k)
{
    cout << "! " << k << endl;
}

int get_ans()
{
    for (int i = 2; i < N; i++)
    {
        int ret = qry(i * 2 + 1, i * 2 + 2);
        if (ret == 1)
        {
            return i * 2 + 1;
        }
    }

    if (qry(1, 2))
        return 1;
    if (qry(1, 3))
        return 1;
    if (qry(2, 3))
        return 2;
    return 4;
}

void sol()
{
    cin >> N;
    int ans = get_ans();
    print_ans(ans);
}

int32_t main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
    {
        sol();
    }
}