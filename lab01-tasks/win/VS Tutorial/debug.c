#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int* bug;

int f(int a, int b)
{
	int c;

	c = a + b;

	return c;
}

int main(void)
{
	printf("Hello SO\n");
	bug = malloc(sizeof(int));
	*bug = f(1, 2);

	printf("bug = %d\n", *bug);
	free(bug);
	return 0;
}

