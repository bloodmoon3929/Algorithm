#include<iostream>
#define MOD 1000000007

using namespace std;

int main()
{
    int N,pre=1,cur=1,temp;
    cin>>N;
    for(int i=2; i<N; i++)
    {
        temp=(pre+cur)%MOD;
        pre=cur;
        cur=temp;
    }
    if(N<=2)
        cout<<"1";    
    else
        cout<<temp%MOD;
    return 0;
}