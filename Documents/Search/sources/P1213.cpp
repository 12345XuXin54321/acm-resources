#include <bits/stdc++.h>
using namespace std;
#define max_len ((1 << 20) + 10)
// 所有的时钟，可以用一个整数存
// 每2位可以看成一个时钟的四种状态
// 一共用了18位
struct all_clock
{
    // 低位的时钟存到数字的低位
    int n;
    // 得到第i个时钟的值
    int get_i_clock(int i)
    {
        return (n >> (i * 2)) % 4;
    }
    // 设置第i个时钟的值
    void set_clock(int i, int val)
    {
        // 先把当前位的清零
        n &= ~(0x3 << (i * 2));
        n ^= (val << (i * 2));
    }
};

// 移动一个时钟
void mov_clock(all_clock &ac, int ck)
{
    ac.set_clock(ck, (ac.get_i_clock(ck) + 1) % 4);
}

// 移动所有的时钟
all_clock move_a_step(all_clock ac, int op)
{
    switch (op)
    {
    case 1:
        mov_clock(ac, 0);
        mov_clock(ac, 1);
        mov_clock(ac, 3);
        mov_clock(ac, 4);
        break;
    case 2:
        mov_clock(ac, 0);
        mov_clock(ac, 1);
        mov_clock(ac, 2);
        break;
    case 3:
        mov_clock(ac, 1);
        mov_clock(ac, 2);
        mov_clock(ac, 4);
        mov_clock(ac, 5);
        break;
    case 4:
        mov_clock(ac, 0);
        mov_clock(ac, 3);
        mov_clock(ac, 6);
        break;
    case 5:
        mov_clock(ac, 1);
        mov_clock(ac, 3);
        mov_clock(ac, 4);
        mov_clock(ac, 5);
        mov_clock(ac, 7);
        break;
    case 6:
        mov_clock(ac, 2);
        mov_clock(ac, 5);
        mov_clock(ac, 8);
        break;
    case 7:
        mov_clock(ac, 3);
        mov_clock(ac, 4);
        mov_clock(ac, 6);
        mov_clock(ac, 7);
        break;
    case 8:
        mov_clock(ac, 6);
        mov_clock(ac, 7);
        mov_clock(ac, 8);
        break;
    case 9:
        mov_clock(ac, 4);
        mov_clock(ac, 5);
        mov_clock(ac, 7);
        mov_clock(ac, 8);
        break;
    }
    return ac;
}

// 每一个状态最小的步骤数
int status_step[max_len];
// 上一个状态
int status_pre_s[max_len];
// 上一个状态到现在的状态
// 需要走的步骤
int status_op[max_len];

// bfs
// 对于每个状态，遍历所有可能的下一步
// 如果没有被搜索过，就加入队列
int bfs(all_clock beg_status)
{
    status_step[beg_status.n] = 1;
    queue<all_clock> que_status;
    que_status.push(beg_status);
    while (que_status.size() != 0)
    {
        auto now_status = que_status.front();
        que_status.pop();
        for (int i = 1; i <= 9; i++)
        {
            auto next_status = move_a_step(now_status, i);

            // 如果没有到达过这个状态
            // 才加入队列
            if (status_step[next_status.n] == 0)
            {
                que_status.push(next_status);
                status_step[next_status.n] = status_step[now_status.n] + 1;
                status_pre_s[next_status.n] = now_status.n;
                status_op[next_status.n] = i;
                // 如果搜到了，就直接返回
                if (next_status.n == 0)
                {
                    return status_step[now_status.n] + 1;
                }
            }
        }
    }
    return status_step[0];
}

// 输出经过的步骤
void print_op()
{
    int ac_i = 0;
    stack<int> stk;
    for (int i = 1; i < status_step[0]; i++)
    {
        // 把上个状态到这个状态的
        // 操作加入栈
        stk.push(status_op[ac_i]);
        // 到上个状态
        ac_i = status_pre_s[ac_i];
    }
    while (stk.size() != 0)
    {
        cout << stk.top();
        stk.pop();
        if (stk.size() != 0)
        {
            cout << " ";
        }
    }

    cout << endl;
}

int main()
{
    all_clock ac;
    ac.n = 0;
    for (int i = 0; i < 9; i++)
    {
        int val;
        cin >> val;
        ac.set_clock(i, (val / 3) % 4);
    }
    bfs(ac);
    print_op();
}