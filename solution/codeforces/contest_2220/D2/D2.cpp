#include <bits/stdc++.h>
using namespace std;

map<vector<int>, int> save_qry;

vector<int> merge_vec(vector<int> vec, vector<int> willmerge)
{
    for (auto v : willmerge)
        vec.push_back(v);
    return vec;
}

vector<int> take_first_k(vector<int> vec, int cnt)
{
    vector<int> v;
    for (int i = 0; i < cnt; i++)
    {
        v.push_back(vec[i]);
    }
    return v;
}

void print_ans(vector<int> vec)
{
    cout << "!";
    for (auto v : vec)
    {
        cout << " " << v;
    }
    cout << endl;
}

int qry(vector<int> vec)
{
    sort(vec.begin(), vec.end());
    if (save_qry.count(vec) == 1)
        return save_qry[vec];
    cout << "? " << vec.size();
    for (auto v : vec)
    {
        cout << " " << v;
    }
    cout << endl;
    int ret;
    cin >> ret;
    if (ret == -1)
        exit(-1);
    save_qry[vec] = ret;
    return ret;
}

bool check_has_appears_thrice(vector<int> vec)
{
    auto ret = qry(vec);
    int sz = vec.size();
    return (sz - ret) % 2 != 0;
}

int appears_thrice_last_idx(vector<int> vec)
{
    int l = 3, r = vec.size();
    while (l + 1 < r)
    {
        int mid = (l + r) / 2;
        if (check_has_appears_thrice(take_first_k(vec, mid)))
        {
            r = mid;
        }
        else
        {
            l = mid;
        }
    }
    if (check_has_appears_thrice(take_first_k(vec, l)))
    {
        return l - 1;
    }
    else
    {
        return r - 1;
    }
}

void sol()
{
    save_qry.clear();
    int N;
    cin >> N;
    vector<int> vec;
    for (int i = 1; i <= N * 2 + 1; i++)
    {
        vec.push_back(i);
    }

    int ind1 = appears_thrice_last_idx(vec);
    auto vec2 = take_first_k(vec, ind1);
    vec2 = merge_vec(vector<int>{vec[ind1]}, vec2);

    int ind2 = appears_thrice_last_idx(vec2);
    auto vec3 = take_first_k(vec2, ind2);
    vec3 = merge_vec(vector<int>{vec2[ind2]}, vec3);

    int ind3 = appears_thrice_last_idx(vec3);
    auto ans_vec = take_first_k(vec3, 2);

    ans_vec.push_back({vec3[ind3]});

    print_ans(ans_vec);
}

int32_t main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
    {
        sol();
    }
}
