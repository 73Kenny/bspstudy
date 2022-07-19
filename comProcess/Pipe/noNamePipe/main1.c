#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_DATA_LEN 256
#define DELAY_TIME 1

int main(int argc, char** argv)
{
	pid_t pid;
	int pipe_fd[2];
	char buf[MAX_DATA_LEN];
	const char data[] = "Pipe Test Program";
	int real_read, real_write;

	memset((void*)buf, 0, sizeof(buf));

	if (0 > pipe(pipe_fd))
	{
		printf("Pipe create error\n");
		exit(1);
	}

	if (0 == (pid = fork()))
	{
		close(pipe_fd[1]); // 关闭写管道
		sleep(DELAY_TIME * 3);

		if (0 < (real_read = read(pipe_fd[0], buf, MAX_DATA_LEN))) // 从管道读到buf
		{
			printf("I am child progress， I have read %d bytes from the pipe:'%s'\n", real_read, buf);
		}

		close(pipe_fd[0]); // 关闭读管道
		exit(0);
	}
	else if (0 < pid)
	{
		close(pipe_fd[0]); // 关闭读管道
		sleep(DELAY_TIME);

		if (-1 != (real_write = write(pipe_fd[1], data, strlen(data)))) // 往管道里写data
		{
			printf("I am parent progress, I have wrote %d bytes to the pipe:'%s'\n", real_write, data);
		}

		close(pipe_fd[1]); // 关闭写管道
		waitpid(pid, NULL, 0);
		exit(0);
	}

	return 0;
}
