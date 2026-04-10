#include "searchable_tree_bag.hpp"

/**
 * 默认构造函数
 * 显式调用 tree_bag 的构造函数。
 * tree_bag 通常会在此处将根节点指针（如 tree 或 root）初始化为 nullptr。
 */
searchable_tree_bag::searchable_tree_bag() : tree_bag() {};

/**
 * 拷贝构造函数
 * 调用 tree_bag 的拷贝构造函数。
 * 树的拷贝通常涉及“深拷贝”（Deep Copy），即递归地复制每一个节点，而不仅仅是复制指针。
 */
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& source) 
    : tree_bag(source) {}

/**
 * 赋值运算符重载
 * 确保在执行 a = b 时，旧的树结构被正确清理，并深拷贝新的树结构。
 */
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& source)
{
    if (this != &source)
    {
        // 调用基类的赋值逻辑，处理复杂的树节点重组
        tree_bag::operator=(source);
    }
    return *this;
}

/**
 * 析构函数
 * 调用 this->clear()。这通常是一个递归释放所有 node 内存的函数。
 * 在处理树形结构时，手动管理内存防止泄漏至关重要。
 */
searchable_tree_bag::~searchable_tree_bag()
{
    this->clear(); 
}

/**
 * 公有接口：has
 * 用户调用的入口。它不暴露底层指针，而是启动递归搜索过程。
 * @param value: 要查找的目标值
 * @return: 查找结果
 */
bool searchable_tree_bag::has(int value) const
{
    // 从根节点 (tree) 开始向下搜索
    return (search(tree, value));
}

/**
 * 私有辅助函数：search (递归实现)
 * 利用 BST（二分搜索树）的特性进行查找：
 * 左子树 < 节点值 < 右子树
 */
bool searchable_tree_bag::search(node* node, const int value) const
{
    // 基准情形 1：遍历到空叶子节点，说明值不存在
    if (node == nullptr)
        return (false);

    // 基准情形 2：当前节点就是要找的值
    if (value == node->value)
        return (true);

    // 递归步骤：
    // 如果目标值小于当前节点，根据 BST 特性，目标只可能在左子树
    if (value < node->value)
        return (search(node->l, value));
    // 否则，目标只可能在右子树
    else
        return (search(node->r, value));
}

/*
核心要点解析
1. 二分搜索效率 (BST Efficiency)

由于你在 search 函数中使用了 value < node->value 的判断，这说明你的树是一棵 二分搜索树 (BST)。

    搜索复杂度：平均情况下为 O(logn)。

    如果这只是一棵普通二叉树（无序），则不能使用 if (value < node->value)，必须同时搜索左右两侧。

2. 内存清理 (clear)

在析构函数中调用 this->clear() 是非常安全的做法。树的 clear 通常采用 后序遍历 (Post-order Traversal)：先销毁左子树，再销毁右子树，最后销毁根节点。
3. 为什么使用递归？

对于树这种天然具有递归特性的数据结构，使用递归实现 search 代码最简洁、易读。

    优化建议：对于极深的树，递归可能导致栈溢出。但在大多数项目（如 42 项目）中，递归搜索是标准且受鼓励的写法。

4. 变量命名注意

    确认你的 tree_bag 基类中定义的成员变量名是 tree 还是 root。

    确认节点的左/右指针是 l/r 还是 left/right。你的实现中使用了 node->l 和 node->r。

这份代码逻辑闭环，通过 private 递归函数配合 public 接口，实现了良好的封装。


*/
