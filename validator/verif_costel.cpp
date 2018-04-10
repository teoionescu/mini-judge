// Evaluator problema poligon, ONI 2018
#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;
const int NMAX = 2000 + 5;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0):
        x(_x), y(_y) {}
    friend inline long double dist(const Point &A, const Point &B) {
        return sqrtl(1LL * (A.x - B.x) * (A.x - B.x) +
                    1LL * (A.y - B.y) * (A.y - B.y));
    }
} points[NMAX];

// Approved grader output format
void result(char msg[], int p) {
    printf("%d %s", p, msg);
    exit(0);
}

bool vis[NMAX];
int nxt[NMAX], prc[NMAX];

int main() {
    ifstream fin("poligon.in");
    ifstream fok("poligon.ok");
    ifstream fout("poligon.out");

    if (!fin) result("Fisier de intrare lipsa", 0);
    if (!fok) result("Fisier OK lipsa", 0);
    if (!fout) result("Fisier de iesire lipsa", 0);

    int type;
    if (!(fin >> type)) result("Fisier de intrare corupt", 0);

    if (type == 1) {
        int T;
        fin >> T;
        while (T --) {    
            long double ourAns;
            if (!(fok >> ourAns))
                result("Fisier OK corupt", 0);
            long double theirAns;
            if (!(fout >> theirAns))
                result("Fisier de iesire corupt", 0);
            const long double EPS = 1E-6L;
            if (fabsl(theirAns - ourAns) >= EPS)
                result("Cost gresit", 0);
        }
        result("Corect", 4);
    }
    else {
        int T;
        fin >> T;
        while (T --) {
            int N;
            fin >> N;
            for (int i = 1; i <= N; ++ i)
                fin >> points[i].x >> points[i].y;

            const long double EPS = 1E-6L;
            for (int i = 1; i <= N; ++ i)
                nxt[i] = i % N + 1, prc[i % N + 1] = i, vis[i] = false;

            long double sum = 0;
            for (int i = 1; i < N; ++ i) {
                int a, b;
                if (!(fout >> a >> b))
                    result("Numar de mutari afisate prea mic", 0);
                if (a == b || a < 1 || b < 1 || a > N || b > N)
                    result("Mutare invalida", 0);
                sum += dist(points[a], points[b]);
                if ((b == nxt[a] || b == prc[a]) && !vis[a]) {
                    vis[a] = true;
                    nxt[prc[a]] = nxt[a], prc[nxt[a]] = prc[a];
                }
                else
                    result("Mutare invalida", 0);
            }

            for (int i = 1; i <= N; ++ i)
                nxt[i] = i % N + 1, prc[i % N + 1] = i, vis[i] = false;

            long double ourAns = 0;
            for (int i = 1; i < N; ++ i) {
                int a, b;
                assert(fok >> a >> b);
                assert(!(a == b || a < 1 || b < 1 || a > N || b > N));
                ourAns += dist(points[a], points[b]);
                if ((b == nxt[a] || b == prc[a]) && !vis[a]) {
                    vis[a] = true;
                    nxt[prc[a]] = nxt[a], prc[nxt[a]] = prc[a];
                }
                else
                    assert(false);
            }

            if (fabsl(sum - ourAns) >= EPS)
                result("Costul muchiilor afisate nu este minim", 0);
        }
        result("Corect", 1);
    }
    return 0;
}
