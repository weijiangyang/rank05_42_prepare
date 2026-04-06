#ifndef SEARCHABLE_TREE_BAG_HPP
# define SEARCHABLE_TREE_BAG_HPP

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

/**
 * searchable_tree_bag 类
 * * 继承关系：
 * 1. 继承自 tree_bag：提供二叉树的底层实现（根节点 root、插入、删除等）。
 * 2. 继承自 searchable_bag：提供搜索功能的接口契约（必须实现 has 方法）。
 */
class searchable_tree_bag : public tree_bag, public searchable_bag
{
    private:
        /**
         * 辅助递归搜索函数
         * @param node: 当前遍历到的节点指针
         * @param value: 要查找的目标值
         * @return: 找到返回 true，否则返回 false
         * * 为什么要写这个？
         * 因为 has(int) 是接口要求的，参数只有 int。
         * 而树的遍历需要从 root 开始递归，所以需要这个私有函数来处理递归逻辑。
         */
        bool search(node* curr_node, const int value) const;

    public:
        // --- 构造与析构 ---
        
        searchable_tree_bag();
        searchable_tree_bag(const searchable_tree_bag& source);
        searchable_tree_bag& operator=(const searchable_tree_bag& source);
        virtual ~searchable_tree_bag();

        /**
         * has 函数（重写接口）
         * 内部逻辑通常是：return search(this->root, target);
         */
        virtual bool has(int target) const;
};

#endif
