#include <bits/stdc++.h>
using namespace std;
#define max_len 1024
#define qpow_len 32

struct MX
{
    bitset<max_len> arr[max_len];
    int n, m;

    void init(int nn, int mm)
    {
        n = nn, m = mm;
        for (int i = 0; i < n; i++)
        {
            arr[i].reset();
        }
    }

    MX T() const
    {
        MX ans;
        ans.init(m, n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                ans.arr[j][i] = arr[i][j];
            }
        }
        return ans;
    }

    MX operator*(const MX &r) const
    {
        MX ans;
        ans.init(n, r.m);
        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k < m; k++)
            {
                if (arr[i][k])
                    ans.arr[i] ^= r.arr[k];
            }
        }
        return ans;
    }
};

struct VEC
{
    bitset<max_len> arr;
    int m;
    void init(int mm)
    {
        m = mm;
        arr.reset();
    }

    VEC operator*(const MX rT) const
    {
        VEC ans;
        ans.init(m);
        for (int i = 0; i < m; i++)
        {
            ans.arr[i] = ((arr & rT.arr[i]).count() % 2 == 1);
        }
        return ans;
    }
    void print()
    {
        for (int i = 0; i < m; i++)
        {
            if (arr[i])
            {
                cout << '1';
            }
            else
            {
                cout << '0';
            }
        }
        cout << "\n";
    }
};

MX qpow_arr[qpow_len];
void init_qpow(MX &mxa)
{
    qpow_arr[0] = mxa;
    for (int i = 1; i < qpow_len; i++)
    {
        qpow_arr[i] = qpow_arr[i - 1] * qpow_arr[i - 1];
    }
    for (int i = 0; i < qpow_len; i++)
    {
        qpow_arr[i] = qpow_arr[i].T();
    }
}

VEC get_ans(VEC &vecb_T, int x)
{
    VEC ans = vecb_T;
    for (int i = 0; i < qpow_len; i++)
    {
        if (x & (1LL << i))
        {
            ans = ans * qpow_arr[i];
        }
    }
    return ans;
}

void sol()
{
    int n;
    cin >> n;
    MX mxa;
    mxa.init(n, n);
    VEC vecb_T;
    vecb_T.init(n);
    string str;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        for (int j = 0; j < n; j++)
        {
            if (str[j] == '1')
            {
                mxa.arr[i][j] = true;
            }
        }
    }
    cin >> str;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '1')
        {
            vecb_T.arr[i] = true;
        }
    }

    MX mxa_T = mxa.T();
    init_qpow(mxa_T);

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int x;
        cin >> x;
        VEC ans = get_ans(vecb_T, x);
        ans.print();
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    sol();
}