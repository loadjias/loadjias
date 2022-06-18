#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1999
#define IV 1;
#define IA 2;
#define DV 3;
#define DA 4;

int n;
int AMatrix[MAX][MAX] = { 0 };
int changed[MAX][MAX] = { 0 };
int op1 = 0, op2 = 0;
//获取原邻接矩阵
void CreatMatrix()
{
	scanf_s("%d",&n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf_s("%d", &AMatrix[i][j]);
		}

	}
	getchar();
}
void InsertVex(int Vertex)
{
	//首先将原来的矩阵扩大
	int i, j;
	int prei, prej;
	for (prei = 0, i = 0; i < n + 1; i++)
	{
		if (i == Vertex)//要插入的位置直接continue留空
		{
			continue;
		}
		for (prej = 0,j = 0; j < n + 1; j++)
		{
			if (j == Vertex)//要插入的位置直接continue留空
			{	
				continue;
			}
			changed[i][j] = AMatrix[prei][prej];
			prej++;
		}
		prei++;
	}
	n++;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			AMatrix[i][j] = changed[i][j];
			changed[i][j] = 0;
		}
}
void InsertArc(int re, int de)
{
	AMatrix[re][de] = 1;
	AMatrix[de][re] = 1;
}
void DeleteVex(int vertex)
{
	int i, j, prei, prej;
	for (prei = 0,i = 0; prei < n; prei++)
	{	
		if (prei == vertex)
		{
			continue;
		}
		for (prej = 0, j = 0; prej < n; prej++)
		{
			if (prej == vertex)
			{
				continue;
			}
			changed[i][j] = AMatrix[prei][prej];
			j++;
		}
		i++;
	}
	n--;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			AMatrix[i][j] = changed[i][j];
			changed[i][j] = 0;
		}
}
void DeleteArc(int re, int de)
{
	AMatrix[re][de] = 0;
	AMatrix[de][re] = 0;
}
int OpType()
{
	char a1, a2;
	char s[20],s1[10],s2[10];
	int type = 1;
	while ((a1 = getchar()) != EOF)
	{	
		type = 1;
		int u = 0,i;
		int k1 = 0, k2 = 0;
		a2 = getchar();
		getchar();
		gets_s(s);
		//处理s
		for (i = 0; s[i] != '\0'; i++)
		{
			if (s[i] == ' ')
			{
				type++;
				s1[i] = '\0';
				continue;
			}
			if (type == 1)
			{
				s1[i] = s[i];
			}
			if (type == 2)
			{
				s2[u++] = s[i];
			}
		}
		if (type == 1)
			s1[i] = '\0';
		s2[u] = '\0';
		//printf("\nIns is %c%c,\n",a1,a2);
		//printf("s is %s,s1 is %s ,s2 is %s\n",s,s1,s2);
		while (s1[k1] != '\0')
			op1 += op1 * 10 + (s1[k1++] - '0');
		if (type == 2)
			while (s2[k2] != '\0')
				op2 += op2 * 10 + (s2[k2++] - '0');
		//printf("op1 = %d, op2 = %d\n",op1,op2);
		if (a1 == 'I' && a2 == 'V')
		{
			InsertVex(op1);
		}
		else if (a1 == 'I' && a2 == 'A')
		{	
			InsertArc(op1,op2);
		}
		else if (a1 == 'D' && a2 == 'V')
		{
			DeleteVex(op1);
		}
		else if (a1 == 'D' && a2 == 'A')
		{
			DeleteArc(op1, op2);
		}
		k1 = k2 = 0;
		op1 = op2 = 0;
	}
	return type;
}
void printM(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d",AMatrix[i][j]);
			if (j != n-1)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}
int main()
{
	CreatMatrix();
	OpType();
	printM(n);
}