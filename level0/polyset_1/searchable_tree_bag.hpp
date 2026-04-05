#ifndef SEARCHABLE_TREE_BAG_HPP
# define SEARCHABLE_TREE_BAG_HPP

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

// 与searchable_array_bag类似
class searchable_tree_bag : public tree_bag, public searchable_bag
{
	private:
	   // 此函数属于类的内部调用， 所以用private
		bool search(node* node, const int value) const;
	public:
		searchable_tree_bag();
		searchable_tree_bag(const searchable_tree_bag& other);
		searchable_tree_bag& operator=(const searchable_tree_bag& other);
		virtual ~searchable_tree_bag();

		bool has(int) const;
		
};

#endif