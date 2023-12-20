#pragma once
#include "usefulfunc.h"
#include <cstdint>
#include <iostream>
#define _FIELD_ORDER 239



class IntMod
{
private:
	int32_t value;
public:
	IntMod& Normalize();
	int32_t GetValue() const;
	void SetValue(int32_t newvalue);
	
	
	IntMod(int32_t value = 0);
	IntMod(const IntMod& mod_new);
	~IntMod();
	IntMod& operator=(const IntMod& intMod);

	IntMod find_reverse() const;


	friend const IntMod operator+(const IntMod& left, const IntMod& right);
	friend IntMod operator-(const IntMod& left,const IntMod& right);

	friend IntMod operator*(const IntMod& left, const IntMod& right);

	friend IntMod operator/(const IntMod& left, const IntMod& right);


	const IntMod& operator+=(const IntMod& intMod);
	const IntMod& operator-=(const IntMod& intMod);
	const IntMod& operator*=(const IntMod& intMod);
	const IntMod& operator/=(const IntMod& intMod);
	bool operator==(const IntMod& other) const;

	bool operator!=(const IntMod& other) const;

	bool operator<(const IntMod& other) const;
	bool operator>(const IntMod& other) const;
	bool operator<=(const IntMod& other) const;
	bool operator>=(const IntMod& other) const;
	/// ???? это метод который меняет или не меняет ? элемент
	IntMod operator^( int32_t exponent);
	int print(std::ostream& stream ) const;
	

};

std::ostream& operator<<( std::ostream& stream, const IntMod& intMod);
std::istream& operator>>(std::istream& stream, IntMod& intMod);
void TestIntMod();