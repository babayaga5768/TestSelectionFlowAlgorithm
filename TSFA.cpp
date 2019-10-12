#include <bits/stdc++.h>
using namespace std;
void calY(map<pair<int,int>,int> x,map<pair<int,int>,double> y,map<pair<int,int>,double> &Y,int N)
{
    Y.clear();
    Y[{2,2}]=y[{2,2}] * pow(y[{1,1}],1-x[{1,1}]) * pow(y[{2,1}],1-x[{2,1}]);
    for(int i=1;i<=N+1;i++)
    {
        Y[{i,1}]= y[{i,1}];
    }
    for(int i=3;i<=N+1;i++)
    {
        Y[{i,2}]=y[{i,2}] * pow(y[{i,1}],1-x[{i,1}]) *pow(Y[{i-1,2}],1-x[{i-1,2}]);
    }
}
void calQ(map<pair<int,int>,int> x,map<pair<int,int>,double> y,map<pair<int,int>,double> &Q,int N)
{
    Q.clear();
    Q[{N+1,2}]=1;
    Q[{N,2}]= 1/y[{N+1,2}];
    for(int i=N-1;i>=2;i--)
    {
        Q[{i,2}]=Q[{i+1,2}]/(y[{i+1,2}] *pow(y[{i+1,1}],x[{i+1,1}]));
    }
    for(int i=1;i<=2;i++)
    {
        Q[{i,1}]=Q[{2,2}]/(y[{2,2}] *pow(y[{1,1}],x[{1,1}]) *pow(y[{2,1}],x[{2,1}]));
    }
    for(int i=3;i<=N;i++)
    {
        Q[{i,1}]=Q[{i,2}]/(y[{i,2}] *pow(y[{i+1,1}],x[{i+1,1}]));
    }
}
void calTeff(map<pair<int,int>,int> x,map<pair<int,int>,double> Y,map<pair<int,int>,double> Q,map<pair<int,int>,double> T,map<pair<int,int>,double> &Teff,int N)
{
    Teff.clear();
    for(int i=1;i<=N;i++)
    {
        Teff[{i,1}]= T[{i,1}] * x[{i,1}] *Q[{i,1}] /Y[{i,1}];
    }
    for(int i=2;i<=N+1;i++)
    {
        Teff[{i,2}]= T[{i,2}] * x[{i,2}] *Q[{i,2}] /Y[{i,2}];
    }
}
void calTau(map<pair<int,int>,double> Teff,double &Tau,int N)
{
    Tau=0;
    for(int i=1;i<=N;i++)
    {
          Tau+=Teff[{i,1}];
    }
    for(int i=2;i<=N+1;i++)
    {
          Tau+=Teff[{i,2}];
    }
}
int main() {
    map<pair<int,int>,double> T;
    map<pair<int,int>,double> y;
    T[{1,1}]=10;
    T[{1,2}]=0;
    T[{2,1}]=10;
    T[{2,2}]=30;
    T[{3,1}]=0;
    T[{3,2}]=70;
    y[{1,1}]=0.70;
    y[{1,2}]=1;
    y[{2,1}]=0.71;
    y[{2,2}]=0.72;
    y[{3,1}]=1;
    y[{3,2}]=0.73;
    int N=2;
    map<pair<int,int>,int> x;
    map<pair<int,int>,double> Y;
    map<pair<int,int>,double> Q;
    map<pair<int,int>,double> Teff;
    double Tau=0;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=2;j++)
        {
            x[{i,j}]=0;
        }
    }
    x[{N+1,2}]=1;
    calY(x,y,Y,N);
    calQ(x,y,Q,N);
    calTeff(x,Y,Q,T,Teff,N);
    calTau(Teff,Tau,N);
    for(int counter=1;counter<=2*N-1;counter++)
    {
        int i1=0,j1=0;
        double Tau1=0;
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=2;j++)
            {
                if(x[{i,j}]==0){
                    x[{i,j}]=1;
                    calY(x,y,Y,N);
                    calQ(x,y,Q,N);
                    calTeff(x,Y,Q,T,Teff,N);
                    calTau(Teff,Tau1,N);
                    //cout<<Tau<<" "<<Tau1<<" "<<i<<j<<endl;
                    if(Tau1<Tau)
                    {
                        Tau=Tau1;
                        i1=i;
                        j1=j;
                    }
                    x[{i,j}]=0;
                    //cout<<Tau<<" "<<Tau1<<" "<<i<<j<<endl;
                }
            }
        }
        x[{i1,j1}]=1;
       // cout<<x[{1,1}]<<x[{2,1}]<<x[{2,2}]<<x[{3,2}]<<endl;
       //cout<<Tau<<endl;
       //cout<<endl;
    }
    cout<<x[{1,1}]<<x[{2,1}]<<x[{2,2}]<<x[{3,2}]<<endl;
    cout<<Tau<<endl;
	return 0;
}