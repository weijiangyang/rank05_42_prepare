#ifndef VECT2_HPP
# define VECT2_HPP

#include <iostream>

class Vect2
{
	private:
		int data[2];
	public:
		Vect2();
		Vect2(int num1, int num2);
		Vect2(const Vect2& other);
		Vect2& operator=(const Vect2& other);
		~Vect2();

		//index
		int& operator[](int index);
		const int& operator[](int index) const;

		//increment & decrement
		Vect2& operator++();
		Vect2  operator++(int);
		Vect2& operator--();
		Vect2  operator--(int);

		//assignment complex
		Vect2& operator+=(const Vect2& other);
		Vect2& operator-=(const Vect2& other);
		Vect2& operator*=(int scale);

		//negative
		Vect2 operator-() const;
		// scale
		Vect2 operator*(int num) const;

		//other math
		Vect2 operator+(const Vect2& other) const;
		Vect2 operator-(const Vect2& other) const;
		Vect2 operator*(const Vect2& other) const;

		//comparison
		bool operator==(const Vect2& other) const;
		bool operator!=(const Vect2& other) const;
};

std::ostream& operator<<(std::ostream& out, const Vect2& v);
Vect2 operator*(int num, const Vect2& v);

#endif