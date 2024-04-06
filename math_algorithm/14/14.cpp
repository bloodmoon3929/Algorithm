#include <bits/stdc++.h>

using namespace std;

int arr[5];

int who_is_first(int a, int b, int c);
int who_is_middle(int a, int b, int c);
vector<char> remote(vector<char> unknown, char ch);
int main()
{
    int N, temp;
    
    vector<char> unknown;
    int guess1[10];
    char guess2[5];
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

    temp=who_is_first(unknown[0]-'A',unknown[1]-'A',unknown[2]-'A');  //질문 3. 남은 4개중 3개를 뽑아 1등을 조사
    if(temp==unknown[0]-'A')
    {
        temp=who_is_middle(unknown[0]-'A',unknown[1]-'A',unknown[3]-'A');  //질문 4. 3번의 정답과 이전에 선택하지 않은 항목과 임의의 한개중 중간값을 구함
        if(temp==unknown[0]-'A')
        {
            // 3번에 1등이 중간이라면, 이전에 선택하지 않았던 것이 1등, 3번의 1등이 중간, 나머지가 꼴등일 것임
            guess2[1]=unknown[3];
            guess2[2]=unknown[0];
            guess2[3]='A'+who_is_middle(unknown[1]-'A',unknown[2]-'A',unknown[3]-'A');
            unknown=remote(unknown, guess2[1]);
            unknown=remote(unknown, guess2[2]);
            unknown=remote(unknown, guess2[3]);
            guess2[4]=unknown[0];
            unknown=remote(unknown, guess2[4]);
        }
        else if(temp==unknown[1]-'A')
        {
            guess2[1]=unknown[0];
            unknown=remote(unknown, guess2[1]);
            guess2[3]=temp='A'+who_is_middle(unknown[0]-'A',unknown[1]-'A',unknown[2]-'A');
            if(temp==unknown[2])
            {
                guess2[2]=unknown[0];
                guess2[4]=unknown[1];
            }
            else if(temp==unknown[1])
            {
                guess2[2]=unknown[0];
                guess2[4]=unknown[2];
            }
            else if(temp==unknown[0])
            {
                guess2[2]=unknown[1];
                guess2[4]=unknown[2];
            }
        }
        else if(temp==unknown[3]-'A')
        {
            guess2[1]=unknown[0];
            unknown=remote(unknown, guess2[1]);
            guess2[3]=temp='A'+who_is_middle(unknown[0]-'A',unknown[1]-'A',unknown[2]-'A');
            if(temp==unknown[2])
            {
                guess2[2]=unknown[1];
                guess2[4]=unknown[0];
            }
            else if(temp==unknown[1])
            {
                guess2[2]=unknown[2];
                guess2[4]=unknown[0];
            }
            else if(temp==unknown[0])
            {
                guess2[2]=unknown[2];
                guess2[4]=unknown[1];
            }
        }
    }
    else if(temp==unknown[1]-'A')
    {
        temp=who_is_middle(unknown[0]-'A',unknown[1]-'A',unknown[3]-'A');  //질문 4. 3번의 정답과 이전에 선택하지 않은 항목과 임의의 한개중 중간값을 구함
        if(temp==unknown[1]-'A')
        {
            // 3번에 1등이 중간이라면, 이전에 선택하지 않았던 것이 1등, 3번의 1등이 중간, 나머지가 꼴등일 것임
            guess2[1]=unknown[3];
            guess2[2]=unknown[1];
            guess2[3]='A'+who_is_middle(unknown[0]-'A',unknown[2]-'A',unknown[3]-'A');
            unknown=remote(unknown, guess2[1]);
            unknown=remote(unknown, guess2[2]);
            unknown=remote(unknown, guess2[3]);
            guess2[4]=unknown[0];
            unknown=remote(unknown, guess2[4]);
        }
        else if(temp==unknown[0]-'A')
        {
            guess2[1]=unknown[1];
            unknown=remote(unknown, guess2[1]);
            guess2[3]=temp='A'+who_is_middle(unknown[0]-'A',unknown[1]-'A',unknown[2]-'A');
            if(temp==unknown[2])
            {
                guess2[2]=unknown[0];
                guess2[4]=unknown[1];
            }
            else if(temp==unknown[1])
            {
                guess2[2]=unknown[0];
                guess2[4]=unknown[2];
            }
            else if(temp==unknown[0])
            {
                guess2[2]=unknown[1];
                guess2[4]=unknown[2];
            }
        }
        else if(temp==unknown[3]-'A')
        {
            guess2[1]=unknown[1];
            unknown=remote(unknown, guess2[1]);
            guess2[3]=temp='A'+who_is_middle(unknown[0]-'A',unknown[1]-'A',unknown[2]-'A');
            if(temp==unknown[2])
            {
                guess2[2]=unknown[1];
                guess2[4]=unknown[0];
            }
            else if(temp==unknown[1])
            {
                guess2[2]=unknown[2];
                guess2[4]=unknown[0];
            }
            else if(temp==unknown[0])
            {
                guess2[2]=unknown[2];
                guess2[4]=unknown[1];
            }
        }
    }
    else if(temp==unknown[2]-'A')
    {
        temp=who_is_middle(unknown[1]-'A',unknown[2]-'A',unknown[3]-'A');  //질문 4. 3번의 정답과 이전에 선택하지 않은 항목과 임의의 한개중 중간값을 구함
        if(temp==unknown[2]-'A')
        {
            // 3번에 1등이 중간이라면, 이전에 선택하지 않았던 것이 1등, 3번의 1등이 중간, 나머지가 꼴등일 것임
            guess2[1]=unknown[3];
            guess2[2]=unknown[2];
            guess2[3]='A'+who_is_middle(unknown[0]-'A',unknown[1]-'A',unknown[3]-'A');
            unknown=remote(unknown, guess2[1]);
            unknown=remote(unknown, guess2[2]);
            unknown=remote(unknown, guess2[3]);
            guess2[4]=unknown[0];
            unknown=remote(unknown, guess2[4]);
        }
        else if(temp==unknown[1]-'A')
        {
            guess2[1]=unknown[2];
            unknown=remote(unknown, guess2[1]);
            guess2[3]=temp='A'+who_is_middle(unknown[0]-'A',unknown[1]-'A',unknown[2]-'A');
            if(temp==unknown[2])
            {
                guess2[2]=unknown[0];
                guess2[4]=unknown[1];
            }
            else if(temp==unknown[1])
            {
                guess2[2]=unknown[0];
                guess2[4]=unknown[2];
            }
            else if(temp==unknown[0])
            {
                guess2[2]=unknown[1];
                guess2[4]=unknown[0];
            }
        }
        else if(temp==unknown[3]-'A')
        {
            guess2[1]=unknown[2];
            unknown=remote(unknown, guess2[1]);
            guess2[3]=temp='A'+who_is_middle(unknown[0]-'A',unknown[1]-'A',unknown[2]-'A');
            if(temp==unknown[2])
            {
                guess2[2]=unknown[1];
                guess2[4]=unknown[0];
            }
            else if(temp==unknown[1])
            {
                guess2[2]=unknown[2];
                guess2[4]=unknown[0];
            }
            else if(temp==unknown[0])
            {
                guess2[2]=unknown[2];
                guess2[4]=unknown[1];
            }
        }
    }
    cout<<"입력값 : ";
        for(int i=0; i<5;i++)
            cout<<(char)('A'+arr[i]-1)<<" ";
        cout<<endl;
        cout<<"추론값 : ";
        for(int i=0; i<5;i++)
            cout<<guess2[i]<<" ";
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
    return ((arr[a] > arr[b]) ? ((arr[b] > arr[c]) ? b : ((arr[a] > arr[c]) ? c : a)) : ((arr[a] > arr[c]) ? a : ((arr[b] > arr[c]) ? c : b)));
}

vector<char> remote(vector<char> unknown, char ch)
{
    unknown.erase(remove_if(unknown.begin(), unknown.end(), [ch](char num) {
        return ch == num;
    }), unknown.end());
    return unknown;
}