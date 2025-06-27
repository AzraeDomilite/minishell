#include <stdio.h>

void fonc(char *arr[])
{
	while(*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

int main(void)
{
	fonc((char*[]){"a", "b", "c", NULL});
}