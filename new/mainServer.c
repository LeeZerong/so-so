#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <string.h>

#define CONFIG_PATH "./so_config"

typedef struct FUNC_LIST
{
	//int a;
	void (*printA)();
	void (*printB)();
}list;

struct FUNC_S
{
	list *func_list;
};

typedef void (*FUNC)(list *funcs);


int main()
{
	int fd = 0;          //文件描述符
	int ret = 0;         //返回值
	char info[50] = {0}; //配置文件中的信息
	char name[50] = {0}; //动态库名
	void *handle  = NULL;//打开动态链接库返回的句柄
	char *lib_path = NULL;//动态库的路径
	
	//struct FUNC_S funcs = {0};
	list funcs = {0};
	
	FUNC func = NULL;
	
	//打开配置文件
	if(0 > (fd = open(CONFIG_PATH, O_RDONLY)))
	{
		perror("open config fail");
		ret = -1;
		goto err;
	}
	
	//读取配置文件的信息
	if(0 > read(fd, info, sizeof(info)))
	{
		perror("read config fail");
		ret = -2;
		goto err;
	}
	
	sscanf(info, "The lib path is: %s ", name);
	printf("The lib path is %s\n", name);
	
	//切割从配置文件中获得的字符串
	lib_path = strtok(name, ",");

	while(lib_path)
	{
		//打开动态链接库
		handle = dlopen(lib_path, RTLD_LAZY);
		if (!handle) 
		{
			printf("%s\n", dlerror());
			ret = -3;
			goto err;
		}
		
		lib_path = strtok(NULL, ",");
		
		//调用注册函数
		func = (FUNC)dlsym(handle, "func_regist_B");
		if(func != NULL)
		{ 
			func(&funcs);
			//printf("B fun funcs:%p\n", &funcs);
		}
		
		func = (FUNC)dlsym(handle, "func_regist_A");
		if(func != NULL)
		{
			//printf("&funcs=%p\n",&funcs);
			func(&funcs);
			//printf("A fun funcs:%p\n", &funcs);
		}
	}	
	
	
	//printf("%d\n",funcs.func_list->a);
	//printf("funcs.func_list->printA:%p\n",funcs.func_list);
	
	funcs.printA();
	
err:
	close(fd);
	return ret;	
	
}