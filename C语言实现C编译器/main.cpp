#pragma once
#include "lexical_analysis.h"
#include "The_symbol_table.h"
//#include "file_mode.h"
#include"head.h"
int main(int argc, char** argv)
{

	string way = argv[1];
	fstream fin;
	fin.open(way, ios::in);
	string buf;
	bool flag = fin.is_open();
	if (flag)
	{
		while (getline(fin, buf))
		{
			parse_line(buf);
		}
	}
	/*while (fgets(buf, MAX_TOKEN_SIZE, file) != NULL)
	{
		parse_line(buf);
	}*/

	fin.close();
	return 0;
}
