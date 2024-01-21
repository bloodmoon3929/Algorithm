// #include <iostream>
// #include "mapreduce.hpp"
// using namespace std;

// namespace prime_calculator
// {
//     bool const is_prime(long const number)
//     {
//         if(number>2)
//         {
//             if(number%2==0)
//                 return false;
            
//             long const n = abs(number);
//             long const sqrt_number = static_cast<long>(sqrt(static_cast<double>(n)));

//             for(long i=3; i<=sqrt_number; i+=2)
//             {
//                 if(n%i==0)
//                 return false;
//             }
//         }
//         else if(number==0||number==1)
//             return false;
//         return true;
//     }

//     template<typename MapTask>
//     class number_source : mapreduce::detail::noncopyable
//     {
//         public:
//             number_source(long first, long last, long step)
//                 :sequence_(0),first_(first), step_(step){}
//             bool const setup_key(typename MapTask::key_type& key)
//             {
//                 key = sequence_++;
//                 retrun (key*step_<last_);
//             }
//             bool const get_data(typename MapTask::key_type conat& key, typename MapTask:::value_type& value)
//             {
//                 typename MapTask::vaule_type val;
//                 val.first=first_+(key*step_);
//                 val.second=std::min(val.first+step_ -1, last_);

//                 std::swap(val, value);
//                 return true;
//             }
//         private:
//             long sequence_;
//             long const step_;
//             long const last_;
//             long const first_;
//     };
//     struct map_task : public mapreduce::map_task<long, std::pair<long,long>>
//     {
//         template<typename Runtime>
//         void operator()(Runtime& runtime, key_type const& /*key*/, value_type const& value)const
//         {
//             for(key_type loop=value.first; loop<= valur.second;++loop)
//                 runtime.emit_intermediate(is_prime(loop),loop)

//         }
//     };
//     struct reduce_task : public mapreduce::reduce_task<bool,long>
//     {
//         template<typename Runtime, typename It>
//         void operator()(Runtime& runtime, key_type const& key, It it, It ite)const
//         {
//             if(key)
//                 std::for_each(it, ite, std::bind(&Runtime::emit, &runtime, true, std::placeholders::_1));
//         }
//     };
//     typedef mapreduce::job<prime_calculator::map_task,prime_calculator::reduce_task,mapreduce::null_combiner,prime_calculator::number_source<prime_calculator::map_task>>job;
// }
// int main(int argc, char* argv[])
// {
//     mapreduce::specification spec;
//     int prime_limit=1000;
//     int cpu_cores=std::max(1U, std::thread::hardware_concurrency());
//     spec.map_tasks=cpu_cores;
//     spec.reduce_tasks=cpu_cores;

//     prime_calculator::job::datasource_type datasource(0,prime_limit,prime_limit/spec.reduce_tasks);
//     std::cout<<"0부터 "<<prime_limit<<" 사이의 정수에서 소수 판별:"<<std::endl;
//     std::cout<<"CPU 코어 개수: "<<cpu_cores<<std::endl;

//     prime_calculator::job job(datasource, spec);
//     mapreduce::results result;

//     job.run<mapreduce::schedule_policy::cpu_parallel<prime_calculator::job>>(result);
//     std::cout<<"맵리듀스 실행시간: "<<result.job_runtime.count()<<" sec."<<std::endl;
//     std::cout <<"검출된 소수 개수: "<<std::distance(job.begin_results(),job.end_results())<<std::endl;

//     for(auto it = job.begin_results();it!=job.end_results();++it)
//         std::cout<<it->second<<" ";
//     std::cout<<std::endl;

//     return 0;
// }