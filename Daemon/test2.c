#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
//	char* argv[] = {"ifconfig", "eno1", "192.168.69.20",  "netmask",  "255.255.255.0", NULL};
//	execvp(argv[0], argv);


//	execl("/bin/sh", "sh", "-c", "ifconfig eno1 192.168.69.10 netmask 255.255.255.0", NULL);

//
//	system("ifconfig eno1 192.168.69.33 netmask 255.255.255.0");

	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", rand()%100);
	}

	return 0;
}
