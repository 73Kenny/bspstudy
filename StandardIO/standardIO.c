#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXSIZE 5

int main(int argc, char* argv[])
{
	FILE* fp1;
	FILE* fp2;

	char ch[MAXSIZE];

	if ( argc != 3 )
	{
		printf("command error!\n");
		return -1;
	}

	if ( (fp1 = fopen(argv[1], "r")) == NULL )
	{
		printf("file %s cannot open.\n", argv[1]);
		return -1;
	}

	if ( (fp2 = fopen(argv[2], "wa+")) == NULL )
	{
		printf("file %s cannot create.\n", argv[2]);
		return -1;
	}

	while ( fgets(ch, MAXSIZE, fp1) != NULL )
	{
		fputs(ch, fp2);
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}

