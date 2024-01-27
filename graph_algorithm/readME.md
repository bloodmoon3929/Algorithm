# 그래프 알고리즘<br>

1. [벨만-포드 알고리즘](#1-벨만-포드-알고리즘)
2. [존슨 알고리즘](#2-존슨-알고리즘)
3. [코사라주 알고리즘](#3-코사라주-알고리즘)

## 1. 벨만-포드 알고리즘

### 벨만-포드(Bellman-ford) 알고리즘이란


### 다익스트라와의 차이점


### 벨만-포드 알고리즘의 구현

```cpp
#include<iostream>
#include<vector>
#include<climits>

using namespace std;

struct Edge
{
    int  src;
    int dst;
    int weight;
};

const int UNKNOWN=INT_MAX;

vector<int> BellmanFord(vector<Edge> edges, int V, int start)
{
    vector<int> distance(V, UNKNOWN);
    distance[start]=0;

    for(int i=0; i<V-1; i++)
    {
        for(auto& e : edges)
        {
            if(distance[e.src]==UNKNOWN)
                continue;
            if(distance[e.dst]>distance[e.src]+e.weight)
            {
                distance[e.dst]=distance[e.src]+e.weight;
            }
        }  
    }
    return distance;
}

int main()
{
    int V=5;
    vector<Edge> edges;
    vector<vector<int>> edge_map {{0,1,3},{1,2,5},{1,3,10},{3,2,-7},{2,4,2}};
    for(auto& e:edge_map)
        edges.emplace_back(Edge {e[0],e[1],e[2]});
    int start =0;
    vector<int> distance = BellmanFord(edges,V,start);

    cout<<"["<<start<<"번 정점으로 부터 최소거리"<<"]"<<endl;

    for(int i =0; i<distance.size(); i++)
    {
        if(distance[i]==UNKNOWN)
            cout<<i<<"번 정점 : 방문하지 않음!"<<endl;
        else
            cout<<i<<"번 정점 : "<<distance[i]<<endl;
    }
}
```

실행 결과
![image](https://github.com/cdmh/mapreduce/assets/144004857/21bbda79-7435-43c1-b62f-9fc060a77aa3)


```cpp
#include<iostream>
#include<vector>
#include<climits>

using namespace std;

struct Edge
{
    int  src;
    int dst;
    int weight;
};

const int UNKNOWN=INT_MAX;

vector<int> BellmanFord(vector<Edge> edges, int V, int start)
{
    vector<int> distance(V, UNKNOWN);
    distance[start]=0;

    for(int i=0; i<V-1; i++)
    {
        for(auto& e : edges)
        {
            if(distance[e.src]==UNKNOWN)
                continue;
            if(distance[e.dst]>distance[e.src]+e.weight)
            {
                cout<<"음수 가중치 사이클 발견!"<<endl;
                return {};
            }
        }  
    }
    return distance;
}



int main()
{
    int V=6;
    vector<Edge> edges;
    vector<vector<int>> edge_map {{0,1,3},{1,3,-8},{2,1,3},{2,5,5},{3,2,3},{2,4,2},{4,5,-1},{5,1,8}};
    for(auto& e:edge_map)
        edges.emplace_back(Edge {e[0],e[1],e[2]});
    int start =0;
    vector<int> distance = BellmanFord(edges,V,start);

    if(!distance.empty())
    {
        cout<<"["<<start<<"번 정점으로 부터 최소거리"<<"]"<<endl;

        for(int i =0; i<distance.size(); i++)
        {
            if(distance[i]==UNKNOWN)
                cout<<i<<"번 정점 : 방문하지 않음!"<<endl;
            else
                cout<<i<<"번 정점 : "<<distance[i]<<endl;
        }
    }
}
```
실행 결과
![image](https://github.com/bloodmoon3929/Algorithm/assets/144004857/4cc9e26f-46f1-49c2-8b56-492f0b65caca)

## 2. 존슨 알고리즘

### 존슨 알고리즘이란


### 존슨 알고리즘의 구현

```cpp
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

const int UNKNOWN = INT_MAX;

bool HasNegativeCycle(const vector<Edge>& edges, vector<int> distance)
{
    for(auto& e : edges)
    {
        if(distance[e.src]==UNKNOWN)
            continue;
        if(distance[e.src]+e.weight<distance[e.dst])
            return true;
    }
    return false;
}

vector<int> BellmanFord(vector<Edge> edges, int V)
{
    vector<int> distance(V+1, UNKNOWN);

    int s=V;
    for(int i=0; i<V;i++)
    {
        edges.push_back(Edge{s,i,0});
    }
    distance[s]=0;

    for(int i=0; i<V; i++)
    {
        for(auto& e : edges)
        {
            if(distance[e.src]==UNKNOWN)
                continue;
            if(distance[e.dst]>distance[e.src]+e.weight)
            {
                distance[e.dst]=distance[e.src]+e.weight;
            }
        }
    }
    if(HasNegativeCycle(edges,distance))
    {
        cout<<"음수 가중치 사이클 발견!"<<endl;
        return {};
    }
    return distance;
}
    
int GetMinDistance(vector<int>& distance, vector<bool>& visited)
{
    int minDistance = UNKNOWN;
    int minIndex = -1;

    for(int i=0; i<distance.size(); i++)
    {
        if(!visited[i]&&distance[i]<=minDistance)
        {
            minDistance=distance[i];
            minIndex=i;
        }
    }
    return minIndex;
} 


vector<int> Dijkstra(vector<Edge> edges, int V, int start)
{
    vector<int> distance(V,UNKNOWN);
    vector<bool> visited(V, false);
     
    distance[start]=0;

    for(int i=0; i<V-1; i++)
    {
        int curr= GetMinDistance(distance, visited);
            
        visited[curr]=true;
        for(auto& e :edges)
        {
            if(e.src !=curr)
                continue;
            if(visited[e.dst])
                continue;
            if(distance[curr]!=UNKNOWN&&distance[e.dst]>distance[curr]+e.weight)
                distance[e.dst]=distance[curr]+e.weight;
        }
    }
    return distance;
}

void Johnson(vector<Edge> edges, int V)
{
    vector<int> h=BellmanFord(edges, V);
    if(h.empty())
        return;
    for(auto& e : edges)
    {
        e.weight+=(h[e.src]-h[e.dst]);
    }
    vector<vector<int>> shortest(V);
    for(int i=0; i<V; i++)
    {
        shortest[i]=Dijkstra(edges, V, i);
    }
    for(int i=0; i<V; i++)
    {
        cout<<i<<":\n";

        for(int j=0; j<V; j++)
        {
            if(shortest[i][j]!=UNKNOWN)
            {
                shortest[i][j] +=h[i]-h[j];
                cout<<"\t"<<j<<":"<<shortest[i][j]<<endl;
            }
        }
    }
}

int main()
{
    int V=5;
    vector<Edge> edges;

    vector<vector<int>> edge_map{{0,1,-7},{1,2,-2},{2,0,10},{0,3,-5},{0,4,2},{3,4,4}};

    for(auto& e : edge_map)
    {
        edges.emplace_back(Edge {e[0],e[1],e[2]});
    }
    Johnson(edges, V);
}
```

## 3. 코사라주 알고리즘


### 강한 연결 요소


### 코사라주 알고리즘이란


### 코사라주 알고리즘의 구현

```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void FillStack(int node, vector<bool>& visited, vector<vector<int>>& adj, stack<int>& stack)
{
    visited[node]=true;

    for(auto next : adj[node])
    {
        if(!visited[next])
        {
            FillStack(next, visited, adj, stack);
        }
    }
    stack.push(node);
}

vector<vector<int>> Transpose(int V, vector<vector<int>> adj)
{
    vector<vector<int>> transpose(V);

    for(int i=0; i<V; i++)
    {
        for(auto next :adj[i])
        {
            transpose[next].push_back(i);
        }
    }
    return transpose;
}

void CollectConnectedComponents(int node, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& component)
{
    visited[node]=true;
    component.push_back(node);

    for(auto next : adj[node])
    {
        if(!visited[next])
        {
            CollectConnectedComponents(next, visited, adj, component);
        }
    }
}

vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj)
{
    vector<bool> visited(V, false);
    stack<int> stack;

    for(int i=0; i<V; i++)
    {
        if(!visited[i])
        {
            FillStack(i, visited, adj, stack);
        }
    }
    vector<vector<int>> transpose = Transpose(V, adj);
    fill(visited.begin(), visited.end(),false);
    vector<vector<int>> connectedComponents;

    while(!stack.empty())
    {
        int node= stack.top();
        stack.pop();

        if(!visited[node])
        {
            vector<int> component;

            CollectConnectedComponents(node, visited, transpose, component);
            connectedComponents.push_back(component);
        }
    }
    return connectedComponents;
}

int main()
{
    int V=9;
    vector<vector<int>> adj={{1,3},{2,4},{3,5},{7},{2},{4,6},{7,2},{8},{3}};

    vector<vector<int>> connectedComponents = Kosaraju(V, adj);
    cout<<"강한 연결 요소 개수 : "<<connectedComponents.size()<<endl;
    for(int i=0; i < connectedComponents.size(); i++)
    {
        cout<<"["<<i+1<<"]";
        for(auto node : connectedComponents[i])
            cout<<node<<" ";
        cout<<endl;
    }
}
```






![벨만포워드](https://github.com/bloodmoon3929/Algorithm/assets/144004857/dd26e25d-b39a-4575-833d-c7f5984fbb55)

0번 정점을 기준으로 다익스트라 알고리즘의 최단 경로는 다음과 같습니다.

|0|-|-|0|가중치|
|-|-|-|-|:-:|
|0|-|-|1|3|
|0|-|1|2|8|
|0|-|1|3|13|
|0|1|2|4|10|

0번 정점을 기준으로 벨만 포워드 알고리즘의 최단 경로는 다음과 같습니다.

|0|-|-|-|0|가중치|
|-|-|-|-|-|:-:|
|0|-|-|-|1|3|
|0|-|1|3|2|6|
|0|-|1|2|3|1|
|0|1|3|2|4|8|
