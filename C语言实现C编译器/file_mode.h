#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;
FILE* file_open(const char* file_way)
{
	//*file_way = "D:/demo.txt";
	FILE* file = NULL;
	file = fopen(file_way, "r+");
	if (file == NULL)
		exit(1);
	else
		return file;
}
class 文件目录类
{
public:
	文件目录类(string 程序路径)
	{
		size_t 末尾分隔符位置 = 程序路径.rfind('\\');
		size_t 字符串长度 = 程序路径.length();
		根目录 = 程序路径.erase(末尾分隔符位置);
	}
	string 根目录;

};
unsigned file_close(FILE* file_way)
{
	FILE* file = file_way;
	if (fclose(file) == EOF)
	{
		printf("cant close file");
		exit(2);
	}
}