#include<iostream>
#include<iomanip>

using namespace std;

int main()
{
    double a=2;//초기값임 교제와 동일
    int repeat=5;//반복 횟수 교제와 동일
    int f_x, f_y;
    for(int i=0; i<=repeat; i++)
    {
        cout <<setw(2)<<i<<"번 반복시 :"<< setprecision(27) << a << endl;
        
        double f_x = a * a + 2;
        double f_prime_x = 2 * a;
        
        a = f_x / f_prime_x;
    }
    return 0;
}