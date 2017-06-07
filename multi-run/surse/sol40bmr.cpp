#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define maxn 100010
#define baza 1073741824
#define maxl 100010

int n, m, k;
int v[maxn];
char s[maxl];
int ng, kg;
int ras[maxl], id[maxl];
int unu[maxl];

void print(int x[]) {
    for(int i = x[0]; i > 0; --i)
        printf("%d", x[i]);
    printf("\n");
}

void mult(int a[], int b) {
    long long carry = 0;
    for (int i = 1; i <= a[0] || carry > 0; ++i) {
        a[0] = max(a[0], i);
        carry = carry + 1LL * a[i] * b;
        a[i] = carry % baza;
        carry /= baza;
    }
}

int div(int a[], int b) {
    long long carry = 0;
    for (int i = a[0]; i > 0; --i) {
        carry = carry * baza + a[i];
        a[i] = carry / b;
        carry = carry % b;
    }
    while (a[0] > 1 && a[a[0]] == 0) {
        --a[0];
    }
    return carry;
}

void dif(int a[], int b[]) {
    long long carry = 0;
    for (int i = 1; i <= a[0] || i <= b[i]; ++i) {
        a[i] -= b[i];
        if (a[i] < 0){
            a[i] += baza;
            --a[i + 1];
        }
    }
    while(a[0] > 1 && a[a[0]] == 0) {
        --a[0];
    }
}

void add(int a[], int b[]) {
    long long carry = 0;
    for (int i = 1; i <= a[0] || i <= b[0] || carry > 0; ++i) {
        a[0] = max(a[0], i);
        carry += a[i] + b[i];
        a[i] = carry % baza;
        carry /= baza;
    }
}

int leq(int a[], int b[]) {
    if (a[0] != b[0]) {
        return a[0] < b[0];
    }
    for (int i = a[0]; i > 0; --i) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return 1;
}


void GetInitial(int n, int k, int ras[]) {
    for (int i = 1; i <= ras[0]; ++i)
        ras[i] = 0;
    ras[0] = ras[1] = 1;
    for (int i = n + 1; i <= n + k - 1; ++i) {
        mult(ras, i);
    }
    for (int i = 1; i <= k - 1; ++i) {
        div(ras, i);
    }
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
    int sum = n;
    for (int i = 1; i < k; ++i) {
        for (int j = 0; j < v[i]; ++j) {
            GetInitial(sum, k - i, ras);
            add(id, ras);
            --sum;
        }
    }
    int ok = 1;
    while (id[0] > 1 || id[1] != 0 || ok == 1) {
        printf("%d", div(id, 2));
        ok = 0;
    }
}

void decode() {
    scanf("%d%d%d", &k, &n, &m);
    scanf("\n%s\n", s);
    int l = strlen(s);
    for (int i = l - 1; i >= 0; --i) {
        mult(id, 2);
        if (s[i] == '1') {
            add(id, unu);
        }
    }
    int sum = n;
    for (int i = 1; i < k; ++i) {
        GetInitial(sum, k - i, ras);
        while (leq(ras, id)) {
            dif(id, ras);
            ++v[i];
            --sum;
            GetInitial(sum, k - i, ras);
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
    for (int i = 1; i <= m; ++i) {
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

    unu[0] = unu[1] = 1;
    id[0] = 1;

    if(tip == 1)
        code();
    else
        decode();
}
