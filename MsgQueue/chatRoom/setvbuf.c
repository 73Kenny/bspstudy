#include "sysmen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* tmp;

int main()
{
	int shmid;
    tmp = (char*)shmlnk(50, 1024, 0600 | IPC_CREAT , &shmid);
    memset(tmp, 0, 1024);
    setvbuf(stdin, tmp, _IOLBF, BUFSIZ);

	char str[1024];


	pid_t pid = fork();

	if (pid == 0)
	{

		int i = 0;
		while(i++<5)
		{
			sleep(1);
			if (strlen(tmp))
			{
				printf("%s", tmp);
			}
		}
	}

	fgets(str, 100, stdin);
	return 0;
}
