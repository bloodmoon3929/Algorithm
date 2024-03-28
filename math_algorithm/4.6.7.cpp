#include<iostream>
#include<queue>

#define MOD 1000000007

using namespace std;

int main()
{
    long long int N,M,temp=1;
    cin>>N>>M;
    queue<int> binary;
    while(M>0)
    {
        binary.push(M%2);
        M/=2;
    }
    while(!binary.empty())
    {
        int bit =binary.front();
        binary.pop();
        if(bit==1)
        {
            temp*=(N%MOD);
        }
        N*=N;
    }
    cout<<temp%MOD;
    return 0;
}