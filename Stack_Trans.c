#include <stdio.h>  /* NULL好像在这个文件中被定义 */
#include <malloc.h>
#include <string.h>
#include "Stack_Trans.h"
#include "Error.h"
#include "Def.h"


int 
	IsEmpty_Trans(Stack_Trans S)
{
	if ( NULL != S)
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
	IsFull_Trans(Stack_Trans S)
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

Stack_Trans
	CreateStack_Trans(int MaxElements)
{
	Stack_Trans S = NULL;

	S = malloc(sizeof (Stack_Trans));
	if (NULL == S)
	{
		FatalError("Stack_Trans create : Cannot allocate more space for S!!!\n");
	}
	S->Capacity = MaxElements;
	S->TopOfStack = 0;
	S->Array = malloc(sizeof (ElementType_Trans) * S->Capacity);
	if (NULL == S->Array)
	{
		FatalError("Stack_Trans create : Cannot allocate more space for S->Array!!!\n");
	}

	return S;
}

void
	DisposeStack_Trans(Stack_Trans S)
{
	if (NULL != S)
	{
		free(S->Array);
		free(S);
	}
}

void
	MakeEmpty_Trans(Stack_Trans S)
{
	/*
	while (IsEmpty_Trans(S) != TRUE)
	{
		Pop_Trans(S);
	}
	*/
	S->TopOfStack = 0;
}

void
	Push_Trans(ElementType_Trans X, Stack_Trans S)
{
	if (IsFull_Trans(S) == TRUE)
	{
		Error(FULL_STACK_TRANS);
	}
	
	else
	{
		S->Array[S->TopOfStack] = malloc( (strlen(X) + 1) * sizeof (char));
		if (NULL == S->Array[S->TopOfStack])
			FatalError("Push_Trans : Cannot allocate more space!!!\n");
		strcpy(S->Array[S->TopOfStack++], X);
	}

}

ElementType_Trans
	Pop_Trans(Stack_Trans S)
{
	if (IsEmpty_Trans(S) == TRUE)
	{
		Error (EMPTY_STACK_TRANS);
	}
	else
	{
		return S->Array[--S->TopOfStack];
	}
}

ElementType_Trans
	Top_Trans(Stack_Trans S)
{
	if (IsEmpty_Trans(S) == TRUE)
	{
		return "";
	}
	return S->Array[S->TopOfStack - 1];
}

