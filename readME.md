# 분할정복 심화<br>

1. [이진 검색](#1-이진-검색)
2. [분할 정복의 이해](#2-분할-정복-이해)
3. [분할 정복 정렬 알고리즘](#3-분할-정복을-이용한-정렬-알고리즘)
4. [분할 정복 기법과 C++ 표준 라이브러리 함수](#4분할-정복-기법과-c-표준-라이브러리-함수)
5. [맵리듀스](#5맵리듀스)
<br><br>
## 1. 이진 검색
배열이나 문서를 검색할 때 두 가지 접근 방법이 존재하는데 이는 다음과 같습니다.<br>
1. [선형 검색(linear search)](#선형-검색)
2. [이진 검색(binary search)](#이진-검색)
   


### 선형 검색<br>
선형 검색의 경우 정렬되어 있지 않더라도 문제없이 작동합니다. 하지만 이는 정렬되어
있다는 이점을 살리지 못한 검색 방법이며, 효율적이지 않습니다.<br><br>

```cpp
bool linear_search(int N, std::vector<int>& sequence)
{
    for(auto i : sequence)
    {
        if(i==N)
            return true;
    }
    return false;
}
```
<br>
해당 코드는 N이라는 원소가 시퀀스에 포함되어 있는지 여부를 판단하는 코드입니다.<br>
선형 검색은 시쿼스의 시작원소 부터 마지막 원소까지 순차적으로 입력된 원소 N과 비교하여 같은지 여부를 판단합니다. 이 경우 시작 복잡도는 O(N)입니다.
<br><br>

### 이진 검색<br>
이진 검색은 정렬된 시퀀스에서만 사용할 수 있지만, 시간 복잡도는 선형 검색보다 효율적입니다.<br><br>

이진 검색의 알고리즘은 다음과 같습니다.
1. 시퀀스의 범위를 측정합니다.
2. 시퀀스의 가운데 원소와 찾고자하는 값을 비교합니다. (만일 두 원소가 같다면 true를 반환)
3. 가운데 원소와 찾고자 하는 값을 비교하여
   * 가운데 원소보다 값이 작다면, 가운데 원소부터 그 이상의 원소를 제거합니다.
   * 반대로 작다면, 가운데 원소부터 그 이하의 원소를 제거합니다.
4. 범위를 다시 측정하여 측정한 범위가 1 초과이면 2번쨰 과정을 반복합니다.(만일 이 과정을 수행할 수 없다면, 시퀀스에는 찾고자한 원소가 존재하지 않는 것이기에 false를 반환합니다.)<br>
   
다음은 이진 검색의 C++ 코드입니다.
```cpp
bool binary_search(int N, std::vector<int>& S)
{
    auto first = S.begin();
    auto last = S.end();

    while(true)
    {
        auto lenth = std::distance(first, last);
        auto middle_index = first+std::floor(lenth/2);
        auto middle = *(middle_index);

        if(middle==N)
            return true;
        if(middle>N)
            std::advance(last, middle_index);
        else
            std::advance(first, middle_index);
        
        if(lenth==1)
            return false;
    }
}
```
<br>
이제 두가지 경우의 소모 시간을 비교해보겠습니다.

```cpp
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
```

![result1](https://github.com/bloodmoon3929/KTC2024/assets/144004857/666a87e0-7cdc-444b-beec-aca6e591eaf2)
<br>
결과를 보면 알수 있듯, 이진 검색의 수행시간은 0에 수렴하지만, 선형 검색의 경우 범위가 늘어남에 따라서 시간도 비례해서 늘어나는 모습을 볼 수 있다.

`std::sort`<br>
C++ 표준 라이브러리에서 제공하는 정렬 알고리즘이며, 임의 접근 반복자의 범위내의 요소들을 정렬합니다. 기본적으로는 올림차순이나 원한다면 내림차순도 가능합니다.
<br><br>
함수의 기본형은 다음과 같습니다.
```cpp
template<class RandomIt>
void sort(RandomIt first, RandomIt last);

template<class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp);
```
여기서 comp는 비교함수이고, 그 값에 따라 오름차순과 내림차순으로 나눠집니다. 간단한 예제를 보겠습니다.

```cpp
std::sort(numbers.begin(), numbers.end(), [](int a, int b) {return a > b;});
```
이 경우 비교함수의 첫 번째 인자가 두 번째 인자보다 크기에 sort함수의 3번째 전달인자 값이 true가 되어 내림차순이 됩니다. 하지만 직접적으로 true 값을 전달인자 값으로 주어서는 안됩니다.

`#include <chrono>`<br>
이 헤더파일은 시간을 다루기 위해 사용하는 헤더파일입니다. 포함되어 있는 클래스는 다음과 같습니다.
```cpp
std::chrono::duration

```



`#include <random>`<br>
<br>

`#include <algorithm>`<br>

## 2. 분할 정복 이해
분할 정복 접근방법은 크게 3단계로 나눌수 있습니다.<br>
1. 분할 : 주어진 문제를 모두 동일하게 해결할 수 있는 세부 문제로 나눕니다.
2. 정복 : 나누어진 세부 문제들의 해답을 구합니다.
3. 결합 : 해답이 구해진 세부 문제들을 결합하여 전체문제의 해답을 구합니다.

## 3. 분할 정복을 이용한 정렬 알고리즘
정렬 알고리즘 구현에 있어 필요한 3가지 요구사항이 있습니다.<br>
1. 모든 데이터 타입에 대해 동작해야 합니다.
2. 많은 양의 데이터를 처리할 수 있어야 합니다.
3. 점근적 시작 복잡도 측면이나 실제 동작시 빨라야 합니다.

이 책에서는 크게 3가지 정렬 알고리즘이 소개되었습니다.
1. [병합 정렬](#1-병합-정렬)
2. [퀵 정렬](#2-퀵-정렬)
3. [선형 시간 선택](#3-선형-시간-선택)

### 1. 병합 정렬
병합 정렬은 전체 집합을 하나의 원소만을 가질때까지 계속하여 부분 집합으로 나눈뒤 올림차순 혹은 내림차순인 상태를 유지하며 합치는 방식입니다.
<br><br>
다음은 병합 정렬의 코드입니다.
```cpp
#include <iostream>
#include <vector>

template<typename T>
std::vector<T> merge(std::vector<T>& arr1, std::vector<T>& arr2)
{
	std::vector<T> merged;

	auto iter1 = arr1.begin();
	auto iter2 = arr2.begin();

	while (iter1 != arr1.end()&&iter2 != arr2.end())
	{
		if (*iter1 < *iter2)
		{
			merged.emplace_back(*iter1);
			iter1++;
		}
		else
		{
			merged.emplace_back(*iter2);
			iter2++;
		}

	}
	if (iter1 != arr1.end())
	{
		for (; iter1 != arr1.end(); iter1++)
			merged.emplace_back(*iter1);
	}
	else
	{
		for (; iter2 != arr2.end(); iter2++)
			merged.emplace_back(*iter2);
	}
	return merged;
}

template<typename T>
std::vector<T> merge_sort(std::vector<T> arr)
{
	if (arr.size() > 1)
	{
		auto mid = size_t(arr.size() / 2);
		auto left_half = merge_sort<T>(std::vector<T>(arr.begin(), arr.begin() + mid));
		auto right_half = merge_sort<T>(std::vector<T>(arr.begin() + mid, arr.end()));

		return merge<T>(left_half, right_half);
	}
	return arr;
}

template<typename T>
void print_vector(std::vector<T> arr)
{
	for (auto i : arr)
		std::cout << i << " ";
	std::cout << std::endl;
}

void run_merge_sort_test()
{
	std::vector<int>	S1{ 45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7 };
	std::vector<float>	S2{ 45.6f, 1.0f, 3.8f, 1.01f, 2.2f, 3.9f, 45.3f, 5.5f, 1.0f, 2.0f, 44.0f, 5.0f, 7.0f };
	std::vector<double>	S3{ 45.6, 1.0, 3.8, 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0 };
	std::vector<char>	S4{ 'b', 'z', 'a', 'e', 'f', 't', 'q', 'u', 'y'};

	std::cout << "정렬되지 않은 입력 벡터:" << std::endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(S4);
	std::cout << std::endl;

	auto sorted_S1 = merge_sort<int>(S1);
	auto sorted_S2 = merge_sort<float>(S2);
	auto sorted_S3 = merge_sort<double>(S3);
	auto sorted_S4 = merge_sort<char>(S4);

	std::cout << "병렬 정합에 의해 정렬된 벡터:" << std::endl;
	print_vector<int>(sorted_S1);
	print_vector<float>(sorted_S2);
	print_vector<double>(sorted_S3);
	print_vector<char>(sorted_S4);
	std::cout << std::endl;
}

int main()
{
	run_merge_sort_test();
	return 0;
}
```
각각의 함수에 대한 간단한 설명을 하겠습니다.<br>
`1. std::vector<T> merge(std::vector<T>& arr1, std::vector<T>& arr2)`<br>
해당 함수는 우선 전달인자로 두 배열을 받습니다. 그 후 다음의 절차를 진행합니다.
1. 배열의 첫 원소 값을 비교하여 원소의 값이 작은 것을 merge 배열에 추가합니다.
2. 1번 과정을 두 배열중 하나의 배열의 모든 원소 값을 merge배열에 추가할때까지 반복합니다.
3. 만일 두 배열중 하나의 배열의 모든 원소값이 merge배열에 추가 되었다면 나머지 배열을 merge배열에 추가합니다.


그 후 함수의 반환형인 vector함수의 형태로 merge배열을 반환합니다.<br><br>
`2. std::vector<T> merge_sort(std::vector<T> arr)`<br>
해당 함수는 배열의 원소가 1개를 가질때까지 배열의 가운데를 기준으로 쪼개서 배열이 한 개의 원소만을 가질때까지 분해한 후, 부분 집합들을 merge함수를 통해 정렬상태를 유지한 상태로 병합합니다.<br><br>
`3. void print_vector(std::vector<T> arr)`<br>
해당 함수는 배열의 시작 원소부터 마지막 원소까지 순서대로 출력하는 함수입니다.<br><br>
`4. void run_merge_sort_test()`<br>
해당 함수는 여러 정렬 알고리즘의 필수 3요소 중 모든 타입에 대해 동작하는지 알아보기 위해, 다양한 타입의 vector 배열을 merge_sort 함수를 사용해서 정렬하는 것을 시연하기 위해 만들어진 함수입니다.<br><br>
# 이해를 돕기 위한 예시를 보겠습니다.<br>


|45| 1| 3| 1| 2| 3|45| 5| 1| 2|44| 5| 7|
|--|--|--|--|--|--|--|--|--|--|--|--|--|

## 해당 배열은 13개의 원소로 이뤄져 있기에 가운데 원소인 45를 기준으로 나눕니다.

|45| 1| 3| 1| 2| 3|/|45| 5| 1| 2|44| 5| 7|
|--|--|--|--|--|--|-|--|--|--|--|--|--|--|


## 나누어진 배열은 원소를 하나만 가질때 까지 반복합니다.

|45| 1| 3|/| 1| 2| 3|/|45| 5| 1|/| 2|44| 5| 7|
|--|--|--|-|--|--|--|-|--|--|--|-|--|--|--|--|
 ***
|45|/| 1| 3|/| 1|/| 2| 3|/|45|/| 5| 1|/| 2|44|/| 5| 7|
|--|-|--|--|-|--|-|--|--|-|--|-|--|--|-|--|--|-|--|--|
***
|45|/| 1|/| 3|/| 1|/| 2|/| 3|/|45|/| 5|/| 1|/| 2|/|44|/| 5|/| 7|
|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|
## 그 후 분해한 역순으로 부분 집합을 병합하는 데, 정렬된 상태를 유지해야 합니다. (순서가 바꾼 부분은 빨간색)
|45|/| 1| 3|/| 1|/| 2| 3|/|45|/|<span style="color:red"> 1</span>|<span style="color:red"> 5</span>|/| 2|44|/| 5| 7|
|--|-|--|--|-|--|-|--|--|-|--|-|--|--|-|--|--|-|--|--|
***
| <span style="color:red">1</span>| <span style="color:red">3</span>|<span style="color:red">45</span>|/| 1| 2| 3|/|<span style="color:red"> 1</span>| <span style="color:red">5</span>|<span style="color:red">45</span>|/|<span style="color:red"> 2</span>|<span style="color:red"> 5</span>|<span style="color:red"> 7</span>|<span style="color:red">44</span>|
|--|--|--|-|--|--|--|-|--|--|--|-|--|--|--|--|
***
| <span style="color:red">1</span>| <span style="color:red">1</span>| <span style="color:red">2</span>| <span style="color:red">3</span>| <span style="color:red">4</span>|<span style="color:red">45</span>|/| <span style="color:red">1</span>| <span style="color:red">2</span>| <span style="color:red">5</span>| <span style="color:red">5</span>| <span style="color:red">7</span>|<span style="color:red">44</span>|<span style="color:red">45</span>|
|--|--|--|--|--|--|-|--|--|--|--|--|--|--|
***
| <span style="color:red">1</span>|<span style="color:red"> 1</span>|<span style="color:red"> 1</span>|<span style="color:red"> 2</span>|<span style="color:red"> 2</span>|<span style="color:red"> 3</span>|<span style="color:red"> 3</span>|<span style="color:red"> 5</span>|<span style="color:red"> 5</span>|<span style="color:red"> 7</span>|<span style="color:red">44</span>|<span style="color:red">45</span>|<span style="color:red">45</span>|
|--|--|--|--|--|--|--|--|--|--|--|--|--|
***
이 배열을 브루트 포스로 풀게 된다면, 시간 복잡도는 $n^2$이지만, 병합 정렬로 풀게 된다면 시간 복잡도는 $nlogn$이 될 것이다.

### 2. 퀵 정렬
퀵 정렬은 임의의 원소를 피벗으로 하여, 피벗과 비교하여 작은 값이 모인 집합과 큰 값이 모인 집합 두개로 나눕니다. 그 후 만들어진 두 집합 역시 동일한 과정을 거쳐 원소를 하나만 가질때까지 반복합니다.
<br><br>
다음은 퀵 정렬의 코드입니다.
```cpp
#include <iostream>
#include <vector>

template<typename T>
auto partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    auto pivot_val=*begin;
    auto left_iter=begin+1;
    auto right_iter=end;
    while (true)
    {
        while (*left_iter<=pivot_val&&std::distance(left_iter, right_iter)>0)
           left_iter++;
        while (*right_iter>pivot_val&&std::distance(left_iter, right_iter)>0)
           right_iter--;
        if(right_iter==left_iter)
            break;
        else
            std::iter_swap(left_iter, right_iter);
        
    }
    if(pivot_val>*right_iter)
        std::iter_swap(begin, right_iter);

    return right_iter;
}

template<typename T>
void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    if(std::distance(begin, end)>=1)
    {
        auto partition_iter = partition<T>(begin, end);
        quick_sort<T>(begin, partition_iter-1);
        quick_sort<T>(partition_iter,end);
    }
}

template<typename T>
void print_vector(std::vector<T> arr)
{
	for (auto i : arr)
		std::cout << i << " ";
	std::cout << std::endl;
}

void run_quick_sort_test()
{
	std::vector<int>	S1{ 45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7 };
	std::vector<float>	S2{ 45.6f, 1.0f, 3.8f, 1.01f, 2.2f, 3.9f, 45.3f, 5.5f, 1.0f, 2.0f, 44.0f, 5.0f, 7.0f };
	std::vector<double>	S3{ 45.6, 1.0, 3.8, 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0 };
	std::vector<char>	S4{ 'b', 'z', 'a', 'e', 'f', 't', 'q', 'u', 'y'};

	std::cout << "정렬되지 않은 입력 벡터:" << std::endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(S4);
	std::cout << std::endl;

	quick_sort<int>(S1.begin(),S1.end()-1);
	quick_sort<float>(S2.begin(),S2.end()-1);
	quick_sort<double>(S3.begin(),S3.end()-1);
	quick_sort<char>(S4.begin(),S4.end()-1);

	std::cout << "퀵 정합에 의해 정렬된 벡터:" << std::endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(S4);
	std::cout << std::endl;
}

int main()
{
	run_quick_sort_test();
	return 0;
}
```
각각의 함수에 대한 간단한 설명을 하겠습니다.<br>
`1. auto partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)`<br>
해당 함수는 전달인자로 배열의 시작 주소와 마지막 주소를 받습니다. 그 후 첫 번째 주소에 저장된 원소를 피벗으로 두고, 피벗을 기준으로 작은 값은 왼쪽, 큰 값은 오른쪽에 배치하고 반환 값으로는 피벗보다 큰 원소의 주소를 반환합니다.
<br>

`2. void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)`<br>
해당 함수는 partition함수를 사용하여 얻은 원소를 기준으로 배열을 두개로 나누는 과정을 배열의 원소가 하나가 될 때까지 반복합니다.
<br>

# 이해를 돕기 위해 예시를 보겠습니다.<br>
|45| 1| 3| 1| 2| 3|45| 5| 1| 2|44| 5| 7|
|--|--|--|--|--|--|--|--|--|--|--|--|--|
## 퀵 정렬은 임의의 원소값을 기준으로 나누지만 해당 코드에서는 첫 번째 원소를 기준으로 배열을 분리 했기에 그를 따르도록 하겠습니다.(피벗은 파랑색)
|<span style="color:blue"> 1</span>| 3| 1| 2| 3|45| 5| 1| 2|44| 5| 7|/|<span style="color:blue">45</span>|
|--|--|--|--|--|--|--|--|--|--|--|--|-|--|
***
|<span style="color:blue"> 1</span>|/| 1| 1|/| <span style="color:blue">3</span>| 2| 3|45| 5| 2|44| 5| 7|/|45|
|--|-|--|-|--|--|--|--|--|--|--|--|--|--|-|--|
***
| 1|/|<span style="color:blue"> 1</span>|/| 1|/| 2| 3| 2|<span style="color:blue"> 3</span>|/|<span style="color:blue">45</span>| 5|44| 5| 7|/|45|
|--|-|--|-|--|-|--|--|--|--|--|-|--|--|--|--|-|--|
***
| 1|/| 1|/| 1|/| 2|<span style="color:blue"> 2</span>|/|<span style="color:blue"> 3</span>| 3|/| <span style="color:blue">5</span>|44| 5| 7|/|45|/|45|
|--|-|--|-|--|-|--|--|-|--|--|-|--|--|--|--|-|--|-|--|
***
| 1|/| 1|/| 1|/| 2|/| <span style="color:blue">2</span>|/| 3|/| <span style="color:blue">3</span>|/| 5| <span style="color:blue">5</span>|/|<span style="color:blue">45</span>| 7|/|45|/|45|
|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|--|-|--|--|-|--|-|--|
***
| 1|/| 1|/| 1|/| 2|/| 2|/| 3|/| 3|/| 5|/| <span style="color:blue">5</span>|/| 7|/|<span style="color:blue">45</span>|/|45|/|45|
|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|-|--|
***
## 3. 선형 시간 선택



# 4.분할 정복 기법과 C++ 표준 라이브러리 함수
지금까지 만든 함수들은 대부분 Algorithm 헤더파일에 포함되어 있습니다. 다음은 유용한 함수들 입니다.
|                STL 함수|함수 설명|
|:-----------------------|:-|
|std::binary_search()    |이진 검색을 이용하여 컨테이너에서 원소 하나를 찾는다.|
|std::search()           |컨테이너에서 일련의 원소를 찾는다.|
|std::upper_bound()      |컨테이너에서 주어진 값보다 큰 원소가 나타나는 위치의 주소를 반환한다.|
|std::lower_bound()      |컨테이너에서 주어진 값보다 작은 원소가 나타나는 위치의 주소를 반환한다.|
|std::partition()        |분할 연산을 수행하고, 피벗보다 작은 원소는 왼쪽, 큰 원소는 오른쪽으로 옮긴다.|
|std::partition_copy()   |분할 연산을 수행하고, 두 배열을 반환한다.|
|std::is_partitioned()   |주어진 피벗 기준으로 분할이 되어있는지 검사한다.|
|std::stable_partition() |분할 연산을 수행하며 원소의 원본 순서를 유지한다.|
|std::sort()             |원소를 정렬한다.|
|std::stable_sort()      |원소를 정렬하되, 같은 원소에 대해 원본 순서를 유지하며 정렬한다.|
|std::partial_sort()     |일부 구간만 정렬한다.|
|std::merge()            |병합한다. 순서는 그대로 유지한다.|
|std::nth_element()      |컨테이너에서 n번째로 작은 원소를 반환한다.|
|std::accumulate()       |원소의 누적 합을 계산한다.|
|std::transform()        |컨테이너와 함수가 주어지면, 컨테이너의 모든 원소에 대해 해당 함수를 적용한다.|
|std::reduce()(C++17문법)|지정된 범위의 원소에 대해 리듀스 연산을 수행하고 결과를 반환한다.|
# 5.맵리듀스
<span style="color:blue">