
// Generator problema countfefete, Baraj 2018
// primeste ca argument N si MAXVAL
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv){
	
	vector<int> args;

	for(int i=1;i<argc;i++){
		int x = atoi(argv[i]);
		args.push_back(x);
	}

	if(args.size() != 2) {
		throw;
	}
	srand(time(0));

	random_device rd;
    mt19937 erd(rd());
    uniform_real_distribution<> dist(0, 1);
	double unif_rand_val = dist(erd);

	int n = args[0];
	int maxv = args[1];

	vector<int> t(n, 0), perm(n, 0);

	for(int i=1; i<n; i++) {
		t[i] = rand()%i;
		perm[i] = i;
	}

	random_shuffle(perm.begin(), perm.end());

	vector<pair<int,int>> g(n-1);
	for(int i=1; i<n; i++) {
		g[i-1] = {perm[i], perm[t[i]]};
	}

	auto randval = []() -> long long {
		return 1LL*rand()*rand();
	};

	cout << n << '\n';
	cout << randval()%maxv+1;
	for(int i=1; i<n; i++) {
		cout << ' ' << randval()%maxv+1;
	}
	cout << '\n';
	for(auto it : g) {
		cout << it.first+1 << ' ' << it.second+1 << '\n';
	}
	
	return 0;
}
