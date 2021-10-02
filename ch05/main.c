/*栈ADT链表实现*/

//头文件

#include<stdio.h>
#include<stdlib.h>

#ifndef _STACK_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;

int IsEmpty(Stack S);
Stack CreateStack(void);
void DisPoseStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType x, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);

#endif

struct Node
{
	ElementType Element;
	PtrToNode Next;
};

//源文件

#include"head.h"
#include<stdio.h>
#include<errno.h>

/*判断栈是否为空*/
int IsEmpty(Stack S)
{
	return S->Next == NULL;
}
/*创建栈*/
Stack CreateStack(void)
{
	Stack S;
	S = malloc(sizeof(struct Node));
	if (S == NULL)
		printf("Out Of Space!");
	S->Next = NULL;
	MakeEmpty(S);//为什么？
	return S;
}
/*销毁栈*/
void DisPoseStack(Stack S)
{
	PtrToNode Tmp= S->Next;
	while (S!= NULL)
	{
		free(S);
		S = Tmp;
		Tmp = Tmp->Next;
	}
	return NULL;
}
/*清空栈*/
void MakeEmpty(Stack S)
{
	if (S == NULL)
		printf("Must use CreateStack first");
	else
		while (!IsEmpty(S))
			Pop(S);
}
/*压栈*/
void Push(ElementType x, Stack S)
{
	PtrToNode TmpCell;
	TmpCell = malloc(sizeof(struct Node));
	if (TmpCell == NULL)
		printf("Out Of Space!");
	else
	{
		TmpCell->Element = x;
		TmpCell->Next = S->Next;
		S->Next = TmpCell;
	}
}
/*返回栈顶*/
ElementType Top(Stack S)
{
	if (!IsEmpty(S))
	{
		return S->Next->Element;
	}
	else
	{
		perror("Empty stack");
		return 0;
	}
}
/*出栈*/
void Pop(Stack S)
{
	PtrToNode Tmp;
	Tmp = S->Next;
	S->Next = S->Next->Next;
	free(Tmp);
}
int main()
{
	printf("创建栈\n");
	Stack S=CreateStack();
	printf("依次压栈\n");
	Push(1, S);
	Push(5, S);
	Push(4, S);
	Push(3, S);
	printf("压栈完成\n");
	printf("依次出栈\n");
	Pop(S);
	Pop(S);
	Pop(S);
	Pop(S);
	if (IsEmpty(S) == 1)
		printf("栈为空\n");
	else
		printf("栈非空\n");
	return 0;
}
