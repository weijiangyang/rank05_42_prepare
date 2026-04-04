#include "set.hpp"
#include "searchable_bag.hpp"
#include <string>

set::set() : _bag(NULL) {}
set::set(searchable_bag &bag) : _bag(&bag) {}
set::set(const set &source) : _bag(source._bag) {}
set &set::operator=(const set &source)
{
    if (this != &source)
        this->_bag = source._bag;
    return (*this);
}

// set.cpp
set::~set() 
{
   
        this->_bag = NULL;
    
}

void set::insert(int value)
{
    if (this->_bag != NULL)
    {
        if (!this->_bag->has(value))
        {
            this->_bag->insert(value);
        }
    }
}

void set::insert(int *array, int size)
{
    if (this->_bag != NULL && array != NULL)
    {
        for (int i = 0; i < size; i++)
            insert(array[i]);
    }
}

bool set::has(int value) const
{
    if (this->_bag != NULL)
        return this->_bag->has(value);
    return (false);
}

void set::print() const
{
    if (this->_bag != NULL)
        this->_bag->print();
}

void set::clear()
{
    if(this->_bag != NULL)
        this->_bag->clear();
}
searchable_bag& set::get_bag() const
{
    return *_bag;
}

