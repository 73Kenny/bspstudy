#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>


int wait_mark;

void waiting()
{
	while (0 != wait_mark);
}

void stop()
{
	wait_mark = 0;
}


int main()
{
	int stdout;
	pid_t pid = fork();

	if ( -1 == pid )
	{
		perror("pid");	
		exit(1);
	}
	else if (0 == pid)
	{
		sigset_t sigs;
		sigemptyset(&sigs);
		sigaddset(&sigs, SIGINT);
		sigprocmask(SIG_BLOCK, &sigs, 0);	
		
		wait_mark = 1;

		signal(16, stop);
		waiting();

		lockf(stdout, 1, 0);
		printf("开车了\n");
		lockf(stdout, 0, 0);
		
		exit(0);
	}
	else
	{
		wait_mark = 1;
		signal(SIGINT, stop);
		waiting();
		kill(pid, 16);
		wait(0);
		
		exit(0);
	}
	
	return 0;
}
