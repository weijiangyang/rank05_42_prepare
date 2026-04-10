#ifndef SEARCHABLE_ARRAY_BAG_HPP
# define SEARCHABLE_ARRAY_BAG_HPP

#include "array_bag.hpp"
#include "searchable_bag.hpp"

/**
 * searchable_array_bag 类
 * * 这是一个“混合类”，它通过多重继承结合了两个父类的能力：
 * 1. 继承自 array_bag：获得了基于数组的存储实现（如何存数据）。
 * 2. 继承自 searchable_bag：获得了“可搜索”的行为契约（能做什么操作）。
 */
class searchable_array_bag : public array_bag, public searchable_bag
{
    public:
        // --- 构造与析构 ---

        // 默认构造函数：负责调用基类的构造逻辑
        searchable_array_bag();

        // 拷贝构造函数：确保在复制对象时，array_bag 里的数组内容也能被正确复制
        searchable_array_bag(const searchable_array_bag& source);

        // 赋值运算符重载：支持 a = b 的操作，内部需显式调用父类的赋值逻辑
        searchable_array_bag& operator=(const searchable_array_bag& source);

        // 虚析构函数：由于存在多态调用，必须设为 virtual 以防止内存泄漏
        virtual ~searchable_array_bag();

        // --- 核心功能 ---

        /**
         * 虚函数 has：实现自 searchable_bag 接口
         * @param target: 要查找的整数
         * @return: 如果数组中存在该数则返回 true，否则返回 false
         * * 注意：虽然在 searchable_bag 中它是纯虚函数 (=0)，
         * 但在这里我们必须给出具体实现，否则这个类将无法实例化。
         */
        virtual bool has(int target) const;
};

#endif