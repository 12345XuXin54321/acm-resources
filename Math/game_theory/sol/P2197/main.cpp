#include <bits/stdc++.h>
using namespace std;
void sol()
{
    int n;
    cin >> n;
    int xor_sum = 0;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        xor_sum ^= tmp;
    }
    if (xor_sum == 0)
    {
        cout << "No\n";
    }
    else
    {
        cout << "Yes\n";
    }
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        sol();
    }
    
}