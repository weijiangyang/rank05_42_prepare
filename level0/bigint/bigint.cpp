#include "bigint.hpp"
#include <sstream>

// --- 构造与基础 ---

bigint::bigint() : str("0"){} // 默认初始化为字符串 "0"

bigint::bigint(unsigned int num)
{
    std::stringstream ss;
    ss << num;
    str = ss.str(); // 利用 stringstream 将数字转为字符串
}

bigint::bigint(const bigint& other)
{
    (*this) = other; // 复用赋值运算符
}

bigint& bigint::operator=(const bigint& other)
{
    if(this != &other) // 防止自赋值
    {
        str = other.str;
    }
    return (*this);
}

std::string bigint::getStr() const
{
    return (str);
}

// --- 辅助计算函数 (Helper Functions) ---

/**
 * 字符串反转函数
 * 为了方便从个位开始计算，通常需要将字符串翻转
 */
std::string reverse(const std::string& str)
{
    std::string revStr;
    for(size_t i = str.length(); i > 0; i--)
    {
        revStr.push_back(str[i - 1]);
    }
    return (revStr);
}

/**
 * 核心加法逻辑 (模拟手工竖式加法)
 * 
 */
std::string addition(const bigint& obj1, const bigint& obj2)
{
    // 1. 将两个数字反转，使得下标 0 对齐个位数
    std::string str1 = reverse(obj1.getStr());
    std::string str2 = reverse(obj2.getStr());
    std::string result;
    
    // 2. 补齐长度：将较短的字符串后面补 '0'，使两者对齐
    size_t len1 = str1.length();
    size_t len2 = str2.length();
    if(len1 > len2) str2.append(len1 - len2, '0');
    else if(len2 > len1) str1.append(len2 - len1, '0');

    // 3. 逐位相加并处理进位
    int carry = 0; // 进位变量
    for(size_t i = 0; i < str1.length(); i++)
    {
        int digit1 = str1[i] - '0'; // 字符转数字
        int digit2 = str2[i] - '0';
        int sum = digit1 + digit2 + carry;

        carry = sum / 10;           // 计算新的进位
        result.push_back((sum % 10) + '0'); // 存储当前位结果
    }

    // 4. 如果最后还有进位，额外补一个 '1'
    if(carry != 0)
        result.push_back(carry + '0');

    // 5. 最后再次反转，恢复正常顺序
    return(reverse(result));
}

// --- 算术运算符重载 ---

bigint bigint::operator+(const bigint& other) const
{
    bigint temp;
    temp.str = addition(*this, other); // 调用辅助函数
    return(temp);
}

bigint& bigint::operator+=(const bigint& other)
{
    (*this) = (*this) + other; // 利用 + 重用逻辑
    return(*this);
}

// 前置自增 (++i)
bigint& bigint::operator++()
{
    *(this) = *(this) + bigint(1);
    return(*this);
}

// 后置自增 (i++)
bigint bigint::operator++(int)
{
    bigint temp = (*this); // 先存副本
    *(this) = *(this) + bigint(1); // 增加
    return(temp); // 返回副本
}

// --- 位移运算符重载 (大整数通常定义为：左移补0，右移删位) ---

// 左移 n 位：相当于乘以 10^n
bigint bigint::operator<<(unsigned int n) const
{
    bigint temp = *this;
    if (temp.str != "0") // 0 左移依然是 0
        temp.str.append(n, '0');
    return(temp);
}

// 右移 n 位：相当于整除 10^n
bigint bigint::operator>>(unsigned int n) const
{
    bigint temp = *this;
    size_t len = temp.str.length();
    if(n >= len)
        temp.str = "0"; // 如果移位超过长度，变为 0
    else
        temp.str.erase(len - n, n); // 删除末尾 n 位
    return(temp);
}

// 辅助函数：将 string 转为 unsigned int 以便进行位移操作
unsigned int stringToUINT(std::string str)
{
    std::stringstream ss(str);
    unsigned int res;
    ss >> res;
    return (res);
}

// 支持 bigint 作为参数的位移 (sa << bigint(2))
bigint bigint::operator<<(const bigint& other) const
{
    return (*this << stringToUINT(other.getStr()));
}

bigint bigint::operator>>(const bigint& other) const
{
    return (*this >> stringToUINT(other.getStr()));
}

// --- 比较运算符重载 ---

bool bigint::operator==(const bigint& other) const
{
    return (this->str == other.str);
}

bool bigint::operator!=(const bigint& other) const
{
    return !(*this == other);
}

bool bigint::operator<(const bigint& other) const
{
    // 数字大小比较逻辑：
    // 1. 先比长度：长度大的数字肯定大
    if(this->str.length() != other.str.length())
        return(this->str.length() < other.str.length());
    // 2. 长度相同时：逐位字典序比较（std::string 已实现此逻辑）
    return(this->str < other.str);
}

bool bigint::operator>(const bigint& other) const
{
    return (other < *this); // 逻辑复用：a > b 即 b < a
}

bool bigint::operator<=(const bigint& other) const
{
    return !(*this > other); // 逻辑复用：<= 即 不大于
}

bool bigint::operator>=(const bigint& other) const
{
    return !(*this < other); // 逻辑复用：>= 即 不小于
}

bigint::~bigint(){};

// --- 非成员函数：输出流 ---
std::ostream& operator<<(std::ostream& output, const bigint& obj)
{
    output << obj.getStr();
    return(output);
}