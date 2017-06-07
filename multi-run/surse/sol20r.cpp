#include <cstdio>
#include <assert.h>
#include <cstring>
#include <iostream>

using namespace std;

const int Q=100001;

int n,k,m;

int v[Q];



void precalc()
{

}

int b[10000000];
char bstring[10000000];
int *enc;

int take_nr(int x)
{
    int rez=0;
    while(x)
    {
        rez++;
        x/=2;
    }
    return rez;
}

void add(int val, int biti)
{
    for(int i=1; i<=biti; i++)
    {
        b[++b[0]]=val%2;
        val/=2;
    }
}

int* encode()
{
    int x;

    int peste=0;

    for(int i=1; i<=n; i++)
    {
        scanf("%d",&x);
        v[x]++;
    }


    int nm=0,act;

    for(int i=1; i<k; i++)
    {
        act=take_nr(v[i]);

        if(act>nm)
            nm=act;
    }

    if(n+k > (k-1)*nm)
    {
        add(0, 1);

        add(nm, 4);

        for(int i=1; i<k; i++)
        {
            add(v[i], nm);
        }
    }
    else
    {
        add(1,1);

        for(int i=1; i<k; i++)
        {
            for(int j=1; j<=v[i]; j++)
            {
                add(1,1);
            }
            add(0,1);
        }
    }

   /* for(int i=1; i<=k; i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<"\n\n";*/

    for(int i=1; i<=b[0]; i++)
    {
        cout<<b[i];
    }
    cout<<"\n";

    return b;
}

int last=0;

int take(int nr)
{
    int act=0;
    for(int i=last+nr; i>last; i--)
    {
        act=act*2+b[i];
    }
    last+=nr;

    return act;

}

void decode()
{
    scanf("%d\n",&m);
    fgets(bstring+1, Q, stdin);

    b[0]=strlen(bstring+1);
    b[0]--;

    for(int i=1; i<=b[0]; i++)
    {
        b[i]=bstring[i]-'0';
    }

    int tip=take(1);

    if(tip==0)
    {
        int pas=take(4);

        for(int i=1; i<k; i++)
        {
            v[i]=take(pas);
        }
    }
    else
    {
        int cnt=0,x;

        for(int i=1; i<k; i++)
        {
            cnt=-1;
            while(true)
            {
                x=take(1);
                cnt++;
                if(x==0)
                {
                    v[i]=cnt;
                    break;
                }
            }
        }
    }



    v[k]=n;

    int max=0;

    for(int i=1; i<k; i++)
    {
        v[k]-=v[i];
    }

    for(int i=1; i<=k; i++)
    {
        //cout<<v[i]<<" ";

        if(v[i] > v[max])
        {
            max=i;
        }
    }

    int x;

    for(int i=1; i<=m; i++)
    {
        scanf("%d",&x);
        v[x]++;
        if(v[x] > v[max])
            max=x;

        printf("%d\n",max);
    }

}

int main()
{
    freopen("op.in", "r",stdin);
    freopen("op.out", "w",stdout);

    int tip;

    scanf("%d",&tip);
    scanf("%d%d\n",&k,&n);

  /*  for(int i=1; i<=n; i++)
    {
        cout<<rand()%k+1<<" ";
    }
    cout<<"\n\n";
*/
    precalc();

    if(tip==1)
    {
        enc=encode();
/*
        for(int i=1; i<=enc[0]; i++)
        {
            cout<<enc[i];
        }
        cout<<"\n";
 */
    }
    else
    {
        decode();
    }

    return 0;
}

