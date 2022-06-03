#pragma once
#include"head.h"
using namespace std;
enum class 词法单元种类
{
	错误类型,
	数字,
	加号,
	减号,
	乘号,
	除号,
	字母,
	等号,
	分隔符,
	字符串结束符
};

#define 最大符号长度 (100)

class 词法单元类
{
public:
	词法单元种类 种类;
	string 字符串;
	double 值;
private:
};

void set_line(char* line);
void 得到下一词法单元(词法单元类* token);

