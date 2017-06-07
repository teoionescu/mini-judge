#include <bits/stdc++.h>

using namespace std;

#define maxn 100010

int n, m, k, lim, typegen, prob;
int v[maxn];

void GenerateRandom() {
    for (int i = 1; i <= n; ++i) {
        int x = rand() % k + 1;
        ++v[x];
        cout << x << "\n";
    }
}

void GenerateBigOne(int poz) {
    for (int i = 1; i <= n; ++i) {
        int zar = rand() % 100, x;
        if (zar < prob)
            x = poz;
        else
            x = rand() % k + 1;
        ++v[x];
        cout << x << "\n";
    }
}

void GenerateOtherRandom() {
    vector<int> v;
    int sum = 0;
    v.push_back(sum);
    for (int i = 1; i <= k; ++i) {
        int zar = rand() % 1000;
        sum += zar;
        v.push_back(sum);
    }

    for (int i = 1; i <= n; ++i) {
        int zar = rand() % sum;
        int j = 0;
        while (v[j] <= zar) {
            ++j;
        }
        ++v[j];
        cout << j << "\n";
    }
}

int main(int argc, char** argv){
    srand(time(0));
	vector<int> args;

	for(int i=1;i<argc;i++){
		int x = atoi(argv[i]);
		args.push_back(x);
	}

    k = args[0];
    n = args[1];
    m = args[2];
    lim = args[3];
    typegen = args[4];
    prob = args[5];

	cout << k << " " << n << " " << m << " " << lim << "\n";

    if (typegen == 0)
        GenerateRandom();
    if (typegen == 1)
        GenerateBigOne(1);
    if (typegen == 2)
        GenerateBigOne(k/2);
    if (typegen == 3)
        GenerateBigOne(k);
    if (typegen == 4)
        GenerateOtherRandom();

    vector<int> a;
    for (int i = 1; i <= k; ++i) {
        a.push_back(i);
    }

    random_shuffle(a.begin(), a.end());

    int added = 0, mx = 0;

    for (int i = 1; i <= k; ++i) {
        if(v[i] > mx) {
            mx = v[i];
        }
    }

    for (int i = 0; i < k; ++i) {
        int nod = a[i];

        while(v[nod] <= mx && added < m) {
            ++added;
            cout << nod << "\n";
            ++v[nod];
        }

        int pls = rand() % 10;

        while (pls > 0 && added < m) {
            ++added;
            cout << nod << "\n";
            ++v[nod];
            --pls;
        }

        mx = v[nod];
    }

    while (added < m) {
        int nod = rand() % k + 1;
        cout << nod << "\n";
        added++;
    }

	return 0;
}
