/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <weiyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:23:22 by weiyang           #+#    #+#             */
/*   Updated: 2026/04/02 14:23:23 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vect2.hpp"

// --- 构造与析构 ---

Vect2::Vect2() {
    data[0] = 0;
    data[1] = 0;
}

Vect2::Vect2(int num1, int num2) {
    data[0] = num1;
    data[1] = num2;
}

// 拷贝构造函数
Vect2::Vect2(const Vect2 &other) {
    *this = other; // 复用赋值运算符
}

Vect2::~Vect2() {}

// 赋值运算符：检查自赋值是关键
Vect2 &Vect2::operator=(const Vect2 &other) {
    if (this != &other) {
        this->data[0] = other.data[0];
        this->data[1] = other.data[1];
    }
    return *this;
}

// --- 下标访问 ---

int &Vect2::operator[](int index) {
    // 注意：在实际项目中，这里通常会加 assert 或 throw 处理 index 越界
    return data[index];
}

const int &Vect2::operator[](int index) const {
    return data[index];
}

// --- 自增 / 自减 ---

// 前置 ++：先修改自己，再返回自己。效率高。
Vect2 &Vect2::operator++() {
    this->data[0]++;
    this->data[1]++;
    return *this;
}

// 后置 ++：先存副本，再修改自己，最后返回副本。
Vect2 Vect2::operator++(int) {
    Vect2 tmp(*this); // 使用拷贝构造
    ++(*this);        // 调用前置版本，减少代码重复
    return tmp;
}

Vect2 &Vect2::operator--() {
    this->data[0]--;
    this->data[1]--;
    return *this;
}

Vect2 Vect2::operator--(int) {
    Vect2 tmp(*this);
    --(*this);
    return tmp;
}

// --- 复合赋值 (Modify-and-Assign) ---

Vect2 &Vect2::operator+=(const Vect2 &other) {
    this->data[0] += other.data[0];
    this->data[1] += other.data[1];
    return *this;
}

Vect2 &Vect2::operator-=(const Vect2 &other) {
    this->data[0] -= other.data[0];
    this->data[1] -= other.data[1];
    return *this;
}

Vect2 &Vect2::operator*=(int scalar) {
    this->data[0] *= scalar;
    this->data[1] *= scalar;
    return *this;
}

// --- 算术运算 (Return new value) ---

Vect2 Vect2::operator-() const {
    return Vect2(-data[0], -data[1]);
}

Vect2 Vect2::operator+(const Vect2 &other) const {
    Vect2 res(*this);
    res += other; // 佳实践：使用 += 来实现 +
    return res;
}

Vect2 Vect2::operator-(const Vect2 &other) const {
    Vect2 res(*this);
    res -= other;
    return res;
}

Vect2 Vect2::operator*(int num) const {
    Vect2 res(*this);
    res *= num;
    return res;
}

// 逐元素乘法
Vect2 Vect2::operator*(const Vect2 &other) const {
    return Vect2(data[0] * other.data[0], data[1] * other.data[1]);
}

// --- 比较运算 ---

bool Vect2::operator==(const Vect2 &other) const {
    return (data[0] == other.data[0] && data[1] == other.data[1]);
}

bool Vect2::operator!=(const Vect2 &other) const {
    return !(*this == other); // 逻辑取反，保证一致性
}

// --- 全局友元/辅助函数 ---

std::ostream &operator<<(std::ostream &out, const Vect2 &v) {
    // 建议：不要在操作符内部写 std::endl，把换行的控制权交给用户
    out << "{" << v[0] << ", " << v[1] << "}";
    return out;
}

// 处理 5 * v 的情况
Vect2 operator*(int num, const Vect2& v) {
    return v * num; // 交换顺序，调用类成员 operator*
}