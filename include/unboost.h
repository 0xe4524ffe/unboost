#ifndef __UNBOOST_H
#define __UNBOOST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
	#error "unboost: only C compiler is supported."
#endif

#if (__STDC_VERSION__ < 201112L) || (!defined(__GNUC__))
	#error "unboost: GNU C 11 support is required."
#endif

#include <assert.h>
#define containerof(p, type, member) ((type *)((char *)(p) - offsetof(type, member)))
#ifndef cold
	#define cold (__attribute__((__cold__)))
#endif
#ifndef hot
	#define hot (__attribute__((__hot__)))
#endif
#ifndef CONST
	#define CONST (__attribute__((__const__)))
#endif
#ifndef pure
	#define pure (__attribute__((__pure__)))
#endif
#ifndef unused
	#define unused (__attribute__((__unused__)))
#endif
#ifndef used
	#define used (__attribute__((__used__)))
#endif

#ifdef __STDC_NO_ATOMICS__
	#error "unboost: atomic operations library is required."
#endif
#include <stdatomic.h>

typedef struct _cntRef{
	void (*f)(const struct _cntRef *);
	uintptr_t i;
} cntRef;

static inline void cntRefInc(const cntRef *p){
	atomic_fetch_add((uintptr_t *)&p->i, 1);
}

static inline void cntRefDec(const cntRef *p){
	if (atomic_fetch_sub((uintptr_t *)&p->i, 1) == 1) p->f(p);
}

#endif //__UNBOOST_H
