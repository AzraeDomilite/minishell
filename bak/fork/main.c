
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
	int count = 3;
	pid_t pid;
	int fd;



	//fd = open("./finished", O_CREAT);
	//write(fd, "a", 1);	
	pid = fork();
	if (!pid)
	{
		pid = fork();
		if (!pid)
		{
			sleep(6);
			open("./finished", O_CREAT);
			exit(0);
		}
		sleep(1);
		exit(0);
	}

	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	printf("finish of main process");
}