#include "common.h"

void client()
{
    int i;

    shmid = shmget(SHMKEY, 1024, 0777); // 创建共享内存
    addr = (int*)shmat(shmid, 0, 0); // 挂接共享内存

    for (i = 9; i >= 0; i--)
    {   
        while (-1 != *addr); // 若数据空则发送
        printf("(client) sent\n");
        *addr = i; // 发9 8 7 6 5 4 3 2 1 0
    }   
    exit(0);
}

int main()
{
	client();

	return 0;
}

