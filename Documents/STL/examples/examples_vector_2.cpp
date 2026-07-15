#include <vector>
#include <iostream>
using namespace std;
int main()
{
    vector<vector<int>> arr;
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
    {
        // 在末尾添加空的vector<int>
        arr.push_back(vector<int>());
        for (int j = 0; j < n; j++)
        {
            int num;
            cin >> num;
            // arr[i]的类型是vector<int>
            arr[i].push_back(num);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}