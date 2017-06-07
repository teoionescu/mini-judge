#include <cstdio>
#include <cstring>

using namespace std;

#define maxn 20

int n, m, k;
int v[maxn];
long long fact[maxn];
char s[maxn*maxn];
int ng, kg;

void NKvotes(int n, int k, long long& ras) {
    ras = fact[n + k - 1] / fact[k - 1] / fact[n];
}

void code() {
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        ++v[x];
    }
    long long id = 0, sum = n, ras;
    for (int i = 1; i < k; ++i) {
        for (int j = 0; j < v[i]; ++j) {
            long long ras;
            NKvotes(sum, k - i, ras);
            id += ras;
            --sum;
        }
    }

    while (id) {
        printf("%d", id % 2);
        id /= 2;
    }
}

void decode() {
    scanf("%d%d%d", &k, &n, &m);
    scanf("\n%s\n", s);
    int l = strlen(s);
    long long id = 0, sum = n, ras;
    for (int i = l - 1; i >= 0; --i) {
        id = id * 2 + s[i] - '0';
    }
    for (int i = 1; i < k; ++i) {
        NKvotes(sum, k - i, ras);
        while (ras <= id) {
            id -= ras;
            ++v[i];
            --sum;
            NKvotes(sum, k - i, ras);
        }
    }
    v[k] = sum;
    int mx = 0, who = 0;
    for (int i = 1; i <= k; ++i) {
        if (v[i] > mx) {
            who = i;
            mx = v[i];
        }
    }
    for (int i=1; i<=m; ++i) {
        int x;
        scanf("%d", &x);
        ++v[x];
        if (v[x] > mx) {
            who = x;
            mx = v[x];
        }
        printf("%d\n", who);
    }
}

int main() {
    freopen("op.in", "r", stdin);
    freopen("op.out", "w", stdout);

    int tip;
    scanf("%d", &tip);

    fact[0] = 1;
    for (int i = 1; i < 20; ++i)
        fact[i] = i * fact[i - 1];

    if(tip == 1)
        code();
    else
        decode();
}
