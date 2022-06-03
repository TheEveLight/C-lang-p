#include"head.h"


int main(int argc, char** argv)
{

	string 项目程序目录 = argv[1];
	文件目录类 项目文件目录(项目程序目录);
	fstream 源代码文件;
	源代码文件.open(项目程序目录, ios::in);

	string 缓存字符串;
	if (源代码文件.is_open())
	{
		while (getline(源代码文件, 缓存字符串))
		{
			词法分析器 词法分析器(缓存字符串);
			// 分析字符串(缓存字符串);
		}
	}
	源代码文件.close();
	return 0;
}
