#include <iostream>
#include <thread>
#include  "SafeQueue.h"

queue<int> q;

void PushElements() 
{
    for (int32_t i = 0; i < 1000; ++i) 
    {
        q.push(i);
    }
}


void PopElements() 
{

    for (int32_t i = 0; i < 999; ++i) 
    {
        q.pop();
    }
}
int main() {
    {
        const int numThreads = 10;
        std::thread threads[numThreads];

        for (int i = 0; i < numThreads; ++i) {
            threads[i] = std::thread(PushElements);
        }

        for (int i = 0; i < numThreads; ++i) {
            threads[i].join();
        }

        if (q.size() == numThreads * 1000) {
            std::cout << "COMPLETE" << std::endl;
        }
        else {
            std::cout << "FAIL" << std::endl;
        }
    }
    {
        const int numThreads = 10;
        std::thread threads[numThreads];

        for (int i = 0; i < numThreads; ++i) {
            threads[i] = std::thread(PopElements);
        }

        for (int i = 0; i < numThreads; ++i) {
            threads[i].join();
        }
        if (q.size() == 10 ) {
            std::cout << "COMPLETE" << std::endl;
        }
        else {
            std::cout << "FAILED" << std::endl;
        }

    }
}