#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHMKEY 75 // 设共享内存标识为75

int shmid, i;
int* addr;

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

void server()
{
	shmid = shmget(SHMKEY, 1024, 0777 | IPC_CREAT); // 创建共享内存区
	addr = shmat(shmid, 0, 0); // 挂接共享内存

	do
	{
		*addr = -1; // 将第一个字节置为-1(表示数据空)
		while (*addr == -1); // 等待其他进程发来消息
		printf("(server) received\n");
	} while (*addr);

	shmdt(addr);
	shmctl(shmid, IPC_RMID, 0);
	exit(0);
}

int main()
{
	while (-1 == (i = fork()));
	if (!i)
	{
		server();
	}

	system("ipcs -m");

	while (-1 == (i = fork()));

	if(!i)
	{
		client();
	}

	wait(0);
	wait(0);

	return 0;
}
