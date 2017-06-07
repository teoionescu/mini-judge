#include <cstdio>

using namespace std;

int n, m, k, lim;
FILE *in, *out;

int main()
{
    in = fopen("op.in", "r");
    out = fopen("op.in.0", "w");

    fscanf(in, "%d%d%d%d", &k, &n, &m, &lim);
    fprintf(out, "1 %d %d\n", k, n);
    for(int i = 0; i < n; ++i)
    {
        int x;
        fscanf(in, "%d", &x);
        fprintf(out, "%d\n", x);
    }
    return 0;
}
