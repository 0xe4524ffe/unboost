#ifdef __GETOPT_PRIVATE
	#undef __GETOPT_PRIVATE
	
	typedef struct _ctxGetopt{
		char *argv[];
		intptr_t permute;
		intptr_t iter;
		intptr_t opt;
		intptr_t sub;
		char *arg;
		char emsg[64];

	} ctxGetopt;
	
	
	#define EMSG_INVALID "Invalid option."
	#define EMSG_MISSINGARG "Option requires an argument."
	#define EMSG_TOOMANYARG "Too many arguments."
	
#endif

typedef enum _OptArgType {NONE, REQUIRED, OPTIONAL} OptArgType;