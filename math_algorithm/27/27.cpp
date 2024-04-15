#include <iostream>
using namespace std;

const int MOD = 1000000007;

long long power(long long x, long long y) 
{
    long long result = 1;
    while (y > 0) 
    {
        if (y % 2 == 1)
            result = (result * x) % MOD;
        x = (x * x) % MOD;
        y /= 2;
    }
    return result;
}

long long combination(int N, int K) 
{
    long long result = 1;
    for (int i = 0; i < K; ++i) 
    {
        result = (result * (N - i)) % MOD;
        result = (result * power(i + 1, MOD - 2)) % MOD;
    }
    return result;
}

int main() {
    int N;
    cin >> N;

    for (int k = 1; k <= N; ++k) 
    {
        long long result = 0;

        for (int m = 1; m <= N; ++m) 
        {
            int M = N - (m - 1) * (k - 1);
            if (M<= 0)
                break;
            long long ways = combination(M, m);
            result = (result + ways) % MOD;
        }

        cout << result << endl;
    }

    return 0;
}