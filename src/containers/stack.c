#define __STACK_PRIVATE
#include "stack.h"

//s - maximum stack size
intptr_t StackInit(Stack * restrict p, size_t s){
	struct _StackHead HeadInit={0, NULL};
	p->Head=ATOMIC_VAR_INIT(HeadInit);
	p->Size=ATOMIC_VAR_INIT(0);
	
	//Preallocating nodes
	p->Buffer=calloc(s, sizeof(struct _StackNode));
	if (p->Buffer == NULL) return ENOMEM;
	
	for (size_t i=0; i<(s-1); i++){
		p->Buffer[i].Next=p->Buffer+i+1;
	}
	
	p->Buffer[s-1].Next=NULL;
	
	struct _StackHead FreeInit={0, p->Buffer};
	p->Free=ATOMIC_VAR_INIT(FreeInit);
	
	return EXIT_SUCCESS;
}

static struct _StackNode *StackPopPrivate(_Atomic struct _StackHead *pHead){
	struct _StackHead Next, Orig=atomic_load(pHead);
	
	do {
		if (Orig.Node == NULL) return NULL; //Stack is empty
		Next.Changed=Orig.Changed+1;
		Next.Node=Orig.Node->Next;
	} while (!atomic_compare_exchange_weak(pHead, &Orig, Next));
	
	return Orig.Node;
}

static void StackPushPrivate(_Atomic struct _StackHead *pHead, struct _StackNode * restrict pNode){
	struct _StackHead Next, Orig=atomic_load(pHead);
	
	do {
		pNode->Next=Orig.Node;
		Next.Counter=Orig.Counter+1;
		Next.Node=pNode;
	} while (!atomic_compare_exchange_weak(pHead, &Orig, Next));
	
}

intptr_t StackPush(Stack *p, void *d){
	struct _StackNode *pNode=StackPopPrivate(&p->Free);
	if (pNode == NULL) return ENOMEM;
	
	pNode->Value=d;
	StackPushPrivate(&p->Head, pNode);
	atomic_fetch_add(&p->Size, 1);

return EXIT_SUCCESS;
}

void StackPop(Stack *p){
	struct _StackNode *pNode=StackPopPrivate(&p->Head);
	if (pNode == NULL) return NULL;
	
	atomic_fetch_sub(&p->Size, 1);
	void *d=pNode->Value;
	StackPushPrivate(&p->Free, pNode);
	
return d;
}
