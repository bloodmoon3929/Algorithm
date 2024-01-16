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
void partial_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    if(std::distance(begin, end)>=1)
    {
        auto partition_iter = partition<T>(begin, end);
        partial_sort<T>(begin, partition_iter-1);
        partial_sort<T>(partition_iter,end);
    }
}

template<typename T>
void print_vector(std::vector<T> arr)
{
	for (auto i : arr)
		std::cout << i << " ";
	std::cout << std::endl;
}

template<typename T>
std::vector<T> input()
{
    T input;
    std::vector<T> scan;
    while (std::cin>>input)
    {
        scan.push_back(input);
    }
    return scan;
}

int main()
{
    std::vector<int> V=input<int>();
    input<int>();
    return 0;
}