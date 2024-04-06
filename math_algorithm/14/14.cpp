#include <bits/stdc++.h>

using namespace std;

int arr[5];

int who_is_first(int a, int b, int c);
vector<char> remote(vector<char> unknown, char ch);
int main()
{
    int N, temp;
    
    vector<char> unknown;
    int guess1[10];
    char guess2[10];
    //A~E의 순위를 입력
    for(int i=0; i<5; i++)
        cin>>arr[i];
    
    //1번 4번 이내의 질문으로는 모든 사람의 순위를 알 수 있는 지의 여부


    //2번 5번의 질문을 했을 때, 모든 사람의 순위를 맞히는 방법을 구성
    for(int i=0; i<5; i++)
        unknown.push_back('A'+i);
    temp=who_is_first(0,1,2);               //질문 1. A,B,C중 가장 빠른 선수를 temp변수에 저장
    guess2[0]='A'+who_is_first(temp,3,4);   //질문 2. temp,D,E중 가장 빠른 선수가 1등이기에 guess[0]에 저장
    unknown=remote(unknown, guess2[0]);     //1등은 찾았기에 1등을 unknown에서 제거

    temp=who_is_first('A'-unknown[0],'A'-unknown[1],'A'-unknown[2]);
    if(temp==0)
    {
        who_is_middle('A'-unknown[0],'A'-unknown[1],'A'-unknown[3]);
    }
    else if(temp==1)
    {
        who_is_middle('A'-unknown[1],'A'-unknown[2],'A'-unknown[3]);
    }
    else
    {
        who_is_middle('A'-unknown[1],'A'-unknown[2],'A'-unknown[3]);
    }


    return 0;
}

/*
    ((arr[0]>arr[1])?arr[1]:arr[0])>arr[2]?arr[2]:((arr[0]>arr[1])?arr[1]:arr[0])
    삼항 연산자를 활용한, 셋 중 가장 빠른 선수 찾는 코드
*/ 
int who_is_first(int a, int b, int c)
{
    return ((arr[a]>arr[b])?b:a)>arr[c]?c:((a>b)?b:a);
}
int who_is_middle(int a, int b, int c)
{
    return ((arr[a]>arr[b])?b:a)>arr[c]?((a>b)?b:a):c;
}
vector<char> remote(vector<char> unknown, char ch)
{
    unknown.erase(remove_if(unknown.begin(), unknown.end(), [ch](char num) {
        return ch == num;
    }), unknown.end());
    return unknown;
}