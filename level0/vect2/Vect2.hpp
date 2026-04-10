/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <weiyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:23:25 by weiyang           #+#    #+#             */
/*   Updated: 2026/04/02 14:23:26 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

/**
 * Vect2 类：一个简单的二维向量类（int 数组实现）
 * 遵循 C++ 98 规范（常用于 42 项目等场景）
 */
class Vect2
{
private:
    int data[2]; // 存储向量的 x 和 y 分量

public:
    // --- 构造与析构 (Canonical Orthodox Form) ---
    
    Vect2();                            // 默认构造函数：初始化 data 为 {0, 0}
    Vect2(int num1, int num2);          // 参数化构造函数
    Vect2(const Vect2 &other);         // 拷贝构造函数
    ~Vect2();                           // 析构函数

    // 赋值运算符重载：返回引用以支持链式赋值 (a = b = c)
    Vect2 &operator=(const Vect2 &other);

    // --- 下标运算符 ---
    
    // 返回引用：允许修改内容，如 v[0] = 5;
    int &operator[](int index);
    // 常量版本：仅供读取，用于 const Vect2 对象
    const int &operator[](int index) const;

    // --- 自增与自减 ---
    
    // 前置自增 (++v)：增加后返回自身的引用，效率高
    Vect2 &operator++();
    // 后置自增 (v++)：增加前的副本，int 参数仅用于区分签名，返回的是旧值的拷贝
    Vect2 operator++(int);
    
    // 前置自减 (--v)
    Vect2 &operator--();
    // 后置自减 (v--)
    Vect2 operator--(int);

    // --- 复合赋值运算符 ---
    
    // 这些运算符通常修改当前对象 (*this)，返回引用以支持链式操作
    Vect2 &operator+=(const Vect2 &other);
    Vect2 &operator-=(const Vect2 &other);
    Vect2 &operator*=(int scalar); // 向量与标量的乘法（缩放）

    // --- 算术运算符 (一元) ---
    
    // 取反运算符：返回一个新的取反后的向量对象，不修改原对象
    Vect2 operator-() const;

    // --- 算术运算符 (二元) ---
    
    // 向量乘标量 (v * num)：返回新对象
    Vect2 operator*(int num) const;

    // 向量加减法与点乘：返回新对象，标记为 const 表示不修改操作数
    Vect2 operator+(const Vect2 &other) const;
    Vect2 operator-(const Vect2 &other) const;
    Vect2 operator*(const Vect2 &other) const; // 注意：通常向量乘向量可能是点积(int)或逐元素乘法，此处返回 Vect2 说明是逐元素

    // --- 比较运算符 ---
    
    bool operator==(const Vect2 &other) const;
    bool operator!=(const Vect2 &other) const;
};

/**
 * 非成员函数：流输出重载
 * 放在类外是为了让 std::cout 在左侧，Vect2 在右侧
 */
std::ostream &operator<<(std::ostream &out, const Vect2 &v);

/**
 * 非成员函数：标量乘向量 (num * v)
 * 允许 2 * v 这种写法（类内成员函数只能处理 v * 2）
 */
Vect2 operator*(int num, const Vect2& v);

#endif