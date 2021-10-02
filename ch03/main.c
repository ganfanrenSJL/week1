/*简单数组多项式ADT实现加法、乘法、初始化为零*/

//头文件

#include<stdio.h>
#include<stdlib.h>
#define MaxDegree 10

typedef struct
{
	int CoeffArray[MaxDegree + 1];
	int HighPower;
}*Polynomial;

void ZeroPolynomial(Polynomial Poly);
void AddPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolySum);
void MultPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolyProd);
void print(const Polynomial Poly);

//源文件

#include<stdio.h>
#include"head.h"
#include<errno.h>

void ZeroPolynomial(Polynomial Poly)
{
	int i;
	for (i = 0; i <= MaxDegree; i++)
	{
		Poly->CoeffArray[i] = 0;
	}
	Poly->HighPower = 0;
}
void AddPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolySum)
{
	int i;
	ZeroPolynomial(PolySum);
	PolySum->HighPower = max(Poly1->HighPower, Poly2->HighPower);
	for (i=PolySum->HighPower; i>=0;i--)
	{
		PolySum->CoeffArray[i] = Poly1->CoeffArray[i] + Poly2->CoeffArray[i];
	}
}
void MultPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolyProd)
{
	int i,j;
	ZeroPolynomial(PolyProd);
	PolyProd->HighPower = Poly1->HighPower + Poly2->HighPower;
	if (PolyProd->HighPower > MaxDegree)
		perror("Exceeded array size");//错误提示，不要忘记
	else
	{
		for (i = 0; i <= Poly1->HighPower; i++)
		{
			for (j = 0; j <= Poly2->HighPower; j++)
			{
				PolyProd->CoeffArray[i + j] += Poly1->CoeffArray[i] * Poly2->CoeffArray[j];//注意是+=
			}
		}
	}
}
void print(const Polynomial Poly)
{
	int i;
	for (i = 0; i <= Poly->HighPower-1; i++)
	{
		if (Poly->CoeffArray[i] == 0)
			printf("");
		else
			printf("%dx^%d + ", Poly->CoeffArray[i], i);
	}
	printf("%dx^%d\n", Poly->CoeffArray[Poly->HighPower], Poly->HighPower);
}
int main()
{
	Polynomial Poly1=malloc(sizeof(int)*(MaxDegree+2)), Poly2= malloc(sizeof(int)*(MaxDegree + 2));
	ZeroPolynomial(Poly1);
	ZeroPolynomial(Poly2);
	Polynomial PolySum= malloc(sizeof(int)*(MaxDegree + 2)), PolyProd= malloc(sizeof(int)*(MaxDegree + 2));
	ZeroPolynomial(PolySum);
	ZeroPolynomial(PolyProd);
	int len1, len2;
	int i;
	printf("请输入第一个多项式的最高次数:");
	scanf_s("%d", &len1);
	Poly1->HighPower = len1;
	printf("请依次输入该多项式的系数(从0-%d):", len1);
	for (i = 0; i <= len1; i++)
	{
		scanf_s("%d", &Poly1->CoeffArray[i]);
	}
	printf("请输入第二个多项式的最高次数:");
	scanf_s("%d", &len2);
	Poly2->HighPower = len2;
	printf("请依次输入该多项式的系数(从0-%d):", len2);
	for (i = 0; i <= len2; i++)
	{
		scanf_s("%d", &Poly2->CoeffArray[i]);
	}
	printf("两个多项式相加的结果为：\n");
	AddPolynomial(Poly1, Poly2, PolySum);
	print(PolySum);
	printf("两个多项式相乘的结果为：\n");
	MultPolynomial(Poly1, Poly2, PolyProd);
	print(PolyProd);
	return 0;
}
