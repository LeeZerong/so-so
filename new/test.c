#include <stdio.h>

struct B
{
	void (*hello)();
};

struct A 
{
	struct B *b;
};

void hel()
{
	printf("hello\n");
}

struct B bb =  {.hello = hel,};

void reg(struct A *a)
{
	(*a).b = &bb;
	printf("aa->b->hello:%p\n", (*a).b->hello);
}

int main()
{
	struct A aa;
	reg(&aa);
	printf("aa.b->hello:%p\n", aa.b->hello);
	aa.b->hello();
	return 0;
}