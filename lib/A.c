#include <stdio.h>

struct FUNC_LIST{
	void (*printA)(struct FUNC_LIST *func_list);
	void (*printB)(struct FUNC_LIST *func_list);
};

void printA(struct FUNC_LIST *func_list)
{
	printf("The A.so is loading! \n");
	if(func_list == NULL)
		printf("error!\n");
	
	if(func_list->printB != NULL)
		func_list->printB(func_list);
}
