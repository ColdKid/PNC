#ifndef COMMON_DEF
#define COMMON_DEF

#include "stdafx.h"

#define MAXQUEUENUM 10
#define PROCFAILED (0)
#define PROSUCCESS (1)
#define GET_CHAR_SIZE(pStr, length)\
{\
length = 0;\
char* temp = pStr;\
while (*temp)\
{\
	length++;\
	temp++;\
}\
}

#endif /*COMMON_DEF*/