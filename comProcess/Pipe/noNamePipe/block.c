#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	int fd_pipe[2] = {0};
	pid_t pid;

	if ( pipe(fd_pipe) < 0) // 创建无名管道
	{
		perror("pipe");
	}


	if ( (pid = fork()) < 0)
	{
		perror("fork");
		exit(-1);
	}

	if ( 0 == pid )
	{

		_exit(0);
	}
	else if ( pid > 0)
	{
		// fcntl(fd_pipe[0], F_SETFL, O_NONBLOCK); // 非阻塞
		char str[50] = {0};
		puts("Before read:");
		read(fd_pipe[0], str, sizeof(str));
		puts("After read:");
		printf("str = \"%s\"\n", str);
	}

	return 0;
}
