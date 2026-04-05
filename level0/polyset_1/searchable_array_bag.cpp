#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() : array_bag(){} //其成员均来自父类 array_bag
searchable_array_bag::searchable_array_bag(const searchable_array_bag& other) : array_bag(other){}//其成员均来自父类 array_bag
searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& other)//其成员均来自父类 array_bag
{
	if (this != &other)
	{
		array_bag::operator=(other);
	}
	return *this;
}
searchable_array_bag::~searchable_array_bag(){};//自动调用父类的析构函数来销毁
bool searchable_array_bag::has(int value)const //遍历数组来确认是否包含某个值
{
	for (int i = 0; i < size; i++)
	{
		if(data[i] == value)
			return (true);
	}
	return false;
}