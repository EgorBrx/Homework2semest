#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>
#include "SomeSorts.h"
bool greaterThan(int32_t a, int32_t b) {
    return a < b;
}

template <typename SortAlgorithm, typename... Args>
auto SuperSort(SortAlgorithm sortAlgorithm, Args&&... args)
-> decltype(sortAlgorithm(std::forward<Args>(args)...))
{
    return sortAlgorithm(std::forward<Args>(args)...);
}

template <typename Container, typename SortAlgorithm, typename CompareFunction>
auto SuperSort(Container& container, SortAlgorithm sortAlgorithm, CompareFunction compareFunction)
-> decltype(sortAlgorithm(container.begin(), container.end(), compareFunction))
{
    return sortAlgorithm(container.begin(), container.end(), compareFunction);
}


template <typename Container, typename SortAlgorithm>
auto SuperSort(Container& container, size_t size, SortAlgorithm sortAlgorithm)
-> decltype(sortAlgorithm(container, size))
{
    return sortAlgorithm(container, size);
}

template <typename Container, typename SortAlgorithm, typename CompareFunction>
auto SuperSort(Container& container, SortAlgorithm sortAlgorithm, CompareFunction compareFunction)
-> decltype(sortAlgorithm(container, compareFunction))
{
    return sortAlgorithm(container, compareFunction);
}

template <typename Container, typename SortAlgorithm>
auto SuperSort(Container& container, SortAlgorithm sortAlgorithm)
-> decltype(sortAlgorithm(container))
{
    return sortAlgorithm(container);
}

using CompareFunction = std::function<bool(int, int)>;

void SortArray(int32_t* A, CompareFunction compare) {
    //std::sort(arr.begin(), arr.end(), compare);
}

void SortMass(int* m, size_t size)
{
    for (int i = size - 1; i >= 1; i--)
        for (int j = 0; j < i; j++)
        {
            if (m[j] > m[j + 1])
            {
                int foo = m[j];
                m[j] = m[j + 1];
                m[j + 1] = foo;
            }
        }
}

void SortMass2(size_t size, size_t x, int32_t* m)
{
    for (int i = size - 1; i >= 1; i--)
        for (int j = 0; j < i; j++)
        {
            if (m[j] > m[j + 1])
            {
                int foo = m[j];
                m[j] = m[j + 1];
                m[j + 1] = foo;
            }
        }
}

int main(int argc, char* argv[]) 
{
    std::vector<int> myVector = { 3, 1, 2, 2312,2,134,1 };
    SuperSort(myVector, std::sort<std::vector<int>::iterator, bool(*)(int32_t, int32_t)>, greaterThan);

    for (const auto& num : myVector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    int32_t A[4] = { 3,1,6,4 };
    SuperSort(SortMass, A, 4);

    for (int32_t i = 0; i < 4; ++i)
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
    int32_t B[16] = { 3,1,6,4,13,-534,13125,645362,13213214,312,2,9,12312,-3123,4324,-3432 };
    SuperSort(bubbleSort<int32_t*, std::less<int32_t>>, B, B + 16, std::less<int32_t>());
    for (int32_t i = 0; i < 16; ++i)
    {
        std::cout << B[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}