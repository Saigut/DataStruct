/*
 * main.c
 *
 *   Created on: 2014年12月4日
 *       Author: Saigut
 *  Description: 对比二叉排序树与数组
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct bTree
{
	long long id;
	long long name;
	int score;
	struct bTree * LSubBTree;
	struct bTree * RSubBTree;
} Student;

Student * Head = NULL;

const long NUMBER = 200000; //学生数量
const long TARGET = 100000; //要查找的学生在数组中的位次

void AddR(long long id, long long name, int score, Student * HeadOfABTree);
void Add(long long id, long long name, int score, Student * HeadOfABTree);

void DisplayBTreeR(Student * HeadOfABTree, int SubBTreeFlag);
void DisplayBTree(Student * HeadOfABTree);

void DeleteTheBTree(Student * HeadOfABTree);

Student * FindInBTree(long long name, Student * HeadOfABTree);

int FindInArray(long long name, Student group[]);

int depth = -4;

int main(void)
{
	puts("   二叉排序树和数组对比：");
	puts("   （为了便于排序时比较，名字以数字表示）");

	Student group[NUMBER];
	int i, id = 1000;
	long long SearchName;
	long start, end, TimeOfArray, TimeOfBTree;

	Student * BResult;
	int AResult;

	for (i = 0; i < NUMBER; i++, id++)
	{
		group[i].id = id;
		group[i].name = rand();
		group[i].score = rand() % 100;
		group[i].LSubBTree = NULL;
		group[i].RSubBTree = NULL;
	}


	puts("\n");
	puts("在数组中的名字：");
	for (i = 0; i < NUMBER; i++)
	{
		printf("%lld\t%lld\t%d\n", group[i].id, group[i].name, group[i].score);
	}

	puts("\n");
	for (i = 0; i < NUMBER; i++)
	{
		Add(group[i].id, group[i].name, group[i].score, Head);
	}
	DisplayBTree(Head);

	puts("\n");
//	SearchName = group[(rand() % 50)].name;
//	SearchName = group[(rand() % 50)].name;
	SearchName = group[TARGET].name;
	printf("查找名字：%lld\n数量：%ld, 目标在数组中位置：%ld\n\n", SearchName, NUMBER, TARGET);

	puts("\n结果：");
	start = clock();
	FindInArray(SearchName, group);
	end = clock();
	AResult = FindInArray(SearchName, group);
	TimeOfArray = end - start;
	printf("\n在数组中找到%lld的id为：%lld\n耗时：%ld毫秒\n", SearchName, group[AResult].id, TimeOfArray);

	start = clock();
	FindInBTree(SearchName, Head);
	end = clock();
	BResult = FindInBTree(SearchName, Head);
	TimeOfBTree = end - start;
	printf("\n在二叉排序树中找到%lld的id为：%lld\n耗时：%ld毫秒\n", SearchName, BResult->id, TimeOfBTree);

	float rate = TimeOfArray/TimeOfBTree;
	printf("二叉排序树速度是数组的%f倍", rate);

	return 0;
}

void AddR(long long id, long long name, int score, Student * HeadOfABTree)
{
	if (name > HeadOfABTree->name)
	{
		if (HeadOfABTree->RSubBTree == NULL)
		{
			HeadOfABTree->RSubBTree = (Student *) malloc(sizeof(Student));
			HeadOfABTree->RSubBTree->id = id;
			HeadOfABTree->RSubBTree->name = name;
			HeadOfABTree->RSubBTree->score = score;
			HeadOfABTree->RSubBTree->LSubBTree = NULL;
			HeadOfABTree->RSubBTree->RSubBTree = NULL;
		}
		else
			Add(id, name, score, HeadOfABTree->RSubBTree);
	}
	else
	{
		if (HeadOfABTree->LSubBTree == NULL)
		{
			HeadOfABTree->LSubBTree = (Student *) malloc(sizeof(Student));
			HeadOfABTree->LSubBTree->id = id;
			HeadOfABTree->LSubBTree->name = name;
			HeadOfABTree->LSubBTree->score = score;
			HeadOfABTree->LSubBTree->LSubBTree = NULL;
			HeadOfABTree->LSubBTree->RSubBTree = NULL;
		}
		else
			Add(id, name, score, HeadOfABTree->LSubBTree);
	}
}

void Add(long long id, long long name, int score, Student * HeadOfABTree)
{
	if (HeadOfABTree == NULL)
	{
		Head = (Student *) malloc(sizeof(Student));
		Head->id = id;
		Head->name = name;
		Head->score = score;
		Head->LSubBTree = NULL;
		Head->RSubBTree = NULL;
	}
	else
		AddR(id, name, score, HeadOfABTree);
}

void DisplayBTreeR(Student * HeadOfABTree, int SubBTreeFlag)
{
	//depth深度用于控制输出
	depth += 4;

	//按右、中、左的顺序，在屏幕上由上到下输出
	if (HeadOfABTree->RSubBTree != NULL)
		DisplayBTreeR(HeadOfABTree->RSubBTree, 2);
	else if (HeadOfABTree->LSubBTree != NULL)			//这里让空缺结点位置打出一个空行，保持整体输出结构。
		puts("");

	int i = depth - 1;
	for (; i > 0; i--)
		printf(" ");
	if (SubBTreeFlag == 1)
		printf("\\");
	if (SubBTreeFlag == 2)
		printf("/");
	printf("%lld", HeadOfABTree->name);
	puts("");

	if (HeadOfABTree->LSubBTree != NULL)
		DisplayBTreeR(HeadOfABTree->LSubBTree, 1);
	else if (HeadOfABTree->RSubBTree != NULL)
		puts("");

	depth -= 4;
}

void DisplayBTree(Student * HeadOfABTree)
{
	if (HeadOfABTree != NULL)
		DisplayBTreeR(HeadOfABTree, 0);
}

void DeleteTheBTree(Student * HeadOfABTree)
{
	if (HeadOfABTree != NULL)
	{
		DeleteTheBTree(HeadOfABTree->LSubBTree);
		DeleteTheBTree(HeadOfABTree->RSubBTree);
		free(HeadOfABTree);
	}
}

Student * FindInBTree(long long name, Student * HeadOfABTree)
{
	Student * temp;

	if (HeadOfABTree != NULL)
	{
		if (HeadOfABTree->name == name)
			return HeadOfABTree;
		else if (name > HeadOfABTree->name)
			temp = FindInBTree(name, HeadOfABTree->RSubBTree);
		else
			temp = FindInBTree(name, HeadOfABTree->LSubBTree);
		return temp;
	}
	else
		return NULL;
}

int FindInArray(long long name, Student group[])
{
	int i;
	for (i = 0; i < NUMBER; i++)
		if (group[i].name == name)
			return i;
	return -1;
}
