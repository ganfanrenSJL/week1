/*多项式ADT单链表实现加法、乘法、初始化零*/

//头文件

#include<stdio.h>
typedef struct Node *PtrToNode;
typedef int Element;

#ifndef _POLYNOMIAL_H
struct Node
{
	int Coefficient;
	int Exponent;
	PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial ZeroPolynomial(Polynomial Poly);
void InsertPolynomial(Element coefficient, Element exponent, Polynomial P);
Polynomial Finish(Polynomial Poly);
Polynomial Advance(Polynomial P);
Polynomial First(Polynomial Poly);
void AddPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolySum);
void MultPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolyProd);
void ListSort(Polynomial Poly);
void CombSimPolynomial(Polynomial Poly);
void print(const Polynomial Poly); 

#endif

//源文件

#include"head.h"
#include<stdio.h>
/*初始化为零*/
Polynomial ZeroPolynomial(Polynomial Poly)
{
	if(Poly==NULL)
		Poly = malloc(sizeof(struct Node));
	if (Poly == NULL)
		printf("初始化失败！！！");
	Poly->Next = NULL;
	return Poly;
}
/*在尾部插入,P为链表尾结点*/
void InsertPolynomial(Element coefficient,Element exponent, Polynomial P)
{
	Polynomial Tmp=malloc(sizeof(struct Node));
	Tmp->Coefficient = coefficient;
	Tmp->Exponent = exponent;
	Tmp->Next = NULL;
	P->Next = Tmp;
}
/*找到尾部节点*/
Polynomial Finish(Polynomial Poly)
{
	Polynomial P = Poly;
	while (P->Next != NULL)
	{
		P = P->Next;
	}
	return P;
}
Polynomial Advance(Polynomial P)
{
	return P->Next;
}
Polynomial First(Polynomial Poly)
{
	return Poly->Next;
}
void AddPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolySum)
{
	Polynomial P1=Poly1->Next, P2=Poly2->Next;
	Polynomial P = PolySum;
	while (P1 != NULL && P2 != NULL)
	{
		if (P1->Exponent < P2->Exponent)
		{
			InsertPolynomial(P1->Coefficient, P1->Exponent,P);
			P1=Advance(P1);
		}
		else if (P2->Exponent < P1->Exponent)
		{
			InsertPolynomial(P2->Coefficient, P2->Exponent, P);
			P2=Advance(P2);
		}
		else if (P2->Exponent = P1->Exponent)
		{
			InsertPolynomial((P1->Coefficient + P2->Coefficient), P1->Exponent, P);
			P1=Advance(P1);
			P2 = Advance(P2);
		}
		P = Advance(P);
	}
	while (P1 != NULL)
	{
		InsertPolynomial(P1->Coefficient, P1->Exponent, P);
		P1 = Advance(P1);
		P = Advance(P);
	}
	while (P2 != NULL)
	{
		InsertPolynomial(P2->Coefficient, P2->Exponent, P);
		P2 = Advance(P2);
		P = Advance(P);
	}
}
void MultPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolyProd)
{
	Polynomial P1 = Poly1->Next, P2 = Poly2->Next;
	Polynomial P = PolyProd;
	while (P1 != NULL)
	{
		while (P2 != NULL)
		{
			InsertPolynomial((P1->Coefficient*P2->Coefficient), (P1->Exponent + P2->Exponent), PolyProd);
			P2=Advance(P2);
			P = Advance(P);
		}
		P1=Advance(P1);
		P2=First(Poly2);
	}
	CombSimPolynomial(PolyProd);
}
void ListSort(Polynomial Poly)
{
	Polynomial P1=NULL, P2=NULL;
	Element coefficient, Exponent;
	for (P1 = Poly->Next; P1 != NULL; P1 = P1->Next)
	{
		for (P2 = P1->Next; P2 != NULL; P2 = P2->Next)
		{
			if (P1->Exponent > P2->Exponent)
			{
				coefficient = P1->Coefficient;
				P1->Coefficient = P2->Coefficient;
				P2->Coefficient = coefficient;
				Exponent = P1->Exponent;
				P1->Exponent = P2->Exponent;
				P2->Exponent = Exponent;
			}
		}
	}
}
void CombSimPolynomial(Polynomial Poly)
{
	Polynomial P1 = Poly->Next;
	Polynomial P2 = P1->Next;
	Polynomial P;
	ListSort(Poly);
	while (P1 != NULL)
	{
		if (P1->Exponent = P2->Exponent)
		{
			P1->Coefficient += P2->Coefficient;
			P = P2;
			P2=Advance(P2);
			free(P);
		}
		else
		{
			P1 = P1->Next;
			P2 = P2->Next;
		}
	}
}
void print(const Polynomial Poly)
{
	Polynomial P;
	for (P = Poly->Next; P->Next!= NULL; P = P->Next)
	{
		printf("%dx^%d + ", P->Coefficient, P->Exponent);
	}
	printf("%dx^%d\n", P->Coefficient,P->Exponent);
}
int main()
{
	Polynomial Poly1=malloc(sizeof(struct Node)), Poly2 = malloc(sizeof(struct Node));
	Polynomial PolySum = malloc(sizeof(struct Node)), PolyProd = malloc(sizeof(struct Node));
	ZeroPolynomial(Poly1);
	ZeroPolynomial(Poly2);
	ZeroPolynomial(PolySum);
	ZeroPolynomial(PolyProd);
	Element coefficient=0, exponent=0;
	Polynomial P1=Poly1, P2=Poly2;
	printf("请依次输入第一个多项式的系数和次数(每一组输入完成后回车，输入0结束):");
	while (1)
	{
		scanf_s("%d %d", &coefficient, &exponent);
		if (coefficient == 0)
			break;
		InsertPolynomial(coefficient, exponent, P1);
		P1 = Advance(P1);
	}
	printf("请依次输入第二个多项式的系数和次数(每一组输入完成后回车，输入0结束):");
	while (1)
	{
		scanf_s("%d %d", &coefficient, &exponent);
		if (coefficient == 0)
			break;
		InsertPolynomial(coefficient, exponent, P2);
		P2 = Advance(P2);
	}
	printf("两个多项式相加的结果为：\n");
	AddPolynomial(Poly1, Poly2, PolySum);
	print(PolySum);
	printf("两个多项式相乘的结果为：\n");
	MultPolynomial(Poly1, Poly2, PolyProd);
	print(PolyProd);
	return 0;
}
