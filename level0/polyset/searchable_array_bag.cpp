#include "searchable_array_bag.hpp"

/**
 * 默认构造函数
 * 显式调用 array_bag 的默认构造函数。
 * 即使不写 : array_bag()，编译器也会自动调用，但显式写出能增加代码可读性。
 * 注意：由于 searchable_bag 是虚继承，底层的 bag 实例由这里的构造函数负责初始化。
 */
searchable_array_bag::searchable_array_bag() : array_bag() {};

/**
 * 拷贝构造函数
 * 利用初始化列表（Member Initializer List）调用父类的拷贝构造函数。
 * 这样做可以确保 source 对象中的数组数据（data）和大小（size）被正确复制到新对象中。
 */
searchable_array_bag::searchable_array_bag(const searchable_array_bag& source) 
    : array_bag(source) {}

/**
 * 赋值运算符重载 (operator=)
 * 用于处理类似 s1 = s2; 的操作。
 */
searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& source)
{
    // 1. 防止自赋值（Self-assignment），例如 s1 = s1;
    if (this != &source)
    {
        // 2. 调用基类的赋值运算符，完成数组数据的拷贝
        // 这里主要依赖 array_bag 已经实现的内存拷贝逻辑
        array_bag::operator=(source);
    }
    // 3. 返回当前对象的引用，以支持链式赋值 (a = b = c)
    return *this;
}

/**
 * 析构函数
 * 虽然目前函数体为空，但由于基类中声明了 virtual，
 * 当对象被销毁时，系统会自动按照“先子类、后基类”的顺序正确释放内存。
 */
searchable_array_bag::~searchable_array_bag() {}

/**
 * 核心功能：has (查找元素)
 * 实现自 searchable_bag 接口定义的纯虚函数。
 */
bool searchable_array_bag::has(int value) const
{
    // 遍历存储在 array_bag 中的底层数组
    // 注意：此处假设 size 和 data 在 array_bag 中是 protected 权限
    // 如果是 private 权限，则需要使用 get_size() 或 operator[] 访问
    for(int i = 0; i < size; i++)
    {
        // 如果找到匹配的值，立即返回 true（早停逻辑，效率最高）
        if(data[i] == value)
            return (true);
    }
    // 遍历结束未找到，返回 false
    return (false);
}