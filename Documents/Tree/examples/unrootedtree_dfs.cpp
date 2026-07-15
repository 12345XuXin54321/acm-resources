#include <queue>
#include <list>
#include <iostream>
using namespace std;

struct tree_node
{
    list<int> linked;
} node_arr[10000];

void dfs(int rooti, int from)
{
    cout << rooti << "\n";
    for (auto chi : node_arr[rooti].linked)
    {
        if (chi != from)
        {
            dfs(chi, rooti);
        }
    }
}

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N - 1; i++)
    {
        int v, u;
        cin >> v >> u;
        node_arr[v].linked.push_back(u);
        node_arr[u].linked.push_back(v);
    }
    dfs(1, -1);
}