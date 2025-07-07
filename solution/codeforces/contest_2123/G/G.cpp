#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define max_len 200020

int arr[max_len];
int N;

struct mod_arr_t
{
    vector<int> mod_arr;
    int segment_cnt;
};

map<int, mod_arr_t> mapmod_arr;

int non_dec_cnt(vector<int> &vec)
{
    int ans = 1;
    for (int i = 1; i < vec.size(); i++)
    {
        ans += (vec[i - 1] > vec[i]);
    }
    return ans;
}

int get_range_nondec(vector<int> &vec, int ind)
{
    int ans = 0;
    if (ind > 0 && vec[ind - 1] > vec[ind])
        ans++;
    if (ind < vec.size() - 1 && vec[ind] > vec[ind + 1])
        ans++;
    return ans;
}

void change_arrval(mod_arr_t &marr, int ind, int moded_val)
{
    int bef_d = get_range_nondec(marr.mod_arr, ind);
    marr.mod_arr[ind] = moded_val;
    int aft_d = get_range_nondec(marr.mod_arr, ind);
    marr.segment_cnt += (aft_d - bef_d);
}

void init_modarr(int mod_val)
{
    auto &[vec, seg_cnt] = mapmod_arr[mod_val];
    vec = vector<int>(N, 0);
    for (int i = 0; i < N; i++)
    {
        vec[i] = arr[i] % mod_val;
    }
    seg_cnt = non_dec_cnt(vec);
}

void sol()
{
    int m, q;
    cin >> N >> m >> q;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < q; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int ind, x;
            cin >> ind >> x;
            ind--;
            arr[ind] = x;
            for (auto &[modn, marr] : mapmod_arr)
            {
                change_arrval(marr, ind, x % modn);
            }
        }
        else
        {
            int k;
            cin >> k;
            int g = gcd(m, k);
            if (mapmod_arr.count(g) == 0)
            {
                init_modarr(g);
            }
            int ans = mapmod_arr[g].segment_cnt;
            if (ans * g <= m)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
    mapmod_arr.clear();
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