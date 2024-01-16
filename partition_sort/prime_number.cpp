#include <iostream>
#include "mapreduce.hpp"
using namespace std;

name space prime_calculator
{
    bool cinst is_prime(long const number)
    {
        if(number>2)
        {
            if(number%2==0)
                return false;
            
            long const n = abs(number);
            long const sqrt_number = static_cast<long>(sqrt(static_cast<double>(n)));

            for(long i=3; i<=sqrt_number; i+=2)
            {
                if(n%i==0)
                return false;
            }
        }
        else if(number==0||number==1)
            return false;
        return true;
    }
}