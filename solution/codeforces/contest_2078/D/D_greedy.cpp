#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define max_len 50
struct op_info
{
    char op;
    int val;
} op_left[max_len], op_right[max_len];

int add_num(op_info op_do, int base_cnt)
{
    if (op_do.op == '+')
    {
        return op_do.val;
    }
    else
    {
        return base_cnt * (op_do.val - 1);
    }
}

void sol()
{
    int32_t N;
    cin >> N;
    for (int32_t i = 0; i < N; i++)
    {
        char op1, op2;
        int32_t val1, val2;
        cin >> op1 >> val1 >> op2 >> val2;
        op_left[i].op = op1;
        op_left[i].val = val1;

        op_right[i].op = op2;
        op_right[i].val = val2;
    }

    int lcnt = 1, rcnt = 1;
    for (int32_t i = 0; i < N; i++)
    {
        int ladd = add_num(op_left[i], lcnt);
        int radd = add_num(op_right[i], rcnt);

        if (i != N - 1)
        {
            bool is_al = true;
            for (int j = i + 1; j < N; j++)
            {
                int ml = 1, mr = 1;
                if (op_left[j].op == 'x')
                {
                    ml = op_left[j].val;
                }
                if (op_right[j].op == 'x')
                {
                    mr = op_right[j].val;
                }
                if (ml > mr)
                {
                    is_al = true;
                    break;
                }
                else if (ml < mr)
                {
                    is_al = false;
                    break;
                }
            }

            if (is_al)
            {
                lcnt += (ladd + radd);
            }
            else
            {
                rcnt += (ladd + radd);
            }
        }
        else
        {
            lcnt += (ladd + radd);
        }
    }
    cout << (lcnt + rcnt) << "\n";
}
int32_t main()
{
    int32_t T = 1;
    cin >> T;
    while (T--)
    {
        sol();
    }
}