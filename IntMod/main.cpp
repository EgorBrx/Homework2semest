#include <iostream>
#include <assert.h>

#include "IntModulo.h"

int32_t main(int32_t argc, char* argv[])
{
	TestIntMod();
	TestFunc();

	IntMod a(6);
	IntMod b(532);
	IntMod c = 5;
	IntMod d = 6564;
	std::cout << a << " " << b << " " << c << " " << d << std::endl;
	std::cout << a << " " << b << " " << c << " " << d << std::endl;
	IntMod k;
	std::cin >> k;
	k = k + 5000;
	std::cout << "k = " << k << std::endl;
	c = a + b;
	std::cout << c << std::endl;
	std::cout << a << " " << b << " " << c << " " << d << std::endl;

	return EXIT_SUCCESS;
}