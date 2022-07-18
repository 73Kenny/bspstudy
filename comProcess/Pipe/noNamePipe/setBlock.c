#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
 
int main(int argc, char *argv[])
{
	int fd_pipe[2] = {0};
	pid_t pid;
	
	if( pipe(fd_pipe) < 0 ){// 创建无名管道
		perror("pipe");
	}
	
	pid = fork(); // 创建进程
	if( pid < 0 ){ // 出错
		perror("fork");
		exit(-1);
	}
	
	if( pid == 0 ){ // 子进程
		
		sleep(3); // 子进程等待3秒时，父进程此时在读
		
		char buf[] = "hello, edu";
		write(fd_pipe[1], buf, strlen(buf)); // 写数据
		
		_exit(0);
	}else if( pid > 0){// 父进程
	
		fcntl(fd_pipe[0], F_SETFL, O_NONBLOCK); // 非阻塞
		// fcntl(fd_pipe[0], F_SETFL, 0); // 阻塞
		
		while(1){
			char str[50] = {0};
			read( fd_pipe[0], str, sizeof(str) );//读数据
			
			printf("str=[%s]\n", str);
			sleep(1);
		}
	}
	
	return 0;
}
