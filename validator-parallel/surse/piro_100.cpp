
// Solutie problema countfefete, Baraj 2018
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
const int kMaxN = 1e5;
const int kMaxVal = 1e9;

int n, elim;
vector<vector<int>> G;
vector<pair<int,int>> ord;
vector<int> mk, t, a;
vector<unsigned> v, mm;
vector<long long> pw;

int q(int x) {
    int r, y;
    for(r = t[x]; r != t[r]; r = t[r]);
    while(x != r) y = t[x], t[x] = r, x = y;
    return r;
}

void uni(int x, int y) {
    int ap = q(x), bp = q(y);
    if(ap != bp) {
        t[ap] = bp;
        a[bp] += a[ap];
        mm[bp] |= mm[ap];
    }
}

int main() {
    ifstream cin("countfefete.in");
    ofstream cout("countfefete.out");
    cin >> n;
    
    G.resize(n);
    ord.resize(n);
    mk.resize(n);
    v.resize(n);
    t.resize(n);

    a.resize(n);
    mm.resize(n);
    pw.resize(n + 1);

    for(int i=0; i<n; i++) {
        cin >> v[i];
        ord[i] = {v[i], i};
    }
    sort(ord.begin(), ord.end());
    for(int i=0; i<n; i++) {
        t[i] = i;
        mk[i] = 0;
        mm[i] = v[i];
        a[i] = 1;
    }
    
    for(int i=1; i<n; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for(int i=n-1; i>=0; i--) {
        auto x = ord[i].second;
        mk[x] = 1;
        
        auto oper = [&](int c, unsigned minu, unsigned nzero, int sgn) {
            assert(c <= n);
            pw[c-1] += sgn * int((~minu) & nzero);
            pw[c-1] += sgn * int(minu & nzero);    pw[0] -= sgn * int(minu & nzero);
            pw[c]   += sgn * int(minu & (~nzero)); pw[0] -= sgn * int(minu & (~nzero));
        };

        for(auto it : G[x])
            if(mk[it])
                oper(a[q(it)], v[x], mm[q(it)], -1);

        for(auto it : G[x])
            if(mk[it])
                uni(x, it);
        
        oper(a[q(x)], v[x], mm[q(x)], 1);
    }

    long long ans = 0, p = 1;
    for(int i=0; i < pw.size(); i++) {
        long long modif = (p * (llabs(pw[i])%MOD)) % MOD;
        ans += (pw[i] >= 0 ? 1 : -1) * modif;
        while(ans < 0) {
            ans += MOD;
        }
        ans %= MOD;
        p = (p*2) % MOD;
    }

    assert(cout << ans << '\n');
    return 0;
}