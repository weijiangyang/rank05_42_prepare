#include "Vect2.hpp"
#include <string>

Vect2::Vect2()
{
    data[0] = 0;
    data[1] = 0;
}

Vect2::Vect2(int num1, int num2)
{
    data[0] = num1;
    data[1] = num2;
}

Vect2::Vect2(const Vect2 &other)
{
    data[0] = other.data[0];
    data[1] = other.data[1];
}

Vect2 &Vect2::operator=(const Vect2 &other)
{
	if (this != &other)
	{
		this->data[0] = other.data[0];
		this->data[1] = other.data[1];
	}
	return (*this);
}

Vect2::~Vect2() {}

int &Vect2::operator[](int index)
{
	return data[index];
}

const int &Vect2::operator[](int index) const
{
	return data[index];
}

Vect2 &Vect2::operator++()
{
	this->data[0]++;
	this->data[1]++;
	return *this;
}

Vect2 Vect2::operator++(int)
{
	Vect2 tmp;
	tmp = *this;
	++(*this);
	return tmp;
}

Vect2 &Vect2::operator--()
{
	this->data[0]--;
	this->data[1]--;
	return *this;
}

Vect2 Vect2::operator--(int)
{
	Vect2 tmp;
	tmp = *this;
	--(*this);
	return tmp;
}

Vect2 &Vect2::operator+=(const Vect2 &other)
{
	this->data[0] += other.data[0];
	this->data[1] += other.data[1];
	return *this;
}

Vect2 &Vect2::operator-=(const Vect2 &other)
{
	this->data[0] -= other.data[0];
	this->data[1] -= other.data[1];
	return *this;
}

Vect2 &Vect2::operator*=(int scalar)
{
	this->data[0] *= scalar;
	this->data[1] *= scalar;
	return *this;
}

Vect2 Vect2::operator-() const
{
	return (Vect2(-data[0], -data[1]));
}

Vect2 Vect2::operator*(int num) const
{
	return (Vect2(data[0] * num, data[1] * num));
}

Vect2 Vect2::operator+(const Vect2 &other) const
{
	return Vect2(data[0] + other.data[0],
				 data[1] + other.data[1]);
}

Vect2 Vect2::operator-(const Vect2 &other) const
{
	return Vect2(data[0] - other.data[0],
				 data[1] - other.data[1]);
}

Vect2 Vect2::operator*(const Vect2 &other) const
{
	return Vect2(data[0] * other.data[0],
				 data[1] * other.data[1]);
}

bool Vect2::operator==(const Vect2 &other) const
{
	return (data[0] == other.data[0] && data[1] == other.data[1]);
}

bool Vect2::operator!=(const Vect2 &other) const
{
	return (!(*this == other));
}

std::ostream &operator<<(std::ostream &out, const Vect2 &v)
{
	out << "{" << v[0] << ", " << v[1] << "}" << std::endl;
	return out;
}

Vect2 operator*(int num, const Vect2& v)
{
	Vect2 tmp;

	tmp = Vect2(v);
	tmp *= num;
	return tmp;
}