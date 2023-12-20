#include "Fiber.h"

Fiber::Fiber() {}
int GetRandomInt(int min, int max)
{
    return min + (std::rand() % (max - min + 1));
}
void Fiber::addTask(int32_t priority) {
    tasks.push_back({ priority });
}

void Fiber::addTask() {
    tasks.push_back({ GetRandomInt(Task::min_priority, Task::max_priority) });
}

int32_t Fiber::getCountInVector(Task& task)
{
    return task.max_priority - task.priority + 1;
}
Task& Fiber::getRandomTask(int32_t& numb)
{
    std::vector<int> temp;
    for (int32_t current_task = 0; current_task < tasks.size(); ++current_task)
    {
        for (int32_t i = 0; i < getCountInVector(tasks[current_task]); ++i)
        {
            temp.push_back(current_task);///возможно много resize
        }
    }
    numb = temp[GetRandomInt(0, temp.size() - 1)];
    return tasks[numb];
}

void Fiber::executeRandomTask() {


    if (tasks.empty()) {
        std::cout << "No tasks to execute." << std::endl;
        return;
    }

    int numb = 0;
    Task& selectedTask = getRandomTask(numb);

    selectedTask.execute();

    tasks.erase(tasks.begin() + numb);
}

