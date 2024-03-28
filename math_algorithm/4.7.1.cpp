#include <iostream>
#include <vector>
#include<queue>

#define MOD 1000000007

using namespace std;

struct Matrix 
{
    vector<vector<long long int>> data;
};

Matrix multiply(const Matrix& A, const Matrix& B) 
{
    Matrix result;
    result.data.resize((long long int)2, vector<long long int>(2, 0));

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) 
            {
                result.data[i][j] += (A.data[i][k] * B.data[k][j])%MOD;
            }
        }
    }

    return result;
}

int main() 
{
    int N;
    cin >> N;

    Matrix begin;
    begin.data = {{1, 1}, {1, 0}};

    queue<int> binary;
    N--;
    while(N>0)
    {
        binary.push(N%2);
        N/=2;
    }
    Matrix result = begin;
    Matrix temp;
    temp.data={{1,0},{0,1}};
    while(!binary.empty())
    {
        int bit =binary.front();
        binary.pop();
        if(bit==1)
        {
            temp = multiply(temp,result);
        }
        result = multiply(result,result);

    }

    cout << (temp.data[1][0] + temp.data[1][1])%MOD;

    return 0;
}
