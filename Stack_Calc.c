#include <stdio.h>
#include <malloc.h>
#include "Stack_Calc.h"
#include "Error.h"
#include "Def.h"

/*
struct Stack_CalcRecord
{
	int Capacity;
	int TopOfStack;
	ElementType_Calc *Array;
};
*/

int 
IsEmpty_Calc(Stack_Calc S)
{
	if (NULL != S)
	{
		if (S->TopOfStack == 0)
			return TRUE;		
		else
			return FALSE;
	}
	else 
		return ERROR;
}

int 
IsFull_Calc(Stack_Calc S)
{
	if (NULL != S)
	{
		if (S->TopOfStack == S->Capacity)
			return TRUE;
		else
			return FALSE;
	}
	else
		return ERROR;
}

Stack_Calc
CreateStack_Calc(int MaxElements)
{
	Stack_Calc S = NULL;

	S = malloc(sizeof (Stack_Calc));
	if (NULL == S)
	{
		FatalError("Stack_Calc create : Cannot allocate more space for S!!!\n");
	}
	S->Capacity = MaxElements;
	S->TopOfStack = 0;
	S->Array = malloc(sizeof (ElementType_Calc) * S->Capacity);
	if (NULL == S->Array)
	{
		FatalError("Stack_Calc create : Cannot allocate more space for S->Array!!!\n");
	}

	return S;
}

void
DisposeStack_Calc(Stack_Calc S)
{
	if (NULL != S)
	{
		free(S->Array);
		free(S);
	}
}

void
MakeEmpty_Calc(Stack_Calc S)
{
	/*
	while (IsEmpty_Calc(S) == FALSE)
	{
		Pop_Calc(S);
	}
	*/
	S->TopOfStack = 0;
}

void
Push_Calc(ElementType_Calc X, Stack_Calc S)
{
	if (IsFull_Calc(S) == TRUE)
	{
		Error(FULL_STACK_CALC);
	}
	
	else
	{
		S->Array[S->TopOfStack++] = X;
	}

}

ElementType_Calc
Pop_Calc(Stack_Calc S)
{
	if (IsEmpty_Calc(S) == TRUE)
	{
		Error (EMPTY_STACK_CALC);
		return 0.0;
	}
	else
	{
		return S->Array[--S->TopOfStack];
	}
}

ElementType_Calc
Top_Calc(Stack_Calc S)
{
	if (IsEmpty_Calc(S) == TRUE)
	{
		Error(EMPTY_STACK_CALC);
		return 0;
	}
	return S->Array[S->TopOfStack - 1];
}
