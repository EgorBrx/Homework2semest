#include <iostream>
#include <vector>
#include <random>
#include "Fiber.h"

int32_t main(int argc, char* argv[])
{
    std::srand(std::time(nullptr));

    Fiber fiber;

    for (int32_t i = 0; i < 5000; ++i)
        fiber.addTask();
    for (int32_t i = 0; i < 5050; ++i)
        fiber.executeRandomTask();
    return EXIT_SUCCESS;
}