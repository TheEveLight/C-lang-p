#include"head.h"
using namespace std;
class 文件目录类
{
public:
	string 根目录;
	文件目录类(string 程序路径)
	{
		size_t 末尾分隔符位置 = 程序路径.rfind('\\');
		size_t 字符串长度 = 程序路径.length();
		根目录 = 程序路径.erase(末尾分隔符位置);
	}
};