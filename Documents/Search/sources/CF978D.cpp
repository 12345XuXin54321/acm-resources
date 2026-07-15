#include <bits/stdc++.h>
using namespace std;
#define max_len 100100
// 原始的数
int arr[max_len];
// 最小改变次数
int min_change = -1;
int N;
// 参数分别为
// ni:当前的下标
// l1:上一个数
// l2:上两个数
// change_num:改变的次数
void dfs(int ni, int l1, int l2, int change_num)
{
    // 当前的改变次数已经比之前的更多了，返回
    if (min_change != -1 && change_num >= min_change)
        return;

    // 到达了第N个，更新最小改变次数
    if (ni >= N)
    {
        if (min_change == -1)
            min_change = change_num;
        else
            min_change = min(min_change, change_num);
    }
    else
    {
        // 第三个数之后
        if (l1 != -1 && l2 != -1)
        {
            int diff = l1 - l2;
            // 判断两者差值的绝对值是否小于等于1
            // 是的话就可以搜下一个了
            if (abs(l1 + diff - arr[ni]) <= 1)
            {
                // 不用改，可以直接搜下一个
                if (l1 + diff == arr[ni])
                    dfs(ni + 1, arr[ni], l1, change_num);

                else if (l1 + diff == arr[ni] + 1)
                    dfs(ni + 1, arr[ni] + 1, l1, change_num + 1);

                else if (l1 + diff == arr[ni] - 1)
                    dfs(ni + 1, arr[ni] - 1, l1, change_num + 1);
            }
        }
        // 第一、二个数，直接往下搜
        else
        {
            dfs(ni + 1, arr[ni], l1, change_num);
            dfs(ni + 1, arr[ni] - 1, l1, change_num + 1);
            dfs(ni + 1, arr[ni] + 1, l1, change_num + 1);
        }
    }
}
int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    dfs(0, -1, -1, 0);
    cout << min_change << endl;
}