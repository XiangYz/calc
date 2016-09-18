#ifndef _Stack_Calc_h

#define _Stack_Calc_h


struct Stack_CalcRecord;
typedef struct Stack_CalcRecord *Stack_Calc;
typedef double ElementType_Calc;

int IsEmpty_Calc(Stack_Calc S);
int IsFull_Calc(Stack_Calc S);
Stack_Calc CreateStack_Calc(int MaxElements);
void DisposeStack_Calc(Stack_Calc S);
void MakeEmpty_Calc(Stack_Calc S);
void Push_Calc(ElementType_Calc X, Stack_Calc S);
ElementType_Calc Pop_Calc(Stack_Calc S);
ElementType_Calc Top_Calc(Stack_Calc S);


struct Stack_CalcRecord
{
	int Capacity;
	int TopOfStack;
	ElementType_Calc *Array;
};

#endif
