#pragma once
#define _CRT_NONSTDC_NO_DEPRECATE
#include"head.h"


struct nlist {
	char* name;//������
	char* defn;
	struct nlist* next;
	struct nlist* last;
};

#define HASHSIZE 101
static struct nlist* Hash_tab[HASHSIZE];

unsigned Hash(char* s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct nlist* Look_up(char* s)
{
	struct nlist* np;

	for (np = Hash_tab[Hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)//�ַ����Ƚ� s��np->nameֵ���
			return np;
	return NULL;
}

struct nlist* Install(char* name, char* defn)
{
	struct nlist* np;
	unsigned hashval;
	//��������ڷ���name
	if ((np = Look_up(name)) == NULL)
	{
		np = (struct nlist*)malloc(sizeof(*np));//����һ����np��Сƥ��Ŀռ� �������ַ��np
		if (np == NULL || (np->name = _strdup(name)) == NULL)//���Ų����ڻ����ַ�������ʧ��
			return NULL;
		hashval = Hash(name);//��ϣ������������±�
		np->next = Hash_tab[hashval];//�ŵ���Ӧ�Ĺ�ϣλ��
		Hash_tab[hashval] = np;//��ָ�뱣�浽��Ӧ��ϣλ��
		if (np->next != NULL)
			np->next->last = np;
	}
	else
		free((void*)np->defn);//�ͷű�np->defnָ��Ŀռ�
	if ((np->defn = _strdup(defn)) == NULL)//��defn���ַ������Ƶ�np-defn�С����ʧ�ܷ���NULL �ɹ�����np��ָ��
		return NULL;
	return np;
}

struct nlist* Delete(char* name)
{
	struct nlist* lp;
	struct nlist* lp_Next;
	unsigned hashval;
	if ((lp = Look_up(name)) != NULL)
	{
		hashval = Hash(name);
		lp = Hash_tab[hashval];
		//int flag;
		while (1)
		{
			if (lp->next == NULL)
			{
				free(lp);
				break;
			}
			else
			{
				lp_Next = lp->next;
				free(lp);
				lp = lp_Next;
			}
		}
	}
	return 0;
}
struct nlist* update(char* name, char* defn)
{
	struct nlist* np;
	//unsigned hashval;
	//��������ڷ���name
	if ((np = Look_up(name)) == NULL)
	{
		printf("error,name cant find");
	}
	else
		if ((np->defn = _strdup(defn)) == NULL)//��defn���ַ������Ƶ�np-defn�С����ʧ�ܷ���NULL �ɹ�����np��ָ��
			return NULL;
}