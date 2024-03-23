#include<iostream>
#include<vector>

using namespace std;
int main()
{
    int N,Q,X,Y;
    cin>>N>>Q;
    vector<int> sum;
    cin>>X;
    sum.push_back(X);
    for(int i=1; i<N; i++)
    {
        cin>>X;
        sum.push_back(X+sum[i-1]);
    }
    vector<pair<int,int>> input;
    for(int i=0; i<Q; i++)
    {
        cin>>X>>Y;
        input.push_back(make_pair(X-1,Y-1));
    }
    for(int i=0; i<Q; i++)
    {
        if(input[i].first==0)
        {
            cout<<sum[input[i].second]<<endl;
        }
        else
        {
            cout<<sum[input[i].second]-sum[input[i].first-1]<<endl;
        }
        
    }
    return 0;
}