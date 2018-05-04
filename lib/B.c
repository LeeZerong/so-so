#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <string.h>

typedef struct FUNC_LIST
{
	void (*printA)();
	void (*printB)();
}list;

extern list func_list;

#define PRINTB  func_list.printB

void printB()
{
	printf("The B.so is loading! \n");
}

//注册函数
void func_regist_B()
{	
	//注册功能函数到函数表中
	PRINTB = printB;
	printf("regist printB!\n");
}

//注销函数
void func_unregist_B()
{
	if(PRINTB != NULL)
	{
		PRINTB = NULL;
	}
}
