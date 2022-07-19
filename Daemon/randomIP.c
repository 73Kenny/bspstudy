#include <unistd.h> 
#include <signal.h> 
#include <fcntl.h>
#include <sys/syslog.h>
#include <sys/wait.h>
#include <sys/param.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
int init_daemon(void)
{ 
	int pid; 
	int i;
	
	// 1）屏蔽一些控制终端操作的信号
	signal(SIGTTOU,SIG_IGN); 
	signal(SIGTTIN,SIG_IGN); 
	signal(SIGTSTP,SIG_IGN); 
	signal(SIGHUP ,SIG_IGN);
 
	// 2）在后台运行
  if( pid = fork() ){ // 父进程
        exit(0);      //结束父进程，子进程继续
	}else if( pid < 0 ){ // 出错
		perror("fork");
		exit(EXIT_FAILURE);
	}
	
	// 3）脱离控制终端、登录会话和进程组
	setsid();  
	
	// 4）禁止进程重新打开控制终端
	if( pid = fork() ){ // 父进程
		exit(0);      // 结束第一子进程，第二子进程继续（第二子进程不再是会话组长） 
	}else if(pid < 0){ // 出错
		perror("fork");
		exit(EXIT_FAILURE);
	}  
	
	// 5）关闭打开的文件描述符
	// NOFILE 为 <sys/param.h> 的宏定义
	// NOFILE 为文件描述符最大个数，不同系统有不同限制
	for(i=0; i< NOFILE; ++i){
		close(i);
	}
	
	// 6）改变当前工作目录
	chdir("/tmp"); 
	
	// 7）重设文件创建掩模
	umask(0);  
	
	// 8）处理 SIGCHLD 信号
	signal(SIGCHLD,SIG_IGN);
	
	return 0; 
} 
 
int main(int argc, char *argv[]) 
{
	FILE* fp;
	int lines = 0;
	int move = 0;
	char str[20], command[100] = {'\0'};

	init_daemon();

	fp = fopen("/tmp/ipList.txt", "r");
	if (fp <= 0)	
	{
		perror("文件打开失败");
		exit(1);
	}
	while (fscanf(fp, "%s", str) != EOF)
	{
		lines++;
	}

	int tmp = lines;
	while(1)
	{
		fseek(fp, 0, SEEK_SET);
		srand( (unsigned int)time(NULL) );
		lines = rand() % tmp;
		printf("lines: %d\n", lines);
		move = 0;
		while (move < lines)
		{
			fscanf(fp, "%s", str);
			move++;
		}
	
		strcpy(command, "ifconfig eno1 ");
		strcat(command, str);
		strcat(command, " netmask 255.255.255.0");
		puts(str);

		pid_t pid = fork();
		if (0 == pid)
		{
			execl("/bin/sh", "sh", "-c", command, NULL);	
		}
		else if (pid > 0)
		{
			wait(NULL);
		}


	//	system(command); // 使用system()函数比较简单，但但使用时应注意在编写具有 SUID/SGID 权限的程序时请勿使用system(), system()会继承环境变量, 通过环境变量可能会造成系统安全的问题.

		

		sleep(1);
	}

	fclose(fp);
 
	return 0;
}
