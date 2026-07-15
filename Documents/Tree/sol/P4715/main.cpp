#include <bits/stdc++.h>
using namespace std;
#define max_len (1LL << 8)
int pow_val[max_len];

int user_list[max_len];
int n, peo_len;

void input_data()
{
    cin >> n;
    peo_len = (1LL << n);
    for (int i = 0; i < peo_len; i++)
    {
        cin >> pow_val[i];
        user_list[i] = i;
    }
}

void sol()
{
    input_data();
    for (int i = 0; i < n - 1; i++)
    {
        int len = (1LL << (n - i - 1));
        for (int j = 0; j < len; j++)
        {
            if (pow_val[user_list[j * 2]] >
                pow_val[user_list[j * 2 + 1]])
            {
                user_list[j] = user_list[j * 2];
            }
            else
            {
                user_list[j] = user_list[j * 2 + 1];
            }
            // cout << user_list[j] << " ";
        }
        // cout << endl;
    }
    if (pow_val[user_list[0]] > pow_val[user_list[1]])
        cout << user_list[1] + 1 << "\n";
    else
        cout << user_list[0] + 1 << "\n";
}

int main()
{
    sol();
}