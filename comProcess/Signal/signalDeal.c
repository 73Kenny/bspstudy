#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signalDeal(int sig, siginfo_t* info, void* t)
{
	if (sig == SIGINT)
	{
		printf("Ctrl + C被按下\n");
	}
	else if (sig == SIGQUIT)
	{
		printf("Ctrl + \\被按下\n");
	}
	else
	{
		printf("其他信号\n");
	}
}


int main(int argc, char** argv)
{
	struct sigaction act;
	act.sa_sigaction = signalDeal;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);

	while (1);

	return 0;
}
