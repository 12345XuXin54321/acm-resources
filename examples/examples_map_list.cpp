#include <bits/stdc++.h>
using namespace std;
int main()
{
    int N;
    cin >> N;
    map<string, list<int>> word_map;
    for (int i = 1; i <= N; i++)
    {
        int L;
        cin >> L;
        // 本句话出现过的单词
        set<string> already_add;
        for (int j = 0; j < L; j++)
        {
            string str;
            cin >> str;
            // 如果这句话里没有出现，就把这行的序号加入到映射
            if (already_add.count(str) == 0)
            {
                already_add.insert(str);
                word_map[str].push_back(i);
            }
        }
    }
    int M;
    cin >> M;
    for (int i = 0; i < M; i++)
    {
        string str;
        cin >> str;
        int j = 0;
        for (auto li : word_map[str])
        {
            if (j != 0)
            {
                cout << " ";
            }
            cout << li;
            j++;
        }
        cout << "\n";
    }
}