#include <stdio.h>

struct FUNC_LIST{
	void (*printA)(struct FUNC_LIST *func_list);
	void (*printB)(struct FUNC_LIST *func_list);
};

void printB(struct FUNC_LIST *func_list)
{
	printf("The B.so is loading! \n");
}
