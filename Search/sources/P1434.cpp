#include <bits/stdc++.h>
using namespace std;
#define max_len 110
// 存放高度的数组
int arr[max_len][max_len];
// 是否访问过
bool is_visit[max_len][max_len];
// 每个点的最长的滑雪的长度
int max_sklen[max_len][max_len];

int R, C;
// 检查参数
bool check_xy(int x, int y)
{
    if (x >= R || x < 0 || y >= C || y < 0)
        return false;
    else
        return true;
}
// 搜索的函数
int dfs(int x, int y)
{
    if (check_xy(x, y) == false)
        return 0;
    // 如果已经访问过，就说明已经被计算过，可以直接返回。
    else if (is_visit[x][y] == true)
        return max_sklen[x][y];
    else
    {
        // 上下左右如果满足条件，则分别进行搜索
        int max_sk = 0;
        if (check_xy(x + 1, y) == true && arr[x + 1][y] < arr[x][y])
            max_sk = max(dfs(x + 1, y) + 1, max_sk);

        if (check_xy(x - 1, y) == true && arr[x - 1][y] < arr[x][y])
            max_sk = max(dfs(x - 1, y) + 1, max_sk);

        if (check_xy(x, y + 1) == true && arr[x][y + 1] < arr[x][y])
            max_sk = max(dfs(x, y + 1) + 1, max_sk);

        if (check_xy(x, y - 1) == true && arr[x][y - 1] < arr[x][y])
            max_sk = max(dfs(x, y - 1) + 1, max_sk);

        // 记忆化数组的存储
        is_visit[x][y] = true;
        max_sklen[x][y] = max_sk;
        return max_sk;
    }
}
int main()
{
    cin >> R >> C;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> arr[i][j];

    int max_can_sk = 0;
    // 需要遍历每一个点进行一次搜索
    // 由于进行了记忆化，总共的搜索次数也只是O(n^2)
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            max_can_sk = max(dfs(i, j), max_can_sk);

    cout << max_can_sk + 1 << endl;
}