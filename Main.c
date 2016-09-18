#include "Stack_Calc.h"   /* typedef的作用范围也只在本文件内  */
#include "Stack_Trans.h"
#include "Error.h"
#include "Def.h"   /* define的作用范围只在本文件内  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <memory.h>


#define STACK_TRANS_SIZE 128
#define STACK_CALC_SIZE 128  //两个栈所能容纳的字符数，不必太大
#define MAX_CHAR_SIZE 1024   //能够接受用户输入的字符数

int GetOp(char *StrFrom, char *Str);
int Calc(char *Str);
int TransInToPost(char *Str);
void PrintDetails(void);


static char StrPostfix[MAX_CHAR_SIZE];   /* 存放后缀表达式 */
static int PosOfStrPostfix = 0;


Stack_Trans S_Trans = NULL;       /* 整个运算过程需要用到两个栈 */
Stack_Calc S_Calc = NULL;

int main(int argc, char *argv[])
{
	int CalcRet;

	S_Trans = CreateStack_Trans(STACK_TRANS_SIZE);
	S_Calc = CreateStack_Calc(STACK_CALC_SIZE);

	PrintDetails();
	while (1)
	{
		//每次运算结束之后要做的操作
		memset(StrPostfix, 0, MAX_CHAR_SIZE);
		PosOfStrPostfix = 0;

		if (TransInToPost(StrPostfix) == ERROR)
			continue;
		//printf("%s\n", StrPostfix);
		if (EXIT == Calc(StrPostfix))
		{
			DisposeStack_Trans(S_Trans);
			DisposeStack_Calc(S_Calc);
			exit(0);
		}
	}
	
	exit(0);
}


/* 打印说明信息 */
void
	PrintDetails(void)
{
	putchar('\n');
	printf("-----------------------------------------------------------\n");
	printf("                         myCalc\n");
	printf("-----------------------------------------------------------\n");
	printf("Author : Xiang\n");
	printf("Date : 2012/3/24\n");
	printf("Description : + - * / %% ^ () sin cos tan log sqrt quit\n");
	printf("-----------------------------------------------------------\n");
}


/* 中缀表达式转换成后缀表达式 */
int
	TransInToPost(char *Str)
{
	int OpType;
	char *pszTop;
	char sTmp[64] = {0};

	
	while ( (OpType = GetOp("stdin" , sTmp)) != '\n' && OpType != '\0')
	{
		switch (OpType)
		{
			case NUMBER :
			{
				strcat(Str, sTmp);
				strcat(Str, " ");    /* 数字直接到输出 */
			}break;
			
			case '(' :
			{
				Push_Trans(sTmp, S_Trans);
			}break;

			case ')' :
			{
				pszTop = Top_Trans(S_Trans);
				while (strcmp(pszTop, "(" ) != 0)
				{
					pszTop = Pop_Trans(S_Trans);
					strcat(Str, pszTop);
					strcat(Str, " ");
					pszTop = Top_Trans(S_Trans);
				}
				Pop_Trans(S_Trans);
			}break;

			case '^' :
			{
				while ( strcmp(pszTop = Top_Trans(S_Trans), "^") == 0 )
				{
					pszTop = Pop_Trans(S_Trans);
					strcat(Str, pszTop);
					strcat(Str, " ");
				}
				Push_Trans(sTmp, S_Trans);
			}break;

			case FUN :
			{
				while ( strcmp(pszTop = Top_Trans(S_Trans), "^") == 0 || strcmp(pszTop, sTmp) == 0)
				{
					pszTop = Pop_Trans(S_Trans);
					strcat(Str, pszTop);
					strcat(Str, " ");
				}
				Push_Trans(sTmp, S_Trans);
			}break;
			
			case '*' :
			{
				while ( strcmp(pszTop = Top_Trans(S_Trans), "^") == 0 || strcmp(pszTop, "*") == 0 || \
				strcmp(pszTop, "/") == 0 || strcmp(pszTop, "%") == 0 || strlen(pszTop) > 1)
				{
					pszTop = Pop_Trans(S_Trans);
					strcat(Str, pszTop);
					strcat(Str, " ");
				}
				Push_Trans(sTmp, S_Trans);
			}break;

			case '/' :
			{
				while ( strcmp(pszTop = Top_Trans(S_Trans), "^") == 0 || strcmp(pszTop, "*") == 0 || \
				strcmp(pszTop, "/") == 0 || strcmp(pszTop, "%") == 0 || strlen(pszTop) > 1)
				{
					pszTop = Pop_Trans(S_Trans);
					strcat(Str, pszTop);
					strcat(Str, " ");
				}
				Push_Trans(sTmp, S_Trans);
			}break;

			case '%' :
			{
				while ( strcmp(pszTop = Top_Trans(S_Trans), "^") == 0 || strcmp(pszTop, "*") == 0 || \
				strcmp(pszTop, "/") == 0 || strcmp(pszTop, "%") == 0 || strlen(pszTop) > 1)
				{
					pszTop = Pop_Trans(S_Trans);
					strcat(Str, pszTop);
					strcat(Str, " ");
				}
				Push_Trans(sTmp, S_Trans);
			}break;

			case '+' :
			{
				while ( strcmp(pszTop = Top_Trans(S_Trans), "^") == 0 || strcmp(pszTop, "*") == 0 || \
				strcmp(pszTop, "/") == 0 || strcmp(pszTop, "%") == 0 || strcmp(pszTop, "+") == 0 || \
				strcmp(pszTop, "-") == 0 || strlen(pszTop) > 1)
				{
					pszTop = Pop_Trans(S_Trans);
					strcat(Str, pszTop);
					strcat(Str, " ");
				}
				Push_Trans(sTmp, S_Trans);
			}break;

			case '-' :
			{
				while ( strcmp(pszTop = Top_Trans(S_Trans), "^") == 0 || strcmp(pszTop, "*") == 0 || \
				strcmp(pszTop, "/") == 0 || strcmp(pszTop, "%") == 0 || strcmp(pszTop, "+") == 0 || \
				strcmp(pszTop, "-") == 0 || strlen(pszTop) > 1)
				{
					pszTop = Pop_Trans(S_Trans);
					strcat(Str, pszTop);
					strcat(Str, " ");
				}
				Push_Trans(sTmp, S_Trans);
			}break;

			default :
			{
				Error(ILLEGAL_OP);
				return ERROR; //这里直接返回，Error函数中已经把两个栈都清空了
			}break;
		}
	}
	while (IsEmpty_Trans(S_Trans) == FALSE)
	{
		pszTop = Pop_Trans(S_Trans);
	 	strcat(Str, pszTop);
	 	strcat(Str, " ");
	}

	return TRUE;
}



/* 计算后缀表达式 */
static double Calc_Fun(char *sType, double Op);   //此函数用于处理函数

int
	Calc(char *Str)
{
	int OpType;
	char sTmp[64];
	double Op2, dTmp;

	while ( (OpType = GetOp(Str, sTmp)) != '\0' && OpType != '\n')
	{
		switch (OpType)
		{
			case NUMBER :
			{
				Push_Calc(atof(sTmp), S_Calc);
			}break;

			case FUN :
			{
				if (strcmp(sTmp, "quit") == 0)
				{
					return EXIT;
				}

				dTmp = Calc_Fun(sTmp, Pop_Calc(S_Calc));
				Push_Calc(dTmp, S_Calc);
			}break;

			case '+' :
			{
				Push_Calc(Pop_Calc(S_Calc) + Pop_Calc(S_Calc), S_Calc);
			}break;

			case '*' :
			{
				Push_Calc(Pop_Calc(S_Calc) * Pop_Calc(S_Calc), S_Calc);
			}break;

			case '-' :
			{
				Op2 = Pop_Calc(S_Calc);
				Push_Calc(Pop_Calc(S_Calc) - Op2, S_Calc);
			}break;

			case '/' :
			{
				Op2 = Pop_Calc(S_Calc);
				if (Op2 != 0.0)
				{
					Push_Calc(Pop_Calc(S_Calc) / Op2, S_Calc);
				}
				else
				{
					Error(ZERO_DIVIDER);
					return ERROR;
				}
			}break;

			case '^' :
			{
				Op2 = Pop_Calc(S_Calc);
				Push_Calc( pow(Pop_Calc(S_Calc), Op2), S_Calc);
			}break;

			case '%' :
			{
				Op2 = Pop_Calc(S_Calc);
				if (Op2 != 0.0)
				{
					Push_Calc( fmod(Pop_Calc(S_Calc), Op2), S_Calc);
				}
				else
				{
					Error(ZERO_DIVIDER);
					return ERROR;
				}
			}break;
			
			default :
			{
				Error(UNKNOWN_COMMAND);
				return ERROR;
			}break;
		}
	}

	if (S_Calc->TopOfStack != 1)
	{
		Error(BAD_EXPRESSION);
		return ERROR;
	}
	else
	{
		printf("\t\t = %.6lf\n", Pop_Calc(S_Calc));
	}

	return TRUE;
}

static double
	Calc_Fun(char *sType, double Op)
{
	if (strcmp(sType, "sin") == 0)
		return sin(Op);
	else if (strcmp(sType, "cos") == 0)
		return cos(Op);
	else if (strcmp(sType, "tan") == 0)
		return tan(Op);
	else if (strcmp(sType, "log") == 0)
	{
		if (Op <= 0)
		{
			Error(ERROR_LOG);
			return (double)ERROR;
		}
		else
			return log(Op);
	}
	else if (strcmp(sType, "sqrt") == 0)
	{
		if (Op < 0)
		{
			Error(ERROR_SQRT);
			return (double)ERROR;
		}
		else
			return sqrt(Op);
	}
	else if (strcmp(sType, "quit") == 0)
	{
		return (double)EXIT;
	}
	else
	{
		Error(UNKNOWN_COMMAND);
		return (double)ERROR;
	}
}


/* 从标准输入或者字符串读取运算单元 */
static int Getch(char *StrFrom);
static void unGetch(char c);

int
	GetOp(char *StrFrom, char *Str)
{
	int i = 0, c;

	/* 去掉前面的空格 */
	while ( (Str[0] = c = Getch(StrFrom) ) == ' ' || c == '\t')
		;
	Str[1] = '\0';
	
	/* 表示读入结束了 */
	if (c == '\n' || c == '\0')   // \n的情况用与从stdin读数据到StrPostfix
		return c;

	/* 如果是 + * / % ^ 就返回, -有可能是负号，所以单独讨论 */
	if (!isalnum(c) && c != '.' && c != 'e' && c != '-')
	{
		return c;
	}

	/* 如果是小写字母但不是‘e’就说明是函数 */
	if (c != 'e' && islower(c))
	{
		while (islower(Str[++i] = c = Getch(StrFrom) ) )
			;
		unGetch(c);
		Str[i] = '\0';
		return FUN;
	}

	if (c == '-')
	{
		if ( (c = Getch(StrFrom) ) == ' ' || c == '\t' || c == '-') 
		{
			unGetch(c);
			return '-';   /* 是减号  */
		}
		else
		{
			unGetch(c);
		}
	}
	
	if (isdigit(c))
	{
		while (isdigit(Str[++i] = c = Getch(StrFrom) ) )
			;
	}

	if (c == '.')
	{
		while (isdigit(Str[++i] = c = Getch(StrFrom) ) )
			;
	}

	if (c == 'e')
	{
		while (isdigit(Str[++i] = c = Getch(StrFrom) ) )
			;
	}

	unGetch(c);
	Str[i] = '\0';

	return NUMBER;
}


/* 输入缓冲，可以从字符串或者标准输入读取数据 */

#define BUFSIZE 10

char Buf[BUFSIZE];
int Bufp = 0;

int 
	Getch(char *StrFrom)
{

	if (strcmp(StrFrom, "stdin") == 0)
	{
		return (Bufp > 0) ? Buf[--Bufp] : getchar();
	}
	else
	{
		return (Bufp > 0) ? Buf[--Bufp] : StrFrom[PosOfStrPostfix++];
	}

}

void unGetch(char c)
{
	Buf[Bufp++] = c;
}



/* 错误处理 */
void
	FatalError(char *Str)
{
	printf("%s", Str);
	exit(1);
}

void
	Error(int ErrorNumber)
{
	switch (ErrorNumber)
	{
		case EMPTY_STACK_CALC :
		{
			printf("\t\tCalcStack is empty!\n");	
		}break;

		case ILLEGAL_OP :
		{
			printf("\t\tSome characters are illegal!\n");
		}break;

		case UNKNOWN_COMMAND :
		{
			printf("\t\tUnknown command or function!\n");

		}break;

		case BAD_EXPRESSION :
		{
			printf("\t\tCalcStack is not empty after calculate!\n");	
		}break;

		case ZERO_DIVIDER :
		{
			printf("\t\tDivider is zero! Your expression is illegal!!!\n");	
		}break;

		case ERROR_LOG :
		{
			printf("\t\tLog number must be above zero!\n");	
		}break;

		case ERROR_SQRT :
		{
			printf("\t\tSqrt number must be not below zero!\n");
		}break;

		default :
		break;
	}
	printf("\t\tThe result may not be correct!!!\n");
	MakeEmpty_Trans(S_Trans);
	MakeEmpty_Calc(S_Calc);
}
