#include "set.hpp"
#include "searchable_bag.hpp"
#include <string>

/**
 * 默认构造函数
 * 将底层容器指针初始化为 NULL，防止出现野指针。
 */
set::set() : _bag(NULL) {}

/**
 * 参数化构造函数
 * @param bag: 传入一个现有的 searchable_bag 对象的引用。
 * 通过取地址符 &bag，让 set 内部的指针指向该对象。
 * 这允许 set 在运行时绑定不同的实现（如 array_bag 或 tree_bag）。
 */
set::set(searchable_bag &bag) : _bag(&bag) {}

/**
 * 拷贝构造函数（浅拷贝）
 * 直接复制 source 的指针地址。
 * 注意：此时两个 set 对象指向同一个底层 bag，修改其中一个会影响另一个。
 */
set::set(const set &source) : _bag(source._bag) {}

/**
 * 赋值运算符重载（浅拷贝）
 * 同样是复制指针地址。返回 *this 以支持链式赋值（如 s1 = s2 = s3）。
 */
set &set::operator=(const set &source)
{
    if (this != &source) // 防止自赋值
        this->_bag = source._bag;
    return (*this);
}

/**
 * 析构函数
 * 这里只是将指针设为 NULL。
 * 注意：因为是浅拷贝且通过引用传入，set 不拥有 _bag 的生命周期，
 * 所以不能在这里 delete _bag，否则会导致外部对象被意外销毁。
 */
set::~set() 
{
    this->_bag = NULL;
}

/**
 * 插入单个元素
 * 集合（Set）的核心逻辑：在插入前先通过 has() 检查元素是否存在。
 * 只有当元素不存在时，才调用底层 bag 的 insert。
 */
void set::insert(int value)
{
    if (this->_bag != NULL)
    {
        // 保证集合中元素的唯一性
        if (!this->_bag->has(value))
        {
            this->_bag->insert(value);
        }
    }
}

/**
 * 批量插入元素
 * @param array: 整数数组头指针
 * @param size: 数组元素个数
 */
void set::insert(int *array, int size)
{
    // 安全检查：确保底层 bag 存在且传入数组不为空
    if (this->_bag != NULL && array != NULL)
    {
        for (int i = 0; i < size; i++)
            insert(array[i]); // 循环调用单个插入逻辑，确保唯一性检查
    }
}

/**
 * 检查元素是否存在
 * 委托模式：直接询问底层的 bag 是否包含该值。
 */
bool set::has(int value) const
{
    if (this->_bag != NULL)
        return this->_bag->has(value);
    return (false);
}

/**
 * 打印集合
 * 委托底层的 bag 执行具体的打印格式。
 */
void set::print() const
{
    if (this->_bag != NULL)
        this->_bag->print();
}

/**
 * 清空集合
 * 调用底层 bag 的 clear 方法，释放或重置所有存储的节点/元素。
 */
void set::clear()
{
    if(this->_bag != NULL)
        this->_bag->clear();
}

/**
 * 获取底层容器引用
 * 返回 _bag 所指向对象的引用。
 * 对应 main 中的调用，如 sa.get_bag().print()。
 */
#include <stdexcept> // 必须包含此头文件以使用 std::runtime_error

/**
 * 获取底层 Bag 的引用
 * * @return: 返回存储在 _bag 指针所指向对象的引用。
 * @throw:  如果内部指针 _bag 为空，抛出 std::runtime_error 异常。
 * * 设计意图：
 * 1. 引用安全性：C++ 引用必须绑定到有效对象。如果不检查直接 return *_bag，
 * 当 _bag 为 NULL 时会引发段错误（Segmentation Fault）。
 * 2. 异常处理：通过抛出异常，强制调用者处理“未初始化”的情况，而不是让程序静默崩溃。
 */
searchable_bag& set::get_bag() const
{
    // 1. 安全检查：验证底层存储指针是否已分配或绑定
    if (_bag == NULL)
    {
        // 2. 抛出标准运行时异常
        // runtime_error 的构造函数接受一个字符串作为错误描述
        throw std::runtime_error("Error: Attempted to access a NULL bag.");
    }

    // 3. 安全返回：解引用指针并将其作为引用返回
    // 此时调用者可以通过该引用直接操作底层的 searchable_bag 对象
    return *_bag;
}
