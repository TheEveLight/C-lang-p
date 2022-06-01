#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "token.h"
#include "The_symbol_table.h"
#include"head.h"
using namespace std;
unordered_map<TokenKind, string> Token_map;
pair<TokenKind, string> token_pair;
static char* st_line;
static int st_line_pos;
enum class LexerStatus {
	INITIAL_STATUS,
	NUM_STATUS,
	IN_INT_PART_STATUS,
	DOT_STATUS,
	IN_FRAC_PART_STATUS,
	WORD_STAUS,
	ASSIGNMENT_STAUS,
	SEPARATOR_STAUS//�ָ��״̬
};//�ʷ�������״̬
class Token;
void get_token(Token* token)
{
	int out_pos = 0;
	LexerStatus status = LexerStatus::INITIAL_STATUS;
	char current_char;
	char next_char;

	token->kind = TokenKind::BAD_TOKEN;
	while (st_line[st_line_pos] != '\0')
	{
		current_char = st_line[st_line_pos];
		next_char = st_line[st_line_pos + 1];
		if (((status == LexerStatus::IN_INT_PART_STATUS || status == LexerStatus::IN_FRAC_PART_STATUS)
			&& !isdigit(current_char) && current_char != '.'))
		{
			token->kind = TokenKind::NUMBER_TOKEN;
			//sscanf(token->str, "%lf", &token->value);
			token->value = atoi(token->str.c_str());
			return;
		}
		if (status == LexerStatus::WORD_STAUS)
		{
			token->kind = TokenKind::WORD_OPERATOR_TOKEN;
			//sscanf(token->str, "%(MAX_TOKEN_SIZE-1)s", &token->value);
			token->value = atoi(token->str.c_str());
			return;
		}
		if (status == LexerStatus::SEPARATOR_STAUS)
		{
			token->kind = TokenKind::SEPARATOR_TOKEN;
			//sscanf(token->str, "%s", &token->value);
			token->value = atoi(token->str.c_str());
			return;
		}
		//����ǿհ��ַ����ж��ǲ��ǻ��з��ţ�������ʶ��Ϊ�ַ���������־������ǰ�ַ�ָ��++
		if (isspace(current_char)) {
			if (current_char == '\n') {
				token->kind = TokenKind::END_OF_LINE_TOKEN;
				return;
			}
			st_line_pos++;
			continue;
		}
		//����ַ��������������ָʾ������ �������ʾ
		if (out_pos >= MAX_TOKEN_SIZE - 1) {
			//�����׼�������� ������ʾ���Ǻų��ȹ���
			fprintf(stderr, "token too long.\n");
			exit(1);
		}
		token->str[out_pos] = st_line[st_line_pos];//��st_line[st_line_pos]�ַ�����str�ַ�����out_pos��
		st_line_pos++;//ָ����һ��
		out_pos++;
		token->str[out_pos] = '\0';//����ַ���������־
		if (current_char == '+')
		{
			token->kind = TokenKind::ADD_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '-')
		{
			token->kind = TokenKind::SUB_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '*')
		{
			token->kind = TokenKind::MUL_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '/')
		{
			token->kind = TokenKind::DIV_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == ';')
		{
			status = LexerStatus::SEPARATOR_STAUS;
		}
		else if (isdigit(current_char))
		{
			if (status == LexerStatus::INITIAL_STATUS)
			{
				status = LexerStatus::IN_INT_PART_STATUS;//����Ϊ����״̬
			}
			else if (status == LexerStatus::DOT_STATUS)//����Ϊ����״̬
			{
				status = LexerStatus::IN_FRAC_PART_STATUS;
			}
		}
		else if (current_char == '.')
		{
			if (status == LexerStatus::IN_INT_PART_STATUS)
				status = LexerStatus::DOT_STATUS;
			else {
				fprintf(stderr, "syntax error.\n");
				exit(1);
			}
		}
		else if ('A' <= current_char <= 'z')
		{
			if (isspace(next_char))
				status = LexerStatus::WORD_STAUS;
		}
		else if (current_char == '=') {
			token->kind = TokenKind::ASSIGNMENT_OPERATOR_TOKEN;
			return;
		}
		else {
			fprintf(stderr, "bad character(%c)\n", current_char);
			exit(1);
		}
	}
}

void set_line(string line)
{
	st_line = line.c_str();
	st_line_pos = 0;
}


void parse_line(string buf)
{
	Token token;

	set_line(buf);

	for (;;)
	{
		get_token(&token);
		if (token.kind == TokenKind::END_OF_LINE_TOKEN)
		{
			break;
		}
		else
		{
			token_pair.first = token.kind;
			token_pair.second = token.str;
			Token_map.insert(token_pair);
			std::cout << "parse:kind=" << (int)token.kind << "	vulue=" << token.str << std::endl;
		}
	}
}
