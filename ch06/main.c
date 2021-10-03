/*栈ADT数组实现（更流行，因为栈一般长度不长，定义一个不越界数组大小简单）*/

//头文件

#include<stdio.h>
#include<stdlib.h>
#define EmptyTOS -1
#define MinStackSize 5
#ifndef _STACK_H

struct StackRecord;
typedef struct StackRecord *Stack;//结构体的指针
typedef int ElementType;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisPoseStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType x, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);

#endif

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};

//源文件

#include"head.h"
#include<stdio.h>
#include<errno.h>

/*判断栈是否为空*/
int IsEmpty(Stack S)
{
	return S->TopOfStack == -1;
}
/*判断栈是否已满*/
int IsFull(Stack S)
{
	return S->Capacity == S->TopOfStack + 1;//不确定
}
/*创建栈*/
Stack CreateStack(int MaxElements)
{
	Stack S;
	if (MaxElements < MinStackSize)
		printf("Stack size is too small");
	S = malloc(sizeof(struct StackRecord));
	if (S == NULL)
		printf("Out of space!!");
	S->Array = malloc(sizeof(ElementType)*MaxElements);
	if (S->Array == NULL)
		printf("Out of spacae!!");
	S->Capacity = MaxElements;
	MakeEmpty(S);
	return S;
}
/*销毁栈*/
void DisPoseStack(Stack S)
{
	if (S != NULL)
	{
		free(S->Array);
		free(S);
	}
}
/*创建空栈*/
void MakeEmpty(Stack S)
{
	S->TopOfStack = EmptyTOS;
}
/*压栈*/
void Push(ElementType x, Stack S)
{
	if (IsFull(S))
		printf("Full stack");
	else
		S->Array[++S->TopOfStack] = x;
}
/*返回栈顶*/
ElementType Top(Stack S)
{
	if (!IsEmpty(S))
		return S->Array[S->TopOfStack];
	printf("Empty stack");
	return 0;
}
/*出栈*/
void Pop(Stack S)
{
	if (IsEmpty(S))
		printf("Empty stack");
	else
		S->TopOfStack--;

}
/*返回栈顶元素并出栈*/
ElementType TopAndPop(Stack S)
{
	if (!IsEmpty(S))
		return S->Array[S->TopOfStack--];
	printf("Empty stack");
	return 0;
}
int main()
{
	printf("创建栈\n");
	Stack S=CreateStack(5);
	printf("建栈成功\n");
	printf("依次压栈\n");
	Push(1, S);
	Push(5, S);
	Push(4, S);
	Push(3, S);
	Push(2, S);
	printf("压栈完成\n");
	if (IsFull(S) == 1)
		printf("栈已满\n");
	else
		printf("栈不满\n");
	printf("依次出栈\n");
	Pop(S);
	Pop(S);
	Pop(S);
	Pop(S);
	printf("栈顶元素为%d\n", TopAndPop(S));
	if (IsEmpty(S) == 1)
		printf("栈为空\n");
	else
		printf("栈非空\n");
	return 0;
}
