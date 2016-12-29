#define __GETOPT_PRIVATE
#include "getopt.h"

intptr_t GetoptErr(ctxGetopt *c, const char * restrict msg, const char * restrict data){
	uintptr_t p=0;
	while (*msg) c->emsg[p++]=*msg++;
	const char *sep=" -- '";
	
	
	return EXIT_FAILURE;
}