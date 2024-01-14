#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

bool linear_search(int N, vector<int>& S)
{
    for(auto i : S)
    {
        if(i==N)
            return true;
    }
    return false;
}

bool binary_search(int N, vector<int>& S)
{
    auto first = S.begin();
    auto last = S.end();

    while(true)
    {
        auto range_length = distance(first, last);
        auto middle_index = range_length / 2;
        auto middle = *(first + middle_index);

        if(middle == N)
            return true;
        else if(middle > N)
            advance(last, -middle_index);
        if(middle < N)
            advance(first, middle_index);

        if(range_length == 1)
            return false;
    }
}


// void run_small_search_test()
// {
//     auto N=2;
//     std::vector<int> S {1,3,2,4,5,7,9,8,6};
//     std::sort(S.begin(),S.end());
//     if(linear_search(N,S))
//         std::cout<<"선형 검색으로 원소를 찾았습니다."<<std::endl;
//     else
//         std::cout<<"선형 검색으로 원소를 찾지 못했습니다."<<std::endl;
//     if(binary_search(N,S))
//         std::cout<<"이진 검색으로 원소를 찾았습니다."<<std::endl;
//     else
//         std::cout<<"이진 검색으로 원소를 찾지 못했습니다."<<std::endl;
// }

void search_test(int size, int N)
{
    vector<int> S;
    random_device rd;
    mt19937 rand(rd());

    uniform_int_distribution<mt19937::result_type> uniform_dist(1,size);

    for(auto i =0; i<size;i++)
        S.push_back(uniform_dist(rand));

    sort(S.begin(),S.end());

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    bool search_result=binary_search(N,S);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto diff = chrono::duration_cast<chrono::microseconds>(end-begin);
    cout<<"이진 검색 수행 시간:"<<diff.count()<<endl;

        if(search_result)
            cout<<"이진 검색으로 원소를 찾았습니다."<<endl;
        else
            cout<<"이진 검색으로 원소를 찾지 못했습니다."<<endl;

    chrono::steady_clock::time_point begin1 = chrono::steady_clock::now();
    bool search_result1=linear_search(N,S);
    chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
    auto diff1 = chrono::duration_cast<chrono::microseconds>(end1-begin1);
    cout<<"선형 검색 수행 시간:"<<diff1.count()<<endl;

        if(search_result1)
            cout<<"선형 검색으로 원소를 찾았습니다."<<endl;
        else
            cout<<"선형 검색으로 원소를 찾지 못했습니다."<<endl;
    cout<<"-----------------------------------------"<<endl;
}

int main()
{
    search_test(100000, 36543);
    search_test(1000000, 36543);
    search_test(10000000, 36543);
    
    return 0;
}