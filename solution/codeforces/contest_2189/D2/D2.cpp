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

    int ans = 2;
    rm_factor(2);
    vector<int> factors_may_multiply;
    for (int i = 1; i < N - 1; i++)
    {
        if (str[i] == '1')
        {
            // mex([p_l, ..., p_r]) = i + 1
            ans = mod(ans * 2);
            rm_factor(2);
        }
        else if (str[i] == '0')
        {
            ans = mod(ans * i);
            rm_factor(i);
        }
        else // str[i] == '?'
        {
            if (i % 2 == 0)
            {
                ans = mod(ans * 2);
                rm_factor(2);
            }
            else
            {
                if (i != 1)
                    factors_may_multiply.push_back(i);
            }
        }
    }
    if (c_factor.size() == 0)
    {
        return -1;
    }
    else
    {
        if (c_factor.size() >= 2 || c_factor.begin()->first != 2)
        {
            for (int i = 0; i < factors_may_multiply.size(); i++)
            {
                ans = mod(ans * 2);
            }
        }
        else
        {
            int fact2_cnt = c_factor[2];
            reverse(factors_may_multiply.begin(), factors_may_multiply.end());
            for (int i = 0; i < factors_may_multiply.size(); i++)
            {
                if (i < fact2_cnt - 1)
                {
                    ans = mod(ans * 2);
                }
                else
                {
                    ans = mod(ans * factors_may_multiply[i]);
                }
            }
        }
    }
    return ans;
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
