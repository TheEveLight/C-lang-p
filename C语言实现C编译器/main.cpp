#pragma once
#include "lexical_analysis.h"
#include "The_symbol_table.h"
#include "file_mode.h"
#include"head.h"
int main(int argc, char** argv)
{

	string 项目程序目录 = argv[1];
	文件目录类 项目文件目录(项目程序目录);
	fstream fin;
	fin.open(项目程序目录, ios::in);
	string 缓存字符串;
	if (fin.is_open())
	{
		while (getline(fin, 缓存字符串))
		{
			词法分析_字符串(缓存字符串);
		}
	}
	/*while (fgets(buf, MAX_TOKEN_SIZE, file) != NULL)
	{
		parse_line(buf);
	}*/

	fin.close();
	return 0;
}
