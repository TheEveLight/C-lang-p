#pragma once
#include"head.h"
using namespace std;
//unordered_map<词法单元种类, string> 符号表;
//pair<词法单元种类, string> 符号键值对;
static string 字符流暂存串;
static int 暂存串字符下标;
static int 暂存串长度;
static int 传入字符串长度;
static bool 暂存串结束标志 = 0;
enum class 词法分析器状态 {
	初态,
	纯整数状态,
	整数部分状态,
	小数点状态,
	浮点部分状态,
	字母状态,
	赋值符状态,
	分隔符状态,
};
void 得到下一词法单元(词法单元类* 词法单元)
{
	int 已输出字符数 = 0;
	词法分析器状态 词法分析器状态 = 词法分析器状态::初态;
	char 当前字符;
	char 下一字符;
	词法单元->种类 = 词法单元种类::错误类型;
	词法单元->字符串.erase(0);
	词法单元->值 = NULL;
	while (传入字符串长度 <= 暂存串长度 + 1)
	{
		传入字符串长度++;
		当前字符 = 字符流暂存串[暂存串字符下标];
		if (暂存串字符下标 + 1 <= 暂存串长度)
		{
			下一字符 = 字符流暂存串[暂存串字符下标 + 1];
		}
		if (词法分析器状态 == 词法分析器状态::纯整数状态)
		{
			词法单元->种类 = 词法单元种类::数字;
			词法单元->值 = atoi(词法单元->字符串.c_str());
		}
		if ((词法分析器状态 == 词法分析器状态::整数部分状态 || 词法分析器状态 == 词法分析器状态::浮点部分状态) && !isdigit(当前字符) && 当前字符 != '.' && !isdigit(当前字符))
		{
			词法单元->种类 = 词法单元种类::数字;
			//sscanf(token->str, "%lf", &token->value);
			词法单元->值 = atoi(词法单元->字符串.c_str());
			return;
		}
		if (词法分析器状态 == 词法分析器状态::字母状态)
		{
			if (下一字符 == '\0' && ('A' << 当前字符 && 当前字符 << 'z'))
			{
				词法单元->种类 = 词法单元种类::字母;
				//sscanf(token->str, "%(MAX_TOKEN_SIZE-1)s", &token->value);
				词法单元->值 = atoi(词法单元->字符串.c_str());
				return;
			}
		}
		if (词法分析器状态 == 词法分析器状态::分隔符状态)
		{
			词法单元->种类 = 词法单元种类::分隔符;
			//sscanf(token->str, "%s", &token->value);
			词法单元->值 = atoi(词法单元->字符串.c_str());
			return;
		}
		if (isspace(当前字符)) {

			暂存串字符下标++;
			continue;
		}
		if (已输出字符数 >= 最大符号长度 - 1) {
			fprintf(stderr, "token too long.\n");
			exit(1);
		}
		词法单元->字符串.push_back(字符流暂存串[暂存串字符下标]);
		暂存串字符下标++;
		//out_pos++;
		//token->str[out_pos] = '\0';
		if (当前字符 == '+')
		{
			词法单元->种类 = 词法单元种类::加号;
			return;
		}
		else if (当前字符 == '-')
		{
			词法单元->种类 = 词法单元种类::减号;
			return;
		}
		else if (当前字符 == '*')
		{
			词法单元->种类 = 词法单元种类::乘号;
			return;
		}
		else if (当前字符 == '/')
		{
			词法单元->种类 = 词法单元种类::除号;
			return;
		}
		else if (当前字符 == ';')
		{
			词法分析器状态 = 词法分析器状态::分隔符状态;
		}
		else if (isdigit(当前字符))
		{
			if (词法分析器状态 == 词法分析器状态::初态)
			{
				词法分析器状态 = 词法分析器状态::整数部分状态;
			}
			else if (词法分析器状态 == 词法分析器状态::小数点状态)
			{
				词法分析器状态 = 词法分析器状态::浮点部分状态;
			}
		}
		else if (当前字符 == '.')
		{
			if (词法分析器状态 == 词法分析器状态::整数部分状态)
				词法分析器状态 = 词法分析器状态::小数点状态;
			else {
				fprintf(stderr, "syntax error.\n");
				exit(1);
			}
		}

		else if ('A' <= 当前字符 <= 'z')
		{
			词法分析器状态 = 词法分析器状态::字母状态;
		}
		else if (当前字符 == '=') {
			词法单元->种类 = 词法单元种类::等号;
			return;
		}
		else {
			fprintf(stderr, "bad character(%c)\n", 当前字符);
			exit(1);
		}
	}

	if (传入字符串长度 >= 暂存串长度)
	{
		词法单元->种类 = 词法单元种类::字符串结束符;
		return;
	}
}

void 初始化符号缓存串(string 行串)
{
	字符流暂存串 = 行串;
	暂存串字符下标 = 0;
	暂存串长度 = 行串.length();
	传入字符串长度 = 0;
}


void 分析字符串(string 一行字符串)
{
	词法单元类 token;

	初始化符号缓存串(一行字符串);

	for (;;)
	{
		得到下一词法单元(&token);
		if (token.种类 == 词法单元种类::字符串结束符)

		{
			break;
		}
		else
		{
			符号键值对.first = token.种类;
			符号键值对.second = token.字符串;
			符号表.insert(符号键值对);
			//std::cout << "parse:kind=" << (int)token.种类 << "	vulue=" << token.字符串 << std::endl;
		}
	}
}
