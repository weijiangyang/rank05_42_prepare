#ifndef BIGINT_HPP
# define BIGINT_HPP

#include <string>
#include <iostream>


class bigint
{
	private:
		std::string str;

	public:
		bigint();
		bigint(unsigned int num);
		bigint(const bigint& other);
		~bigint();
		
		std::string getStr() const;

		bigint& operator=(const bigint& other);

		//addition
		bigint operator+(const bigint& otherr) const;
		bigint& operator+=(const bigint& other);

		//increment
		bigint& operator++();
		bigint  operator++(int);

		// shift with num
		bigint operator<<(unsigned int n) const;
		bigint operator>>(unsigned int n) const;
		bigint& operator<<=(unsigned int n);
		bigint& operator>>=(unsigned int n);

		// shift with object
		bigint operator<<(const bigint& other) const;
		bigint operator>>(const bigint& other) const;
		bigint& operator<<=(const bigint& other);
		bigint& operator>>=(const bigint& other);

		// ==, !=, <, >, <=, >=
		bool operator==(const bigint& other) const;
		bool operator!=(const bigint& other) const;
		bool operator<(const bigint& other) const;
		bool operator>(const bigint& other) const;
		bool operator<=(const bigint& other) const;
		bool operator>=(const bigint& other) const;
		
};

std::ostream& operator<<(std::ostream& out, const bigint& data);

#endif