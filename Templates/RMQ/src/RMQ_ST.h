#include <bits/stdc++.h>
using namespace std;

#define max_len 100010
#define log2_max_len 18
class RMQ
{
    int range_max_toR[max_len][log2_max_len];
    int log2_val[max_len];
    int len;

    void init_log2_val()
    {
        log2_val[1] = 0;
        for (int i = 2; i < max_len; i++)
        {
            log2_val[i] = log2_val[i / 2] + 1;
        }
    }

public:
    void build(int N, int *arr)
    {
        init_log2_val();

        len = N;

        for (int i = 0; i < N; i++)
        {
            range_max_toR[i][0] = arr[i];
        }

        for (int log2_range = 1; log2_range <= log2_val[N]; log2_range++)
        {
            int range_len = (1 << log2_range);
            int half_len = range_len / 2;
            for (int i = 0; i < N; i++)
            {
                int lbeg = i;
                int rbeg = min(i + half_len, N - half_len);
                range_max_toR[i][log2_range] = max(
                    range_max_toR[lbeg][log2_range - 1],
                    range_max_toR[rbeg][log2_range - 1]
                );
            }
        }
    }

    int query_max(int l, int r)
    {
        int qry_len = r - l + 1;
        int log2_qry = log2_val[qry_len];
        int range_len = (1 << log2_qry);

        int lmax = range_max_toR[l][log2_qry];
        int rmax = range_max_toR[r - range_len + 1][log2_qry];
        return max(lmax, rmax);
    }
};

