#pragma once
#include <iostream>
#include <vector>

struct Task {
    static const int32_t max_priority = 9;
    static const int32_t min_priority = 1;
    int32_t priority;

    void execute()
    {
        std::cout << "Executing task with priority " << priority << std::endl;
    }

};
class Fiber {
private:
    std::vector<Task> tasks;
public:
    Fiber();
    void addTask(int32_t priority);
    void addTask();
    int32_t getCountInVector(Task& task);
    Task& getRandomTask(int32_t& numb);
    void executeRandomTask();
};
