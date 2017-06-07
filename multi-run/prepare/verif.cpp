#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

ifstream fin("op.in");
ifstream fout("op.out.0");
ifstream fout2("op.out.1");

#define maxn 100010

int k, n, m, lim;
int v[maxn];
string code;

void Msg(int pct, string msg )
{
    cout << pct << ' ' << msg;
    try
    {
        fout.close();
    }
    catch (string ex) {}
    exit(0);
}

int main()
{
    if (!fout)
        Msg(0, "Fisier de iesire lipsa la prima rulare!");
    if (!fout2)
        Msg(0, "Fisier de iesire lipsa la a doua rulare!");

    fin>>k>>n>>m>>lim;
    fout>>code;

    if(code.size() > lim)
        Msg(0, "Codul depaseste lungimea maxima admisa!");

    int mx = 0;
    for(int i = 0; i < n; ++i)
    {
        int x;
        fin>>x;
        ++v[x];
        if (v[x] > mx)
            mx = v[x];
    }
    for(int i = 0; i < m; ++i) {
        int x, y;
        fin>>x;
        ++v[x];
        if (v[x] > mx)
            mx = v[x];

        fout2>>y;
        if (y <= 0 || y > k)
            Msg(0, "Raspuns gresit!");
        if (v[y] != mx)
            Msg(0, "Raspuns gresit!");
    }

    Msg(10, "OK!");
    return 0;
}
