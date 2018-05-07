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

#define PRINTA  funcs->printA
#define PRINTB  func->printB

typedef struct FUNC_LIST
{
	void (*printA)();
	void (*printB)();
}list;
void printA();
list *func;

//功能函数
void printA()
{
	printf("The A.so is loading! \n");
	//printf("func->printB : %p \n", func);

	if(PRINTB != NULL)
		PRINTB(); 
}

//注册函数
void func_regist_A(list *funcs)
{	
	func = funcs;
	PRINTA = printA;
	//printf("A func :%p\n", funcs);	
	printf("regist printA!\n");
	
}

//注销函数
void func_unregist_A(list *funcs)
{
	if(PRINTA!= NULL)
	{
		PRINTA= NULL;
	}
}