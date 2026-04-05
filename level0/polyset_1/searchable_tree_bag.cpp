#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag(){}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other){}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& other)
{
	if (this != &other)
	{
		tree_bag::operator=(other);
	}
	return *this;
}
//增加clear, 用于显式清理成员（因为二叉树的特殊性）
searchable_tree_bag::~searchable_tree_bag()
{
	this->clear();
}

bool searchable_tree_bag::has(int value) const
{
	return (search(tree, value));
}
bool searchable_tree_bag::search(node* node, const int value) const
{
	if (!node)//递归的终止条件
		return false;
	if (node->value == value)//递归的终止条件
		return true;
	if (value < node->value)
		return search(node->l, value);//继续递归
	else
		return search(node->r, value);//继续递归（一定要加return )
}
