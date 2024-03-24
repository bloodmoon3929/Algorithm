#include <iostream>
#include <vector>
#include <stack>
#include<queue>
#include<cmath>

using namespace std;

struct Matrix 
{
    vector<vector<int>> data;
};

Matrix multiply(const Matrix& A, const Matrix& B) 
{
    Matrix result;
    result.data.resize(2, vector<int>(2, 0));

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) 
            {
                result.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }

    return result;
}

Matrix matrixPower(const Matrix& mat, int power)
{
    if (power == 0) 
    {
        Matrix result;
        result.data.resize(2, vector<int>(2, 0));
        for (int i = 0; i < 2; ++i) 
        {
            result.data[i][i] = 1;
        }
        return result;
    } 
    else if (power == 1) 
    {
        return mat;
    } 
    else 
    {
        Matrix result = matrixPower(mat, power / 2);
        result = multiply(result, result);
        if (power % 2 == 1) 
        {
            result = multiply(result, mat);
        }
        return result;
    }
}
int main() 
{
    int N;
    cin >> N;

    Matrix begin;
    begin.data = {{1, 1}, {1, 0}};

    vector<int> powers;
    int temp = N-2;
    while (temp > 0) 
    {
        int power = 1;
        while (power * 2 <= temp) 
        {
            power *= 2;
        }
        powers.push_back(power);
        temp -= power;
    }

    Matrix result = begin;
    for (int power : powers) 
    {
        result = multiply(result, matrixPower(begin, power));
    }

    cout << result.data[1][0] + result.data[1][1];

    return 0;
}
