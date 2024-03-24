#include<iostream>
#include<vector>
#include<climits>

using namespace std;

struct Edge
{
    int src;
    int dst;
    int weight;
};

const int UNKNOWN=INT_MAX;

int main()
{
    int N,M,X,Y;
    vector<vector<Edge>> G(N + 1);
    cin>>N>>M;
    for(int i=0; i<M; i++)
    {
        cin>>X>>Y;
        G[X].push_back({X,Y,0});
        G[Y].push_back({Y,X,0});
    }

    for (int i = 1; i <= N; i++) 
    {
        cout << i << ": "<<endl;
        for (auto& node : G[i]) 
        {
            cout <<"{" <<node.src<<":" <<node.dst<< "}"<<endl;
        }
        cout << endl;
    }
    return 0;
}