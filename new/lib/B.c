#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct FUNC_LIST
{
	void (*printA)();
	void (*printB)();
}list;

#define PRINTB funcs->printB

void printB()
{
	printf("The B.so is loading! \n");
}

list *func;

//注册函数
void func_regist_B(list *funcs)
{	
	func = funcs;
	PRINTB = printB;
	//printf("B func :%p\n", funcs);
	printf("regist printB!\n");
	
}

//注销函数
void func_unregist_B(list *funcs)
{
	if(PRINTB != NULL)
	{
		PRINTB = NULL;
	}
}
