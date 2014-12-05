/*
 * main.c
 *
 *   Created on: 2014年12月3日
 *       Author: Saigut
 *  Description: 二叉排序树的实现
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct bTree
{
	int value;
	struct bTree * LSubBTree;
	struct bTree * RSubBTree;
} BTree;

BTree * Head = NULL;

//判断是否为二叉排序树
int JudgeOfSortedBTreeR(BTree * HeadOfABTree);
void JudgeOfSortedBTree(BTree * HeadOfABTree);

//添加
void AddR(int value, BTree * HeadOfABTree);
void Add(int value, BTree * HeadOfABTree);

//删除结点
int DeleteR(int value, BTree * HeadOfABTree, BTree * PNode, int SubBTreeFlag);
void Delete(int value, BTree * HeadOfABTree);
//最左节点
BTree * LeftEndOfBTree(BTree * HeadOfABTree);

//显示树
void DisplayBTreeR(BTree * HeadOfABTree, int SubBTreeFlag);
void DisplayBTree(BTree * HeadOfABTree);

//删除树
void DeleteTheBTree(BTree * HeadOfABTree);

//三种非递归遍历
void PreOrderN(BTree * HeadOfABTree);
void InOrderN(BTree * HeadOfABTree);
void PostOrderN(BTree * HeadOfABTree);

int depth = -4;

int main(void)
{
	puts("   二叉排序树的实现\n");

	puts("生成：");
	Add(50, Head);
	Add(25, Head);
	Add(75, Head);
	Add(12, Head);
	Add(38, Head);
	Add(62, Head);
	Add(88, Head);
	Add(6, Head);
	Add(18, Head);
	Add(31, Head);
	Add(44, Head);
	Add(56, Head);
	Add(68, Head);
	Add(81, Head);
	Add(94, Head);
	DisplayBTree(Head);

	puts("");
	puts("添加：");
	Add(80, Head);
	Add(23, Head);
	DisplayBTree(Head);

	puts("");
	puts("删除结点：");
	Delete(38, Head);
	Delete(56, Head);
	DisplayBTree(Head);

	puts("\n");
	puts("判断是否为排序二叉树：");
	JudgeOfSortedBTree(Head);

	puts("\n");
	puts("先序遍历：");
	PreOrderN(Head);
	puts("");
	puts("中序遍历：");
	InOrderN(Head);
	puts("");
	puts("后序遍历：");
	PostOrderN(Head);

	puts("\n");
	puts("删除树：");
	DeleteTheBTree(Head);
	Head = NULL;
	DisplayBTree(Head);

	return 0;
}

int JudgeOfSortedBTreeR(BTree * HeadOfABTree)
{
	//0表示符合，1表示不符
	if (HeadOfABTree != NULL)
	{
		if ((HeadOfABTree->LSubBTree != NULL)
				&& ((HeadOfABTree->LSubBTree->value > HeadOfABTree->value)
						|| (JudgeOfSortedBTreeR(HeadOfABTree->LSubBTree) == 1)))
			return 1;
		else
		{
			if ((HeadOfABTree->RSubBTree != NULL)
					&& ((HeadOfABTree->RSubBTree->value <= HeadOfABTree->value)
							|| (JudgeOfSortedBTreeR(HeadOfABTree->RSubBTree) == 1)))
				return 1;
			else
				return 0;
		}
	}
	else
		return 0;
}

void JudgeOfSortedBTree(BTree * HeadOfABTree)
{
	if (JudgeOfSortedBTreeR(HeadOfABTree) == 0)
		printf("它是二叉树。\n");
	else
		printf("它不是二叉树。\n");
}

void AddR(int value, BTree * HeadOfABTree)
{
	if (value > HeadOfABTree->value)
	{
		if (HeadOfABTree->RSubBTree == NULL)
		{
			HeadOfABTree->RSubBTree = (BTree *) malloc(sizeof(BTree));
			HeadOfABTree->RSubBTree->value = value;
			HeadOfABTree->RSubBTree->LSubBTree = NULL;
			HeadOfABTree->RSubBTree->RSubBTree = NULL;
		}
		else
			Add(value, HeadOfABTree->RSubBTree);
	}
	else
	{
		if (HeadOfABTree->LSubBTree == NULL)
		{
			HeadOfABTree->LSubBTree = (BTree *) malloc(sizeof(BTree));
			HeadOfABTree->LSubBTree->value = value;
			HeadOfABTree->LSubBTree->LSubBTree = NULL;
			HeadOfABTree->LSubBTree->RSubBTree = NULL;
		}
		else
			Add(value, HeadOfABTree->LSubBTree);
	}
}

void Add(int value, BTree * HeadOfABTree)
{
	if (HeadOfABTree == NULL)
	{
		Head = (BTree *) malloc(sizeof(BTree));
		Head->value = value;
		Head->LSubBTree = NULL;
		Head->RSubBTree = NULL;
	}
	else
		AddR(value, HeadOfABTree);
}

int DeleteR(int value, BTree * HeadOfABTree, BTree * PNode, int SubBTreeFlag)
{
	if (HeadOfABTree != NULL && HeadOfABTree->value == value)
	{
		if (HeadOfABTree->RSubBTree != NULL)
		{
			//左子树接到右子树
			LeftEndOfBTree(HeadOfABTree->RSubBTree)->LSubBTree =
					HeadOfABTree->LSubBTree;

			//子树接到父结点。后同
			if (SubBTreeFlag == 1)
				PNode->LSubBTree = HeadOfABTree->RSubBTree;
			else
				PNode->RSubBTree = HeadOfABTree->RSubBTree;

		}
		else
		{
			if (SubBTreeFlag == 1)
				PNode->LSubBTree = HeadOfABTree->LSubBTree;
			else
				PNode->RSubBTree = HeadOfABTree->LSubBTree;
		}

		//释放内存
		free(HeadOfABTree);
		return 0;
	}
	else if (HeadOfABTree == NULL)
		return 1;
	else if (DeleteR(value, HeadOfABTree->LSubBTree, HeadOfABTree, 1) == 0)
		return 0;
	else if (DeleteR(value, HeadOfABTree->RSubBTree, HeadOfABTree, 2) == 0)
		return 0;
	else
		return 1;
}

void Delete(int value, BTree * HeadOfABTree)
{
	if (HeadOfABTree != NULL)
	{
		if (HeadOfABTree->value != value)
			DeleteR(value, HeadOfABTree, NULL, 0);
		else
		{
			if (HeadOfABTree->RSubBTree != NULL)
			{
				LeftEndOfBTree(HeadOfABTree->RSubBTree)->LSubBTree =
						HeadOfABTree->LSubBTree;

				Head = HeadOfABTree->RSubBTree;
			}
			else
				Head = HeadOfABTree->LSubBTree;
			free(HeadOfABTree);

		}
	}
}

BTree * LeftEndOfBTree(BTree * HeadOfABTree)
{
	if (HeadOfABTree->LSubBTree == NULL)
		return HeadOfABTree;
	else
		return LeftEndOfBTree(HeadOfABTree->LSubBTree);
}

void DisplayBTreeR(BTree * HeadOfABTree, int SubBTreeFlag)
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
	printf("%d", HeadOfABTree->value);
	puts("");

	if (HeadOfABTree->LSubBTree != NULL)
		DisplayBTreeR(HeadOfABTree->LSubBTree, 1);
	else if (HeadOfABTree->RSubBTree != NULL)
		puts("");

	depth -= 4;
}

void DisplayBTree(BTree * HeadOfABTree)
{
	if (HeadOfABTree != NULL)
		DisplayBTreeR(HeadOfABTree, 0);
}

void DeleteTheBTree(BTree * HeadOfABTree)
{
	if (HeadOfABTree != NULL)
	{
		DeleteTheBTree(HeadOfABTree->LSubBTree);
		DeleteTheBTree(HeadOfABTree->RSubBTree);
		free(HeadOfABTree);
	}
}

void PreOrderN(BTree * HeadOfABTree)
{
	BTree *St[200], *p;
	int top = -1;
	if (HeadOfABTree != NULL)
	{
		top++;
		St[top] = HeadOfABTree;
		while (top > -1)
		{
			p = St[top];
			top--;
			printf("%d ", p->value);
			if (p->RSubBTree != NULL)
			{
				top++;
				St[top] = p->RSubBTree;
			}
			if (p->LSubBTree != NULL)
			{
				top++;
				St[top] = p->LSubBTree;
			}
		}
		puts("");
	}
}

void InOrderN(BTree * HeadOfABTree)
{
	BTree *St[200], *p;
	int top = -1;
	if (HeadOfABTree != NULL)
	{
		p = HeadOfABTree;
		while (top > -1 || p != NULL)
		{
			while (p != NULL)
			{
				top++;
				St[top] = p;
				p = p->LSubBTree;
			}

			if (top > -1)
			{
				p = St[top];
				top--;
				printf("%d ", p->value);
				p = p->RSubBTree;
			}
		}
		puts("");
	}
}

void PostOrderN(BTree * HeadOfABTree)
{
	BTree *St[200], *p;
	int flag, top = -1;
	if (HeadOfABTree != NULL)
	{
		do
		{
			while (HeadOfABTree != NULL)
			{
				top++;
				St[top] = HeadOfABTree;
				HeadOfABTree = HeadOfABTree->LSubBTree;
			}

			p = NULL;
			flag = 1;
			while (top != -1 && flag)
			{
				HeadOfABTree = St[top];
				if (HeadOfABTree->RSubBTree == p)
				{
					printf("%d ", HeadOfABTree->value);
					top--;
					p = HeadOfABTree;
				}
				else
				{
					HeadOfABTree = HeadOfABTree->RSubBTree;
					flag = 0;
				}
			}
		} while (top != -1);
		puts("");
	}
}
