#include <bits/stdc++.h>
using namespace std;
#define max_len 30000
bool input_str(int &val, int &path, bool &is_end)
{
    string str;
    if (!(cin >> str))
    {
        return false;
    }

    if (str == "()")
    {
        is_end = true;
    }
    else
    {
        val = 0;
        int ps = 1;
        while (str[ps] != ',')
        {
            val *= 10;
            val += (str[ps] - '0');
            ps++;
        }
        path = 1;
        for (int i = ps + 1; i < str.size() - 1; i++)
        {
            path *= 2;
            if (str[i] == 'R')
            {
                path += 1;
            }
        }

        is_end = false;
    }
    return true;
}

int node_val[max_len * 2];
int N = 0;

bool input_data()
{
    N = 0;
    for (int i = 0; i < max_len; i++)
    {
        node_val[i] = 0;
    }

    int val, node_path;
    bool is_end = false;
    while (input_str(val, node_path, is_end) == true)
    {
        // cout << node_val << " " << node_path << "\n";

        if (is_end)
        {
            return true;
        }
        else
        {
            node_val[node_path] = val;
            N++;
        }
    }
    return false;
}

int get_tree_node(int ri)
{
    // cout << ri << endl;
    if (node_val[ri] == 0)
    {
        return 0;
    }
    else
    {
        return 1 +
               get_tree_node(ri * 2) +
               get_tree_node(ri * 2 + 1);
    }
}

bool sol()
{
    bool isn_eof = input_data();
    if (isn_eof == false)
    {
        return false;
    }
    if (get_tree_node(1) == N)
    {
        int pn = 0;
        for (int i = 0; i < max_len; i++)
        {
            if (node_val[i] != 0)
            {
                if (pn != 0)
                {
                    cout << " ";
                }
                pn++;
                cout << node_val[i];
            }
        }
        cout << "\n";
    }
    else
    {
        cout << "not complete\n";
    }
    return true;
}

int main()
{
    while (sol() == true)
        ;
}