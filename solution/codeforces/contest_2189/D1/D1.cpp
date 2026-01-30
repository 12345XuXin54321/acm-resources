#include <bits/stdc++.h>
using namespace std;
#define int int64_t
constexpr int mod_n = 1e9 + 7;
constexpr int max_prime = 2e5 + 10;
#define mod(x) ((x) % mod_n)

string str;
int N, c;
map<int, int> c_factor;

vector<int> prime;
int factor_arr[max_prime];
bool is_not_prime[max_prime];
void init_prime()
{
    for (int i = 2; i < max_prime; i++)
    {
        if (!is_not_prime[i])
        {
            prime.push_back(i);
            factor_arr[i] = i;
        }
        for (auto p : prime)
        {
            if (i * p >= max_prime)
                break;
            is_not_prime[i * p] = true;
            factor_arr[i * p] = p;
            if (i % p == 0)
                break;
        }
    }
}

void rm_factor(int num)
{
    while (num != 1)
    {
        int p = factor_arr[num];
        num /= p;
        if (c_factor.count(p))
        {
            c_factor[p]--;
            if (c_factor[p] == 0)
            {
                c_factor.erase(p);
            }
        }
    }
}

int get_ans()
{
    if (str[0] == '0' || str[N - 1] == '0')
    {
        return -1;
    }

    int ans = 1;
    for (int i = 1; i < N; i++)
    {
        if (str[i] == '1')
        {
            // mex([p_l, ..., p_r]) = i + 1
            ans *= 2;
            ans = mod(ans);
            rm_factor(2);
        }
        else // (str[i] == '0')
        {
            ans *= i;
            ans = mod(ans);
            rm_factor(i);
        }
    }
    if (c_factor.size() != 0)
    {
        return ans;
    }
    else
    {
        return -1;
    }
}

void get_factor()
{
    c_factor.clear();
    for (auto p : prime)
    {
        while (c % p == 0)
        {
            c_factor[p]++;
            c /= p;
        }
        if (p * p > 1e9 + 10)
            break;
    }
    if (c != 1)
    {
        c_factor[c]++;
    }
}

void sol()
{
    cin >> N >> c;
    cin >> str;

    get_factor();
    int ans = get_ans();
    cout << ans << "\n";
}

int32_t main()
{
    init_prime();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
    {
        sol();
    }
}
