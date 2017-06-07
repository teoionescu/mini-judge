#include <cstdio>
#include <cstring>

using namespace std;

#define maxn 20

int n, m, k;
int v[maxn];
char s[maxn*maxn];
int ng, kg;

void DecreaseK(long long& ras) {
    ras = ras * (kg - 1) / (ng + kg - 1);
    --kg;
}

void DecreaseN(long long& ras) {
    ras = ras * ng / (ng + kg - 1);
    --ng;
}

void GetInitial(int n, int k, long long& ras) {
    ras = 1;
    for (int i = n + 1; i <= n + k - 1; ++i)
        ras *= i;
    for (int i = 1; i <= k - 1; ++i)
        ras /= i;
    ng = n;
    kg = k;
}

void code() {
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        ++v[x];
    }
    long long id = 0, sum = n, ras;
    GetInitial(n, k, ras);
    //printf("%d\n", ras);
    for (int i = 1; i < k; ++i) {
        DecreaseK(ras);
        for (int j = 0; j < v[i]; ++j) {
            id += ras;
            DecreaseN(ras);
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
    GetInitial(n, k, ras);
    for (int i = 1; i < k; ++i) {
        DecreaseK(ras);
        while (ras <= id) {
            id -= ras;
            ++v[i];
            DecreaseN(ras);
        }
    }
    v[k] = ng;
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

    if(tip == 1)
        code();
    else
        decode();
}
