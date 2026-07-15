#include <bits/stdc++.h>
using namespace std;
#define max_len 30
int arr[max_len];
void sol()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    int ln = 0, rn = 0;
    for (int i = 0; i < N; i++)
    {
        if (arr[i] != 0)
        {
            ln++;
        }
        else
        {
            break;
        }
    }
    for (int i = N - 1; i >= 0; i--)
    {
        if (arr[i] != 0)
        {
            rn++;
        }
        else
        {
            break;
        }
    }
    if (ln % 2 != 0 || rn % 2 != 0)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

int main()
{
    sol();
}