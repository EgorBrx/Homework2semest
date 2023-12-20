#include <iostream>

class A
{
private:
    virtual void foo()
    {
        std::cout << "A::foo()" << std::endl;
    }
};

int main()
{
    A obj;
    void** vtablePtr = *(void***)(&obj);

    void (*funcPtr)() = reinterpret_cast<void (*)()>(vtablePtr[0]);

    funcPtr();

    return 0;
}