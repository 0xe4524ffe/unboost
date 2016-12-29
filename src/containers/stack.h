#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdint.h>
#include <stdatomic.h>

#include "config.h" //FIXME: uintptr_exact_t definition
//TODO: use opaque pointer, probably will fix all the problems
#ifdef __STACK_PRIVATE
	#undef __STACK_PRIVATE
#else
	
	struct _StackNode {
		void *Value;
		struct _StackNode *Next;
	};
	
	struct _StackHead {
		UINTPTR_EXACT_T Changes;
		struct _StackNode *Node
	};
	
	typedef struct _Stack {
		struct _StackNode *Buffer;
		_Atomic struct _StackHead Head, Free;
		_Atomic size_t Size;
	} Stack;
	
#endif

//Public API
intptr_t StackInit(Stack restrict *p, size_t s); // s - maximum stack size

static inline void StackFree(Stack * restrict p){
	free(p->Buffer);
	p->Buffer=NULL;
}

static inline size_t StackGetSize(Stack *p){
	return atomic_load(&p->Size);
}

intptr_t StackPush(Stack *p, void *d);
void *StackPop(Stack *p);

#endif
