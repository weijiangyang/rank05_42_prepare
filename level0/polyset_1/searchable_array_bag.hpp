#ifndef SEARCHABLE_ARRAY_BAG_HPP
# define SEARCHABLE_ARRAY_BAG_HPP

#include "array_bag.hpp"
#include "searchable_bag.hpp"

//这个类继承了array_bag 与 searchable_bag, 必须canonical orthodox, 析构函数前加virtual, 有一个函数用来查找有无某个值
class searchable_array_bag : public array_bag, public searchable_bag
{
	public:
		searchable_array_bag();
		searchable_array_bag(const searchable_array_bag& other);
		searchable_array_bag& operator=(const searchable_array_bag& other);
		virtual ~searchable_array_bag();

		bool has(int) const;
};

#endif