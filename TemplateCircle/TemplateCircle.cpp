#include "Crcl_List.h"
#include <iostream>


int main()
{
    test();
    Crcl_List<int32_t> Circle(35);
    Circle.Append(5);
    Circle.Append(7);
    Circle.Insert(-23);
    Circle.extract();
    Circle.extract();
    Circle.extract();
    Circle.extract();
    std::cout << Circle.GetSize() << std::endl;
    Circle.Append(78);
    Circle.Append(23);
    for (auto iter = Circle._begin(); iter != Circle._end(); iter++)
    {
        std::cout << *iter << std::endl;
    }
    for (int i = 0; i < Circle.GetSize(); ++i)
    {
        std::cout << Circle[i] << std::endl;
    }
    Circle.extract(3);
    for (int i = 0; i < Circle.GetSize(); ++i)
    {
        std::cout << Circle[i] << std::endl;
    }
    for (;;)
    {
        int32_t n = 0;
        std::cin >> n;
        std::cout << Circle.GetValue(n) << std::endl;
    }
}
