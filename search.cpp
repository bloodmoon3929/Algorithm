#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

bool linear_search(int N, std::vector<int>& S)
{
    for(auto i : S)
    {
        if(i==N)
            return true;
    }
    return false;
}

// bool binary_search(int N, std::vector<int>& S)
// {
//     auto first = S.begin();
//     auto last = S.end();

//     while(true)
//     {
//         auto range_lenth = std::distance(first, last);
//         auto middle_index = (int)std::floor(range_lenth/2);
//         auto middle = *(first + middle_index);

//         if(middle==N)
//             return true;
//         else if(middle>N)
//             std::advance(last, -middle_index);
//         if(middle<N)
//             std::advance(first, middle_index);
        
//         if(range_lenth==1)
//             return false;
//     }
// }
bool binary_search(int N, std::vector<int>& S)
{
    auto first = S.begin();
    auto last = S.end();

    while(true)
    {
        auto range_length = std::distance(first, last);
        auto middle_index = range_length / 2;
        auto middle = *(first + middle_index);

        if(middle == N)
            return true;
        else if(middle > N)
            std::advance(last, -middle_index);
        if(middle < N)
            std::advance(first, middle_index);

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
    std::vector<int> S;
    std::random_device rd;
    std::mt19937 rand(rd());

    std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1,size);

    for(auto i =0; i<size;i++)
        S.push_back(uniform_dist(rand));

    std::sort(S.begin(),S.end());

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    bool search_result=binary_search(N,S);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"이진 검색 수행 시간:"<<diff.count()<<std::endl;

        if(search_result)
            std::cout<<"이진 검색으로 원소를 찾았습니다."<<std::endl;
        else
            std::cout<<"이진 검색으로 원소를 찾지 못했습니다."<<std::endl;

    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    bool search_result1=linear_search(N,S);
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    auto diff1 = std::chrono::duration_cast<std::chrono::microseconds>(end1-begin1);
    std::cout<<"선형 검색 수행 시간:"<<diff1.count()<<std::endl;

        if(search_result1)
            std::cout<<"선형 검색으로 원소를 찾았습니다."<<std::endl;
        else
            std::cout<<"선형 검색으로 원소를 찾지 못했습니다."<<std::endl;
    std::cout<<"-----------------------------------------"<<std::endl;
}

int main()
{
    search_test(100000, 36543);
    search_test(1000000, 36543);
    search_test(10000000, 36543);
    
    return 0;
}