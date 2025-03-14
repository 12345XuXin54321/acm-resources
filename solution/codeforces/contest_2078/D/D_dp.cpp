#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define max_len 50
struct op_info
{
    char op;
    int val;
} op_left[max_len], op_right[max_len];
int32_t N;

int to_end_mult_left[max_len];
int to_end_mult_right[max_len];

int get_mult(op_info op)
{
    if (op.op == '+')
        return 1;
    else
        return op.val;
}

void sol()
{
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

    to_end_mult_left[N] = 1;
    to_end_mult_right[N] = 1;

    for (int32_t i = N - 1; i >= 0; i--)
    {
        to_end_mult_left[i] = to_end_mult_left[i + 1] + (get_mult(op_left[i]) - 1) * max(to_end_mult_left[i + 1], to_end_mult_right[i + 1]);
        to_end_mult_right[i] = to_end_mult_right[i + 1] + (get_mult(op_right[i]) - 1) * max(to_end_mult_left[i + 1], to_end_mult_right[i + 1]);
    }

    int ans = to_end_mult_left[0] + to_end_mult_right[0];
    for (int i = 0; i < N; i++)
    {
        if (op_left[i].op == '+')
        {
            ans += op_left[i].val * max(to_end_mult_left[i + 1], to_end_mult_right[i + 1]);
        }
        if (op_right[i].op == '+')
        {
            ans += op_right[i].val * max(to_end_mult_left[i + 1], to_end_mult_right[i + 1]);
        }
    }

    cout << ans << "\n";
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