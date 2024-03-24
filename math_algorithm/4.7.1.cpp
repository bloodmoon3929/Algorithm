#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Matrix 
{
    vector<vector<int>> data;
};

Matrix multiply(const Matrix& A, const Matrix& B) {

    
    Matrix result;
    result.data.resize(2, vector<int>(2, 0));

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                result.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }

    return result;
}

Matrix matrixPower(const Matrix& mat, int power) {
    if (power == 0) {
        Matrix result;
        int size = mat.data.size();
        result.data.resize(size, vector<int>(size, 0));
        for (int i = 0; i < size; ++i) {
            result.data[i][i] = 1;
        }
        return result;
    } else if (power == 1) {
        return mat;
    } else {
        Matrix result = matrixPower(mat, power / 2);
        result = multiply(result, result);
        if (power % 2 == 1) {
            result = multiply(result, mat);
        }
        return result;
    }
}
int main() 
{
    int N;
    Matrix begin;
    stack<int> binary;
    stack<Matrix> stack;
    begin.data = {{1, 1}, {1, 0}};
    cin>>N;
    while (N > 0) {
        binary.push(N % 2);
        N /= 2;
    }
    while(!binary.empty())
    {
        stack.push(matrixPower(begin,binary.top()));
        binary.pop();
    }
    Matrix curr=stack.top();
    stack.pop();
    while(!stack.empty())
    {
        curr=multiply(curr,stack.top());
        stack.pop();
    }

    cout<<curr.data[1][0]+curr.data[1][1];

    return 0;
}
