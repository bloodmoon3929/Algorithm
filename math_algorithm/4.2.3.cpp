#include<iostream>
#include<vector>

using namespace std;
int main()
{
    int N,Q,X,Y,Z;
    cin>>N>>Q;
    vector<int> sum(N+2);
    for(int i=0; i<Q; i++)
    {
        cin>>X>>Y>>Z;
        sum[X]+=Z;
        sum[Y+1]-=Z;
    }
    for(int i=2; i<N+1; i++)
    {
        if(sum[i]>0)
        {
            cout<<"<";
        }
        else if(sum[i]==0)
        {
            cout<<"=";
        }
        else if(sum[i]<0)
        {
            cout<<">";
        }
    }
    return 0;
}