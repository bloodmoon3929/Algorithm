#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

int main()
{
    int arr[2][3];
    int pattern=2;
    int vecter[2][4];
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<2; j++)
        {
            cin>>arr[j][i];
        }
    }
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<2; j++)
        {
            vecter[j][i]=arr[j][i]-arr[j][i+1];
        }
    }
    vecter[0][0]=arr[0][0]-arr[0][1];
    vecter[1][0]=arr[1][0]-arr[1][1];

    vecter[0][1]=arr[0][2]-arr[0][1];
    vecter[1][1]=arr[1][2]-arr[1][1];

    vecter[0][2]=arr[0][0]-arr[0][2];
    vecter[1][2]=arr[1][0]-arr[1][2];
    
    vecter[0][3]=arr[0][1]-arr[0][2];
    vecter[1][3]=arr[1][1]-arr[1][2];

    if(vecter[0][0]*vecter[0][1]+vecter[1][0]*vecter[1][1]<0)
        pattern=1;
    else if(vecter[0][2]*vecter[0][3]+vecter[1][2]*vecter[1][3]<0)
        pattern=3;

    if(pattern==1)
        cout<<std::setprecision(13)<<sqrt(pow(vecter[0][0],2)+pow(vecter[1][0],2));
    else if(pattern==2)
    {
       cout<<std::setprecision(13)<<abs(vecter[0][0]*vecter[1][1]-vecter[1][0]*vecter[0][1])/sqrt(pow(vecter[0][1],2)+pow(vecter[1][1],2));
    }
    else if(pattern==3)
        cout<<std::setprecision(13)<<sqrt(pow(vecter[0][2],2)+pow(vecter[1][2],2));
    return 0;
}