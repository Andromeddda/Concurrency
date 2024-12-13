#include "mutex/mutexes.hpp"
#include "thread_pool/thread_pool.hpp"

#include <vector>
#include <iostream>
#include <functional>

using namespace std;

void sum(int& ans, std::vector<int>& arr) 
{
    ans = 0;
    for (auto i = 0LU; i < arr.size(); ++i)
        ans += arr[i];
}

int main(void)
{
    ThreadPool thread_pool(3);
    std::vector<int> s1 = { 1, 2, 3 };
    int ans1 = 0;
    
    std::vector<int> s2 = { 4, 5 };
    int ans2 = 0;
    
    std::vector<int> s3 = { 8, 9, 10 };
    int ans3 = 0;
        
    auto id1 = thread_pool.add_task(sum, std::ref(ans1), std::ref(s1));
    auto id2 = thread_pool.add_task(sum, std::ref(ans2), std::ref(s2));
    auto id3 = thread_pool.add_task(sum, std::ref(ans3), std::ref(s3));

    thread_pool.wait_all();

    std::cout << ans1 << std::endl;
    std::cout << ans2 << std::endl;
    std::cout << ans3 << std::endl;
    return 0;
}