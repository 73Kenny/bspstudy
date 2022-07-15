#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void input(char* str)
{
	fgets(str, 1024, stdin);
	str[strlen(str)-1] = '\0';
}

int getSpaces(char* str)
{
	char* p = str;
	int countSpace = 0;

	while(*p++)
	{
		if (*p == ' ')
		{
			countSpace++;
		}
	}

	return countSpace;
}


void processData(char* str, int arguments)
{
	char* buf[arguments+1];
	char* delim = " ";

	char* p = strtok(str, delim);
	while (p)
	{
		static int index = 0;
		buf[index] = p;
		++index;
		p = strtok(NULL, delim);
	}
	buf[arguments] = NULL;

	execvp(buf[0], buf);
}


int main()
{
	char str[1024];

	do
	{
		input(str);

		if (strcmp(str, "q") == 0 || strcmp(str, "quit") == 0)
		{
			break;
		}

		pid_t pid = fork();
		switch (pid)
		{
			case 0:
				int countArguments = getSpaces(str) + 1;
				processData(str, countArguments);
				exit(0);
				puts("error");
				break;
			case -1:
				perror("Error: ");
				break;
			default:
				wait(NULL);
		}
	}
	while(1);

	return 0;
}
