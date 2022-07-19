#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main()
{
	int ret;
	ret = mkfifo("My_FIFO", 0666);

	if (0 != ret)
	{
		perror("mkfifo");
	}
	return 0;
}
