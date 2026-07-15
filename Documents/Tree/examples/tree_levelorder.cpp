#include <queue>
#include <list>
#include <iostream>
using namespace std;

struct tree_node
{
    list<int> children;
} node_arr[10000];

void levelorder(int rooti)
{
    // node, level
    queue<pair<int, int>> que;
    que.push(make_pair(rooti, 0));
    while (que.size() != 0)
    {
        auto [node_i, lv] = que.front();
        que.pop();
        // 访问结点
        cout << node_i << " "
             << lv << "\n";

        for (auto chi : node_arr[node_i].children)
        {
            que.push(make_pair(chi, lv + 1));
        }
    }
}

int main()
{
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        int K;
        cin >> K;
        for (int j = 0; j < K; j++)
        {
            int tmp;
            cin >> tmp;
            node_arr[i].children.push_back(tmp);
        }
    }
    levelorder(1);
}