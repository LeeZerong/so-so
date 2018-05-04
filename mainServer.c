#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <string.h>

#define CONFIG_PATH "./so_config"

struct FUNC_LIST{
	void (*printA)(struct FUNC_LIST *func_list);
	void (*printB)(struct FUNC_LIST *func_list);
};

typedef void (*FUNC)(struct FUNC_LIST *func_list);

int main()
{
	int fd = 0;          //文件描述符
	int ret = 0;         //返回值
	char info[50] = {0}; //配置文件中的信息
	char name[50] = {0}; //动态库名
	void *handle  = NULL;//打开动态链接库返回的句柄
	char *lib_path = NULL;//动态库的路径
	
	FUNC func = NULL;
	struct FUNC_LIST func_list = {0};
	
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
		
		//获取功能函数存入函数表中
		func = (FUNC)dlsym(handle, "printA");
		if(func != NULL)
			func_list.printA = func;
		
		func = (FUNC)dlsym(handle, "printB");
		if(func != NULL)
			func_list.printB = func;
		
		lib_path = strtok(NULL, ",");
	}	
		
	if((func_list.printA != NULL) && (func_list.printB != NULL))
		func_list.printA(&func_list);
		
	
	
	//关闭动态链接库
    dlclose(handle); 
	
err:
	close(fd);
	return ret;	
	
}