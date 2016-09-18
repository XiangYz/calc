#ifndef _Stack_Trans_h

#define _Stack_Trans_h

struct Stack_TransRecord;
typedef struct Stack_TransRecord *Stack_Trans;
typedef char * ElementType_Trans;

int IsEmpty_Trans(Stack_Trans S);
int IsFull_Trans(Stack_Trans S);
Stack_Trans CreateStack_Trans(int MaxElements);
void DisposeStack_Trans(Stack_Trans S);
void MakeEmpty_Trans(Stack_Trans S);
void Push_Trans(ElementType_Trans X, Stack_Trans S);
ElementType_Trans Pop_Trans(Stack_Trans S);
ElementType_Trans Top_Trans(Stack_Trans S);

struct Stack_TransRecord
{
	int Capacity;
	int TopOfStack;
	ElementType_Trans *Array;
};

#endif
