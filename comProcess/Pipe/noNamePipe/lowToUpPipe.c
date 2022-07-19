// 创建一个进程两个管道，从一管道写入小写字符串，另一管道读出大写字符串
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

char *strupr(char *str){
    char *orign=str;
    for (; *str!='\0'; str++)
        *str = toupper(*str);
    return orign;
}

int main(int argc, char* argv[])
{
    int fd_pipe1[2] = {0};
    int fd_pipe2[2] = {0};
    pid_t pid;

    if ( pipe(fd_pipe1) < 0 || pipe(fd_pipe2) < 0) // 创建无名管道1
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
		close(fd_pipe1[1]);
		close(fd_pipe2[0]);

        char str[50] = {0};
        read(fd_pipe1[0], str, sizeof(str)); // 从管道1里读小写字符串
		strcpy(str, strupr(str));			 // 转换小写字符串为大写字符串

		write(fd_pipe2[1], str, strlen(str)); // 往管道2里写处理后的大写字符串
    }
    else if ( pid > 0) // 父进程
    {
		close(fd_pipe1[0]);
		close(fd_pipe2[1]);

        char buf[] = "i am the test string.";
        write(fd_pipe1[1], buf, strlen(buf)); // 往管道1里写小写字符串

		char str1[50];
		read(fd_pipe2[0], str1, sizeof(str1)); // 从管道2里读大写字符串
		puts(str1);
    }

}
