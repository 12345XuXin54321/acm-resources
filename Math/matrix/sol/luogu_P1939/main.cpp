#include <bits/stdc++.h>
using namespace std;
#define mx_size 3
#define mod_n (1000000007)
#define mod(x) ((x) % mod_n)
#define mxqpow_size 33

struct MX
{
    int64_t arr[mx_size][mx_size];
    void init()
    {
        for (int i = 0; i < mx_size; i++)
        {
            for (int j = 0; j < mx_size; j++)
            {
                arr[i][j] = 0;
            }
        }
    }
    MX operator*(const MX &r) const
    {
        MX ans;
        ans.init();
        for (int i = 0; i < mx_size; i++)
        {
            for (int k = 0; k < mx_size; k++)
            {
                for (int j = 0; j < mx_size; j++)
                {
                    ans.arr[i][j] += mod(arr[i][k] * r.arr[k][j]);
                    ans.arr[i][j] = mod(ans.arr[i][j]);
                }
            }
        }
        return ans;
    }
};

struct VEC
{
    int64_t arr[mx_size];
    void init()
    {
        for (int i = 0; i < mx_size; i++)
        {
            arr[i] = 0;
        }
    }
    VEC operator*(const MX &r) const
    {
        VEC ans;
        ans.init();
        for (int i = 0; i < mx_size; i++)
        {
            for (int k = 0; k < mx_size; k++)
            {
                ans.arr[i] += mod(r.arr[i][k] * arr[k]);
                ans.arr[i] = mod(ans.arr[i]);
            }
        }
        return ans;
    }
};

MX mx_qpow_arr[mxqpow_size];

void init_qpow()
{
#define set_mx(x, y, val) mx_qpow_arr[0].arr[x][y] = val
    set_mx(0, 0, 0), set_mx(0, 1, 0), set_mx(0, 2, 1);
    set_mx(1, 0, 1), set_mx(1, 1, 0), set_mx(1, 2, 0);
    set_mx(2, 0, 0), set_mx(2, 1, 1), set_mx(2, 2, 1);

    for (int i = 1; i < mxqpow_size; i++)
    {
        mx_qpow_arr[i] = mx_qpow_arr[i - 1] * mx_qpow_arr[i - 1];
    }
}

VEC get_ans(VEC b, int64_t x)
{
    for (int i = 0; i < mxqpow_size; i++)
    {
        if (x & (1LL << i))
        {
            b = b * mx_qpow_arr[i];
        }
    }
    return b;
}

void sol()
{
    int N;
    cin >> N;
    VEC vecb;
    vecb.arr[0] = vecb.arr[1] = vecb.arr[2] = 1;
    for (int i = 0; i < N; i++)
    {
        int64_t x;
        cin >> x;
        if (x <= 3)
        {
            cout << "1\n";
        }
        else
        {
            auto ansvec = get_ans(vecb, x - 3);
            cout << ansvec.arr[2] << "\n";
        }
    }
}

int main()
{
    init_qpow();
    sol();
}