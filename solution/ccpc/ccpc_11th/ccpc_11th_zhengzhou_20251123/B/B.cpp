#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define max_len 1000010

template <typename T>
constexpr T qpow(T x, uint64_t n)
{
    T res{1};
    for (; n != 0; n /= 2, x *= x)
    {
        if (n % 2 == 1)
        {
            res *= x;
        }
    }
    return res;
}

template <typename T, T ModP>
class ModInt
{
    T x;

    constexpr T mod(const T v)
    {
        T res = v % ModP;
        if (res < 0)
            res += ModP;
        return res;
    }

public:
    constexpr ModInt() = default;
    constexpr ModInt(T v)
    {
        x = mod(v);
    }
    constexpr T val() const
    {
        return x;
    }

    constexpr ModInt inv() const
    {
        return qpow(*this, ModP - 2);
    }

    constexpr ModInt &operator+=(const ModInt &rhs)
    {
        x = mod(x + rhs.x);
        return *this;
    }
    constexpr ModInt &operator-=(const ModInt &rhs)
    {
        x = mod(x - rhs.x);
        return *this;
    }
    constexpr ModInt &operator*=(const ModInt &rhs)
    {
        x = mod(x * rhs.x);
        return *this;
    }
    constexpr ModInt &operator/=(const ModInt &rhs)
    {
        (*this) *= rhs.inv();
        return *this;
    }

    friend constexpr ModInt operator+(ModInt lhs, const ModInt &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend constexpr ModInt operator-(ModInt lhs, const ModInt &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr ModInt operator*(ModInt lhs, const ModInt &rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr ModInt operator/(ModInt lhs, const ModInt &rhs)
    {
        lhs /= rhs;
        return lhs;
    }
};

using point = array<int, 3>;
using Mint = ModInt<int, int(1e9 + 7)>;

int N;
point arr[max_len];

int x_split[max_len];
int y_split[max_len];
int z_split[max_len];

int x_cnt, y_cnt, z_cnt;
int L, W, H;

struct cmp_point
{
    int dim;
    bool operator()(const point &p1, const point p2) const
    {
        return p1[dim] < p2[dim];
    }
};

int find_last_lt_idx(int *val_arr, int len, int x)
{
    int l = 0, r = len - 1;
    while (l + 1 < r)
    {
        int mid = (l + r) / 2;
        if (val_arr[mid] < x)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    if (val_arr[r] < x)
        return r;
    else
        return l;
}

int to_idx(point &p)
{
    int x = find_last_lt_idx(x_split, x_cnt, p[0]);
    int y = find_last_lt_idx(y_split, y_cnt, p[1]);
    int z = find_last_lt_idx(z_split, z_cnt, p[2]);
    return x * (y_cnt * z_cnt) + y * z_cnt + z;
}

int cnt_arr[max_len];

int get_ans()
{
    if (N % (x_cnt * y_cnt * z_cnt) != 0)
        return 0;

    int cnt_per = N / (x_cnt * y_cnt * z_cnt);

    Mint ans = 1;

    array<int, 3> dim_cnt = {x_cnt, y_cnt, z_cnt};
    array<int *, 3> dim_split = {x_split, y_split, z_split};

    auto fill_split = [&](int dim) -> void
    {
        sort(arr, arr + N, cmp_point{dim});
        int dim_size = x_cnt * y_cnt * z_cnt / dim_cnt[dim];
        int *split_arr = dim_split[dim];

        for (int i = 1; i <= dim_cnt[dim]; i++)
        {
            int split_idx = dim_size * i * cnt_per - 1;
            int split_l = arr[split_idx][dim];
            split_arr[i] = split_l;
            if (i != dim_cnt[dim])
            {
                int split_r = arr[split_idx + 1][dim] - 1;
                if (split_l > split_r)
                {
                    ans = 0;
                }
                else
                {
                    ans *= (split_r - split_l + 1);
                }
            }
        }
    };

    fill_split(0);
    fill_split(1);
    fill_split(2);

    if (ans.val() == 0)
        return ans.val();

    for (int i = 0; i < N; i++)
    {
        cnt_arr[to_idx(arr[i])]++;
    }
    for (int i = 0; i < N / cnt_per; i++)
    {
        if (cnt_arr[i] != cnt_per)
            return 0;
    }
    return ans.val();
}

void sol()
{
    cin >> L >> W >> H;
    cin >> x_cnt >> y_cnt >> z_cnt;
    x_cnt++, y_cnt++, z_cnt++;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }

    int ans = get_ans();
    cout << ans << "\n";
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        sol();
    }
}