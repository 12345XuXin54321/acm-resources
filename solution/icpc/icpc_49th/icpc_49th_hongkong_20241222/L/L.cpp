#include <bits/stdc++.h>
using namespace std;
#define max_len 300

// #define LOCAL_DEBUG

#define cv_char(c) ((c) == 'B')

enum ret_t
{
    unfinish,
    finish,
    err
};

string str_arr[max_len];

bitset<max_len> bit_map[max_len];
int line_size[max_len];

void print_now_map(int n, int m)
{
#ifdef LOCAL_DEBUG
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < line_size[i]; j++)
        {
            cout << (bit_map[i][j] ? 'B' : 'W');
        }
        cout << "\n";
    }
    cout << "---\n";
#endif
}

void init_line(int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        line_size[i] = m;
    }
}
bool check_all_same(int n, bool need_ch)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < line_size[i]; j++)
        {
            if (bit_map[i][j] != need_ch)
            {
                return false;
            }
        }
    }
    return true;
}
ret_t re_linesize(int n, int m, bool need_ch)
{
    for (int i = 0; i < n - 1; i++)
    {
        int lim = (i == 0 ? 1 : line_size[i - 1]);
        while (line_size[i] > lim && bit_map[i][line_size[i] - 1] == need_ch)
        {
            line_size[i]--;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (line_size[i] == 1)
        {
            if (i == n - 2)
            {
                if (check_all_same(n, need_ch))
                {
                    return finish;
                }
                else if (check_all_same(n, !need_ch))
                {
                    return unfinish;
                }
                else
                    return err;
            }
        }
    }
    return unfinish;
}

bool do_a_flip(int n, int m, bool need_ch, string &path)
{
    path = "";
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        while (true)
        {
            bit_map[i][j] = !bit_map[i][j];

            if (j + 1 < line_size[i])
            {
                j++;
                path.push_back('R');
            }
            else
            {
                break;
            }
        }
        if (i + 1 != n)
            path.push_back('D');
    }
    if (j != m - 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void cp_to_bitmap(int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bit_map[i][j] = cv_char(str_arr[i][j]);
        }
    }
}

vector<string> ans_save;
bool check(int n, int m, char need_ch)
{
    ans_save.clear();

    if (n == 1)
    {
        for (int i = 1; i < m; i++)
        {
            if (str_arr[0][i - 1] != str_arr[0][i])
            {
                return false;
            }
        }
        return true;
    }
    else if (m == 1)
    {
        for (int i = 1; i < n; i++)
        {
            if (str_arr[i - 1][0] != str_arr[i][0])
            {
                return false;
            }
        }
        return true;
    }

    cp_to_bitmap(n, m);
    init_line(n, m);

    if (str_arr[0][0] != str_arr[n - 1][m - 1])
    {
        return false;
    }

    while (true)
    {
#ifdef LOCAL_DEBUG
        cout << "=========\n";
#endif
        auto ret = re_linesize(n, m, cv_char(need_ch));
        print_now_map(n, m);
        if (ret == err)
        {
            return false;
        }
        else if (ret == finish)
        {
            return bit_map[0][0] == cv_char(need_ch);
        }

        string ans_s;
        bool is_ok = do_a_flip(n, m, cv_char(need_ch), ans_s);
        print_now_map(n, m);
        if (!is_ok)
        {
            return false;
        }
        if (ans_s.size() != 0)
            ans_save.push_back(ans_s);
    }
}
void sol()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> str_arr[i];
    }

    auto print_ans = []()
    {
        cout << "YES\n";
        cout << ans_save.size() << "\n";
        for (auto s : ans_save)
        {
            cout << s << "\n";
        }
    };

    if (check(n, m, 'B'))
    {
        print_ans();
    }
    else
    {
        if (check(n, m, 'W'))
        {
            print_ans();
        }
        else
        {
            cout << "NO\n";
        }
    }
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        sol();
    }
}