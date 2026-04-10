#ifndef BIGINT_HPP
# define BIGINT_HPP

#include <string>
#include <iostream>

/**
 * bigint 类：处理超长整数
 * 内部使用 std::string 存储数字，以避开硬件对整数位数的限制。
 */
class bigint
{
    private:
        std::string str; // 存储数字的字符串形式，例如 "12345678901234567890"

    public:
        // --- 构造与析构 (Orthodox Canonical Form) ---
        
        bigint();                           // 默认构造：通常初始化为 "0"
        bigint(unsigned int num);           // 将普通无符号整数转换为 bigint
        bigint(const bigint& other);        // 拷贝构造函数
        ~bigint();                          // 析构函数

        // --- 访问器 ---
        std::string getStr() const;         // 获取存储数字的字符串副本

        // --- 赋值运算符 ---
        bigint& operator=(const bigint& other);

        // --- 算术运算符 (加法) ---
        
        // 二元加法：返回两个 bigint 相加后的新对象
        bigint operator+(const bigint& other) const;
        // 复合赋值加法：将 other 累加到当前对象，返回引用以支持链式操作
        bigint& operator+=(const bigint& other);

        // --- 自增运算符 ---
        
        bigint& operator++();               // 前置自增 (++i)：增加后返回自身的引用
        bigint  operator++(int);            // 后置自增 (i++)：返回增加前的副本

        // --- 位移运算符 (参数为无符号整数) ---
        // 注意：在大整数上下文中，<< 通常代表左移（数值增大），>> 代表右移（数值减小）
        bigint operator<<(unsigned int n) const;
        bigint operator>>(unsigned int n) const;
        bigint& operator<<=(unsigned int n);
        bigint& operator>>=(unsigned int n);

        // --- 位移运算符 (参数为 bigint 对象) ---
        // 允许使用另一个 bigint 对象作为位移的步数
        bigint operator<<(const bigint& other) const;
        bigint operator>>(const bigint& other) const;
        bigint& operator<<=(const bigint& other);
        bigint& operator>>=(const bigint& other);

        // --- 比较运算符 ---
        // 由于数字存储在字符串中，比较时需要特殊逻辑（先比长度，长度相同再逐位比字典序）
        bool operator==(const bigint& other) const;
        bool operator!=(const bigint& other) const;
        bool operator<(const bigint& other) const;
        bool operator>(const bigint& other) const;
        bool operator<=(const bigint& other) const;
        bool operator>=(const bigint& other) const;
        
};

/**
 * 全局流输出运算符重载
 * 允许直接使用 std::cout << my_bigint; 打印大整数
 */
std::ostream& operator<<(std::ostream& out, const bigint& data);

#endif