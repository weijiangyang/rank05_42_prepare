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
	Vect2 &operator++();//返回ref
	Vect2 operator++(int);
	Vect2 &operator--();//返回ref
	Vect2 operator--(int);

	// asignment complex
	Vect2 &operator+=(const Vect2 &other);//返回ref
	Vect2 &operator-=(const Vect2 &ohter);//返回ref
	Vect2 &operator*=(int scalar);//返回ref

	// negative
	Vect2 operator-() const;//返回新值
	// multiplier
	Vect2 operator*(int num) const;//返回新值

	// other mathematic
	Vect2 operator+(const Vect2 &other) const;//返回新值
	Vect2 operator-(const Vect2 &other) const;//返回新值
	Vect2 operator*(const Vect2 &other) const;//返回新值

	// comparaison
	bool operator==(const Vect2 &other) const;
	bool operator!=(const Vect2 &other) const;
};
std::ostream &operator<<(std::ostream &out, const Vect2 &v);
Vect2 operator*(int num, const Vect2& v);//返回新值

#endif