#include "IntModulo.h"

IntMod& IntMod::Normalize()
{
	value = mod(value, _FIELD_ORDER);
	return *this;
}

int32_t IntMod::GetValue() const { return value; }

void IntMod::SetValue(int32_t newvalue) { value = newvalue; this->Normalize(); }

IntMod::IntMod(int32_t value) : value(mod(value, _FIELD_ORDER)) {}

IntMod::IntMod(const IntMod& mod_new) : value(mod_new.value) {}

IntMod::~IntMod() {}

IntMod IntMod::find_reverse() const
{
	int32_t a = value;
	int32_t b = _FIELD_ORDER;
	int32_t x = 0;
	int32_t y = 0;

	if (a == 0)
		throw std::runtime_error("Division by zero");

	gcdExtended(a, b, x, y);
	return IntMod(x);

}
IntMod& IntMod::operator=(const IntMod& intMod)
{
	if (this != &intMod) {
		this->SetValue(intMod.GetValue());
		this->Normalize();
	}
	return *this;
}
const IntMod& IntMod::operator+=(const IntMod& intMod)
{
	this->SetValue(this->GetValue() + intMod.value);
	this->Normalize();
	return *this;
}

const IntMod& IntMod::operator-=(const IntMod& intMod)
{
	this->SetValue(this->GetValue() - intMod.value);
	this->Normalize();
	return *this;
}

const IntMod& IntMod::operator*=(const IntMod& intMod)
{
	this->SetValue(this->GetValue() * intMod.value);
	this->Normalize();
	return *this;
}

const IntMod& IntMod::operator/=(const IntMod& intMod)
{
	*this *= intMod.find_reverse();
	return *this;
}
bool IntMod::operator==(const IntMod& other) const
{
	return mod(value, _FIELD_ORDER) == mod(other.value, _FIELD_ORDER);
}
bool IntMod::operator!=(const IntMod& other) const
{
	return !(*this == other);
}
bool IntMod::operator<(const IntMod& other) const
{
	return mod(value, _FIELD_ORDER) < mod(other.value, _FIELD_ORDER);
}
bool IntMod::operator>(const IntMod& other) const
{
	return mod(value, _FIELD_ORDER) > mod(other.value, _FIELD_ORDER);
}

bool IntMod::operator<=(const IntMod& other) const
{
	return mod(value, _FIELD_ORDER) <= mod(other.value, _FIELD_ORDER);
}

bool IntMod::operator>=(const IntMod& other) const
{
	return mod(value, _FIELD_ORDER) >= mod(other.value, _FIELD_ORDER);
}

/// ???? это метод который меняет или не меняет ? элемент

inline IntMod IntMod::operator^(int32_t exponent)
{  //0^0? 0^(-1)? согласимся: 0^0 = 1, 0^n = 0 n - целое ненулевое 
	if (exponent == 0)
		return 1;
	if (value == 0)
		return 0;
	if (exponent < 0)
		return (this->find_reverse()) ^ (exponent * -1);
	if (exponent % 2 == 1)
		return (*this ^ (exponent - 1)) * (*this);
	return ((*this) * (*this)) ^ (exponent / 2);
}

inline int IntMod::print(std::ostream& stream) const
{
	stream << this->GetValue();
	return 0;
}

const IntMod operator+(const IntMod& left, const IntMod& right)
{
	IntMod result = left;
	return result += right;
}

IntMod operator-(const IntMod& left, const IntMod& right)
{
	IntMod result = left;
	return result -= right;
}

IntMod operator*(const IntMod& left, const IntMod& right)
{
	IntMod result = left;
	return result *= right;
}

IntMod operator/(const IntMod& left, const IntMod& right)
{
	IntMod result = left;
	return result /= right;
}

std::ostream& operator<<(std::ostream& stream, const IntMod& intMod)
{
	intMod.print(stream);
	return stream;
}

std::istream& operator>>(std::istream& stream, IntMod& intMod)
{
	int32_t value;
	stream >> value;
	intMod.SetValue(value);
	return stream;
}

void TestIntMod()
{
	{
		IntMod a(6);
		assert(a.GetValue() == mod(6, _FIELD_ORDER));
	}

	{
		IntMod a(514451);
		assert(a.GetValue() == mod(514451, _FIELD_ORDER));
	}
	{
		IntMod a = 6574142;
		assert(a.GetValue() == mod(6574142, _FIELD_ORDER));
	}
	{
		IntMod a(-42341423);
		assert(a.GetValue() == mod(-42341423, _FIELD_ORDER));
	}
	{
		IntMod a = -42341423;
		assert(a.GetValue() == mod(-42341423, _FIELD_ORDER));
	}
	{
		IntMod a(6);
		IntMod b(532);
		assert(a.GetValue() == mod(6, _FIELD_ORDER));
		a += b;
		assert(a.GetValue() == 60);
	}
	{
		IntMod a(150);
		IntMod b(64536);
		IntMod c = a + b;

		assert(c.GetValue() == mod(64536 + 150, _FIELD_ORDER));
		c += a;
		assert(c.GetValue() == mod(64536 + 150 + 150, _FIELD_ORDER));
	}
	{
		IntMod a(6);
		IntMod b(532);
		IntMod c;
		c = a + b;
		assert(c.GetValue() == mod(6 + 532, _FIELD_ORDER));
		c += a;
		assert(c.GetValue() == mod(6 + 532 + 6, _FIELD_ORDER));
		c += a;
		c += a;
		c += a;
	}
	{
		IntMod a(6);
		a += 5;
		assert(a.GetValue() == mod(6 + 5, _FIELD_ORDER));
	}
	{
		IntMod a(1);
		assert(a.find_reverse().GetValue() == mod(1, 239));
	}
	{
		IntMod a(238);
		assert(a.find_reverse().GetValue() == mod(238, 239));
	}
	{
		IntMod a(132);
		assert(a.find_reverse().GetValue() == mod(67, 239));
	}
	{
		IntMod a(67);
		assert(a.find_reverse().GetValue() == mod(132, 239));
	}
	{
		IntMod a = 67;
		assert(a.find_reverse().GetValue() == mod(132, 239));
	}
	{
		IntMod a = 67 - 239 * 35;
		assert(a.find_reverse().GetValue() == mod(132, 239));
	}
	////условные тесты сломаются от изменение _Field_order 
	{
		IntMod a = 67;
		IntMod b = 123;
		assert(a < b);
	}
	{
		IntMod a = 67;
		assert(a > 5);
	}
	{
		IntMod a = 67;
		assert(a <= 67);
	}
	{
		IntMod a = 67;
		assert(a >= 67);
	}
	{
		IntMod a = 67;
		assert(!(a == 69));
	}
	{
		IntMod a = 67;
		assert(a == 306);
	}
	{
		IntMod a = 67;
		IntMod b = 5234;
		assert(a != b);
	}
	{
		IntMod a = 2;
		IntMod b = a ^ 8;
		assert(b == mod(256, _FIELD_ORDER));
	}
	{
		IntMod a = 7;
		IntMod b = a ^ 8;
		assert(b == mod(121, _FIELD_ORDER));
	}
	{
		IntMod a = 7;
		IntMod b = a ^ 9;
		assert(b == mod(130, _FIELD_ORDER));
	}
	{
		IntMod a = 7;
		IntMod b = a ^ 1;
		assert(b == mod(7, _FIELD_ORDER));
	}
	{
		IntMod a = 7;
		IntMod b = a ^ 0;
		assert(b == mod(1, _FIELD_ORDER));
	}
	{
		IntMod a = 313;
		IntMod b = a ^ -5;
		assert(b == mod(57, _FIELD_ORDER));
	}
	{
		IntMod a = 239;
		IntMod b = 23;
		b = a / b;
		assert(b == mod(0, _FIELD_ORDER));
	}

	IntMod d = 6564;
}
