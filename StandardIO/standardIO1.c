#include <stdio.h>
#include <stdlib.h>

#define N 5

int main()
{
	FILE* fp;
	int a[N], b[N];
	int i, size = sizeof(int);

	if ( NULL == (fp = fopen("demo.txt", "rb+")) )
	{
		puts("Fail to open file!");
		exit(0);
	}

	for (i = 0; i < N; i++)
	{
		scanf("%d", &a[i]);
	}

	fwrite(a, size, N, fp);
	rewind(fp);
	fread(b, size, N, fp);

	for (i = 0; i < N; i++)
	{
		printf("%d ", b[i]);
	}

	printf("\n");
	fclose(fp);
	
	return 0;
}
