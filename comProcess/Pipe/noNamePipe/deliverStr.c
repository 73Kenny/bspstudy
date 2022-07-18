#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int fd_pipe[2] = {0};
	pid_t pid;

	if ( pipe(fd_pipe) < 0) // 创建无名管道
	{
		perror("pipe");
	}

	pid = fork(); // 创建进程
	if ( pid < 0 )
	{
		perror("fork");
		exit(-1);
	}
	
	if ( pid == 0) // 子进程
	{
		char buf[] = "I am sunplus";
		write(fd_pipe[1], buf, strlen(buf)); // 往管道里写数据
		_exit(0);
	}
	else if ( pid > 0) // 父进程
	{
		wait(NULL);
		char str[50] = {0};
		read(fd_pipe[0], str, sizeof(str)); // 从管道里读数据
		printf("str = \"%s\"\n", str);
	}

}
