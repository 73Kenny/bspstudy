#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void waiting();
void stop();

int wait_mark;

int main()
{
	int p1, p2, stdout;

	while (-1 == (p1 = fork())); // 创建进程p1
	if (0 < p1) // p1父进程
	{
		while (-1 == (p2 = fork())); // 创建进程p2
		if (0 < p2) // p2父进程
		{
			wait_mark = 1;
			signal(SIGINT, stop); // 为信号SIGINT注册相应的处理函数stop
			waiting();
			kill(p1, 10); // 为进程p1发送信号16(SIGSTKFLT)
			kill(p2, 12); // 为进程p2发送信号17(SIGCHLD), 信号接收不一定是这个顺序
			wait(0);
			wait(0);
			printf("Parent process is killed!\n");
			exit(0);
		}
		else // p2子进程
		{
			sigset_t sigs; // 信号集
			sigemptyset(&sigs); // 信号集合初始化为空
			sigaddset(&sigs, SIGINT); // 将信号SIGINT添加到信号集sigs中
			sigprocmask(SIG_BLOCK, &sigs, 0); // 将信号集sigs中的信号添加到屏蔽字中
			wait_mark = 1;
			signal(12, stop); // 为信号17(SIGCHLD)注册相应的处理函数stop
			waiting();
			lockf(stdout, 1, 0); // 标准输出加锁
			printf("Child process 2 is killed by parent!\n");
			lockf(stdout, 0, 0); // 标准输出解锁
			exit(0);
		}
	}
	else // p1子进程
	{
		sigset_t sigs;
		sigemptyset(&sigs);
		sigaddset(&sigs, SIGINT);
		sigprocmask(SIG_BLOCK, &sigs, 0);
		wait_mark = 1;
		signal(10, stop); // 为信号16(SISTKFLT)注册相应的处理函数stop
		waiting();
		lockf(stdout, 1, 0);
		printf("Child process 1 is killed by parent!\n");
		lockf(stdout, 0, 0);
		exit(0);
	}

	return 0;
}

void waiting()
{
	while (0 != wait_mark);
}

void stop()
{
	wait_mark = 0;
}
 
