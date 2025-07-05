#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define max_len 200010
int N;

int neg_one_ind;
int arr_a[max_len];
int arr_ans[max_len];

int p_beg, p_end;

void fill_left(int it)
{
    for (int i = 0; i < neg_one_ind; i++)
    {
        if (arr_a[i] == it)
        {
            if (it % 2 == 1)
            {
                arr_ans[i] = p_end;
                p_end--;
            }
            else
            {
                arr_ans[i] = p_beg;
                p_beg++;
            }
        }
    }
}
void fill_right(int it)
{
    for (int i = N - 1; i > neg_one_ind; i--)
    {
        if (arr_a[i] == it)
        {
            if (it % 2 == 1)
            {
                arr_ans[i] = p_end;
                p_end--;
            }
            else
            {
                arr_ans[i] = p_beg;
                p_beg++;
            }
        }
    }
}

void sol()
{
    cin >> N;
    p_beg = 1, p_end = N;
    int max_num = 1;
    for (int i = 0; i < N; i++)
    {
        cin >> arr_a[i];
        max_num = max(max_num, arr_a[i]);
        if (arr_a[i] == -1)
        {
            neg_one_ind = i;
        }
    }
    for (int i = 1; i <= max_num; i++)
    {
        fill_left(i), fill_right(i);
    }
    arr_ans[neg_one_ind] = p_beg;
    for (int i = 0; i < N; i++)
    {
        cout << arr_ans[i] << " \n"[i == N - 1];
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