
// Brut problema countfefete, Baraj 2018
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

int n, root;
vector<vector<int>> G, T;
vector<int> v, mk;

void dfs(int x) {
    mk[x] = 1;
    for(auto it : G[x]) {
        if(!mk[it]) {
            T[x].push_back(it);
            dfs(it);
        }
    }
}

pair<vector<int>, vector<int>> minarb(int x) {
    vector<int> sol, interm;
    int cnt = 0;
    for(auto it : T[x]) {
        auto r = minarb(it);
        if(r.first.size()) {
            cnt++;
            sol.insert(sol.end(), r.first.begin(), r.first.end());
            interm.insert(interm.end(), r.second.begin(), r.second.end());
        }
    }
    interm.push_back(x);
    if(cnt > 1 || mk[x]) {
        sol.insert(sol.end(), interm.begin(), interm.end());
        interm.clear();
    }
    return {sol, interm};
}

int main() {
	freopen("countfefete.in", "r", stdin);
	freopen("countfefete.out", "w", stdout);
    cin >> n;
    
    G.resize(n);
    T.resize(n);
    mk.resize(n);
    v.resize(n);

    for(int i=0; i<n; i++) {
        cin >> v[i];
    }

    for(int i=1; i<n; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for(int i=0; i<n; i++) {
        mk[i] = 0;
    }
    root = 1;
    dfs(root);

    long long ans = 0;

    for(int w=1; w<(1<<n); w++) {
        int x = 0;
        for(int i=0; i<n; i++) {
            mk[i] = ((1<<i)&w) > 0;
            x ^= mk[i]*v[i];
        }
        auto arb = minarb(root);
        int mn = v[arb.first.back()];
        for(auto it : arb.first) {
            mn = min(mn, v[it]);
        }
        x ^= mn;
        ans = (ans + x) % MOD;
    }

    cout << ans << '\n';

    return 0;
}