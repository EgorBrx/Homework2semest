#include <iostream>

class Amin
{
public:
	char e[42]{}; 
	bool h, g; 
	int a; 
	double c, d; 
	int f[2]{ 0 };
	int b; 
};

class Amax
{
public:
	bool h; 
	double c;
	bool g;
	double d;
	int a; 
	char e[42]{};
	int f[2]{ 0 }; 
	int b; 
};


int main(int argc, char* argv[])
{
	std::cout << sizeof(Amin) << std::endl;
	std::cout << sizeof(Amax) << std::endl;
	return 0;
}