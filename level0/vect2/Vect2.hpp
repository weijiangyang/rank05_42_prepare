/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <weiyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:23:25 by weiyang           #+#    #+#             */
/*   Updated: 2026/04/02 14:23:26 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Vect2_HPP
#define Vect2_HPP

#include <iostream>

class Vect2
{
private:
	int data[2];

public:
	// canonical orthodox
	Vect2();
	Vect2(int num1, int num2);
	Vect2(const Vect2 &other);
	~Vect2();

	Vect2 &operator=(const Vect2 &other);

	//[]index;
	int &operator[](int index);
	const int &operator[](int index) const;

	// increment & decrement
	Vect2 &operator++();
	Vect2 operator++(int);
	Vect2 &operator--();
	Vect2 operator--(int);

	// asignment complex
	Vect2 &operator+=(const Vect2 &other);
	Vect2 &operator-=(const Vect2 &ohter);
	Vect2 &operator*=(int scalar);

	// negative
	Vect2 operator-() const;
	// multiplier
	Vect2 operator*(int num) const;

	// other mathematic
	Vect2 operator+(const Vect2 &other) const;
	Vect2 operator-(const Vect2 &other) const;
	Vect2 operator*(const Vect2 &other) const;

	// comparaison
	bool operator==(const Vect2 &other) const;
	bool operator!=(const Vect2 &other) const;
};
std::ostream &operator<<(std::ostream &out, const Vect2 &v);
Vect2 operator*(int num, const Vect2& v);

#endif