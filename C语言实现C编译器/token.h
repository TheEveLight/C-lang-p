#pragma once
#include<string>
using namespace std;
enum class TokenKind
{
	BAD_TOKEN,
	NUMBER_TOKEN,
	ADD_OPERATOR_TOKEN,
	SUB_OPERATOR_TOKEN,
	MUL_OPERATOR_TOKEN,
	DIV_OPERATOR_TOKEN,
	WORD_OPERATOR_TOKEN,
	ASSIGNMENT_OPERATOR_TOKEN,
	SEPARATOR_TOKEN,
	END_OF_LINE_TOKEN
};

#define MAX_TOKEN_SIZE (100)

class Token
{
public:
	TokenKind kind;
	string str;
	double value;
private:
};

void set_line(char* line);
void get_token(Token* token);

