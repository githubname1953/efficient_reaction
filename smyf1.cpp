// from filament perspective
#include<iostream>
#include<cmath>
#include<random>
#include<vector>
#include<deque>
#include<chrono>
#include<string>
//#include<boost/random.hpp>
#include "pcg_random.hpp"
#include "cbt2.cpp"
using namespace std;

int main()
{
    const double koff=1.0; const double r=370; const double d=45;
	const double v=3500/2.7; const double w=0.004;

    random_device rd; pcg32 pg(rd()); uniform_real_distribution<double> dist(0.0,1.0);
    double t=2*500000000; int inc=1000000; long int times=(long int) t/inc;
    int i,j; double ks, kt; double r1; int i1=0,i2=0,i3; double mean=0; double sig=0;
    const int Nmax = 4000; const int Ninit = 1000; int len;

    int s=1; int N=0; // N is the # of motors on the filament
    deque<int> fil(Ninit);
    for(int i=0; i<Ninit; i++) fil[i]=i;
    cbt graph(Nmax,Ninit);
    graph.init_tree(fil);

    for(j=1;j<=t;j++)
    {
        r1=dist(pg);
        len = fil.size(); N = graph.tree[0][0];
        ks = s*r + (1-s)*koff;
        kt = ks + d + w*len + v*N; //cout<<r1*kt<<endl;

        if(r1<ks/kt)
        {
            i3=0;
            if(s==1)
            {
                graph.insert(fil);
            }

            else s=1;
        }

        else if(r1<(ks+d)/kt)
        {
            i3=1;
            graph.remove(fil);
        }

        else if(r1<(ks + d + w*len)/kt)
        {
            i1 = (int) (r1*kt - ks - d)/w; //cout<<i1<<endl;
            graph.update1(fil[i1],1);
        }

        else
        {
            i1 = (int) (r1*kt - ks - d - w*len)/v; i1++;
            i2 = 0; i3=3;

            graph.transport(i1,s,fil);
            
        }
        
        if(j%inc==0)
		{
			mean += (double) len; sig += (double) len*len; // count++; t1m=mean/count; ts=sig/count;
			cout<<N<<'\t'<<len<<'\t'<<j<<'\n';
		}

        if(len==1 || len == Nmax)
        {
            cout<<"finished at time "<<j<<endl;
            break;
        }
    }

    mean=mean/times; sig=sig/times;
	//cout<<count<<'\t'<<times<<endl;
	cout<<mean<<'\t'<<sig-mean*mean<<endl;

    return 0;
}