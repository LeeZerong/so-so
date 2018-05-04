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

#define PRINTA  func_list.printA
#define PRINTB  func_list.printB

//功能函数
void printA()
{
	printf("The A.so is loading! \n");

	if(PRINTB != NULL)
		PRINTB();
}

//注册函数
void func_regist_A()
{	
	//注册功能函数到函数表中
	PRINTA = printA;
	printf("regist printA!\n");
}

//注销函数
void func_unregist_A()
{
	if(PRINTA != NULL)
	{
		PRINTA = NULL;
	}
}