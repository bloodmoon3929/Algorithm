#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int main()
{
    int N,limit;
    cin>>N;
    vector<bool> arr(N+1);
    fill(arr.begin(),arr.end(),true);
    
    limit=sqrt(N);
    for(int i=2; i<limit+1; i++)
    {
        if(arr[i]==true)
        {
            for(int j=i*i; j<N+1; j+=i)
            {
                arr[j]=false;
            }
        }
    }
    for(int i=2; i<N+1; i++)
    {
        if(arr[i]==true)
        {
            cout<<i<<", ";
        }
    }

    return 0;
}