#include <cstdio>

using namespace std;

#define maxn 10000010

int n, m, k, lim;
FILE *in, *out, *in2;
char s[maxn];

int main()
{
    in = fopen("op.in", "r");
    out = fopen("op.out.0", "r");
    in2 = fopen("op.in.1", "w");

    fscanf(in, "%d%d%d%d", &k, &n, &m, &lim);
    fscanf(out, "%s", s);
    fprintf(in2, "2 %d %d %d\n", k, n, m);
    fprintf(in2, "%s\n", s);
    for(int i = 0; i < n; ++i)
    {
        int x;
        fscanf(in, "%d", &x);
    }
    for(int i = 0; i < m; ++i) {
        int x;
        fscanf(in, "%d", &x);
        fprintf(in2, "%d\n", x);
    }
    return 0;
}
