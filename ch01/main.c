//头文件
#include<stdlib.h>
#include<stdio.h>
#ifndef _List_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(ElementType x, List L);
void Delete(ElementType x, List L);
Position FindPrevious(ElementType x, List L);
void Insert(ElementType x, List L, Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
int Retrieve(Position P);
Position AccordingNum(int num, List L);
void print(List L);
#endif

struct Node
{
	int Element;
	Position Next;
};

//main.c

#include"标头.h"
#include<stdio.h>
#include<stdlib.h>
/*创建空链表*/
List MakeEmpty(List L)
{
	L = malloc(sizeof(struct Node));
	L->Next = NULL;
	return L;
}
/*判断链表是否为空*/
int IsEmpty(List L)
{
	return L->Next == NULL;
}
/*判断是否为最后一个结点*/
int IsLast(Position P, List L)
{
	return P->Next == NULL;
}
/*返回某个元素的位置*/
Position Find(ElementType x, List L)
{
	Position P = L->Next;
	while (P != NULL && P->Element != x)
	{
		P = P->Next;
	}
	return P;
}
/*删除某个元素*/
void Delete(ElementType x, List L)
{
	Position P, TmpCell;
	P= FindPrevious(x, L);
	if (!IsLast(P,L))
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}
/*找到某个元素的前驱位置*/
Position FindPrevious(ElementType x, List L)
{
	Position P = L;
	if (P->Next != NULL && P->Next->Element != x)
	{
		P = P->Next;
	}
	return P;
}
/*在某个位置后插入某个元素*/
void Insert(ElementType x, List L, Position P)
{
	Position TmpCell;
	//P = FindPrevious(x, L);
	TmpCell = malloc(sizeof(struct Node));
	if (TmpCell == NULL)
	{
		printf("Out Of Space!!!");
	}
	TmpCell->Element = x;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}
/*删除链表*/
void DeleteList(List L)
{
	Position P,Tmp;
	P = L->Next;
	L->Next = NULL;
	while (P != NULL)
	{
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
}
/*返回头结点*/
Position Header(List L)
{
	return L;
}
/*返回第一个结点*/
Position First(List L)
{
	return L->Next;
}
/*返回某个结点的后驱结点*/
Position Advance(Position P)
{
	return P->Next;
}
/*返回某结点的值*/
int Retrieve(Position P)
{
	return P->Element;
}
/*返回某个位置的结点（假设头结点为0位置）*/
Position AccordingNum(int num,List L)
{
	int i;
	Position P = L->Next;
	for (i=1; i <num; i++)
	{
		P = P->Next;
	}
	return P;
}
/*遍历打印链表*/
void print(List L)
{
	Position P = L->Next;
	while (P != NULL)
	{
		printf("%d  ", P->Element);
		P = P->Next;
	}
}
int main()
{
	int len, element;
	int i;
	List L = malloc(sizeof(struct Node));
	printf("请输入链表的长度：");
	scanf_s("%d", &len);
	printf("请依次输入链表中存取的数据：");
	Position P = L;
	for (i = 0; i < len; i++)
	{
		scanf_s("%d", &element);
		Position TmpCell = malloc(sizeof(struct Node));
		TmpCell->Element = element;
		TmpCell->Next = NULL;
		P->Next = TmpCell;
		P = TmpCell;
	}
	printf("链表已初始化成功！！!\n");
	if (!IsEmpty(L))printf("链表非空\n");
	else printf("链表为空\n");
	printf("第三个位置的元素为%d\n", Retrieve(AccordingNum(3,L)));
	printf("输入想要返回位置的元素：");
	scanf_s("%d", &element);
	Position Pot=Find(element, L);
	printf("在该元素后插入8\n");
	Insert(8,L, Pot);
	printf("遍历打印链表:");
	print(L);
	return 0;
}
