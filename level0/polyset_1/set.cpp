#include "set.hpp"

set::set() : _bag(nullptr) {}
set::set(searchable_bag &bag) : _bag(&bag) {}
set::set(const set &other) : _bag(other._bag) {}
set &set::operator=(const set &other)
{
	if (this != &other)
		this->_bag = other._bag;
	return *this;
}
set::~set()
{
	_bag = nullptr;
}

void set::insert(int value)
{
	if (_bag != nullptr) // 必须先确认_bag存在
	{
		if (!_bag->has(value))//如果不含有此数值， 才能添加进去， 避免重复
			_bag->insert(value);
	}
}

void set::insert(int *array, int size)
{
	if (_bag != nullptr && array != nullptr)// 必须先确认_bag存在， 且array也存在
	{
		for (int i = 0; i < size; i++)
		{
			insert(array[i]);
		}
	}
}

bool set::has(int value) const
{
	if (_bag != nullptr) // 先确认_bag存在
		return _bag->has(value);
	return false; // 如果_bag不存在， 直接返回false
}

void set::print() const
{
	if (_bag != nullptr) //先确认_bag存在
		_bag->print();
}

void set::clear()
{
	if (_bag != nullptr) //先确认_bag存在
		_bag->clear();
}

searchable_bag& set::get_bag()const
{
	return *_bag;
}
