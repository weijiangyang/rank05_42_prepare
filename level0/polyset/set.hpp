#ifndef SET_HPP
# define SET_HPP

# include "searchable_bag.hpp"

class set
{
    private:
        searchable_bag* _bag;

    public:
        // Orthodox Canonical Form
        set();
        set(searchable_bag& bag); // 匹配 set sa(*a)
        set(const set& source);
        set& operator=(const set& source);
        ~set();

        // 必须实现的方法，否则 main.cpp 无法编译
        void insert(int value);               // 对应 st.insert(atoi(argv[i]))
        void insert(int *array, int size);    // 对应 sa.insert((int[]){1,2,3,4}, 4)
        
        bool has(int value) const;            // 对应 sa.has(...)
        void print() const;                   // 对应 sa.print()
        void clear();                         // 对应 sa.clear()

        // 关键：main 中调用了 sa.get_bag().print()
        searchable_bag& get_bag() const;
};

#endif