#include <unistd.h>
#include <stddef.h>

int main()
{
	write(STDIN_FILENO, "asdf", 4);
	execve("cat", NULL, NULL);
}