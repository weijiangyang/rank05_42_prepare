#include "searchable_tree_bag.hpp"
#include <string>

searchable_tree_bag::searchable_tree_bag() : tree_bag(){};
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& source) : tree_bag(source){}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& source)
{
    if (this != &source)
    {
      tree_bag::operator=(source);
    }
    return *this;
}
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
    if (node == NULL)
        return (false);
    if (value == node->value)
        return (true);
    if (value < node->value)
        return (search(node->l, value));
    else
        return (search(node->r, value));

}
