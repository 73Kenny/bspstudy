#include <stdio.h>
#include <stdlib.h>

#define SIZE 4096


int main(void)
{
	FILE* fp1;
	FILE* fp2;
	int tmp[SIZE];

	if ((fp1 = fopen("烈火战马(Live)--GAI周延.mp3", "rb")) == NULL)
	{
		perror("fp1");
		exit(0);
	}

	if ((fp2 = fopen("copy烈火战马.mp3", "wb")) == NULL)
	{
		perror("fp2");
		exit(0);
	}

	int validCount = 0;

	// 每个数据块为sizeof(int) 读取SIZE块 缓冲区tmp = int * SIZE
	while ( (validCount = fread(tmp, sizeof(int), SIZE, fp1)) != 0 )
	{
		printf("%d\n", validCount);
		fwrite(tmp, sizeof(int), validCount, fp2);
	}

	fclose(fp1);
	fclose(fp2);

	puts("文件复制完成！");

	return 0;
}
