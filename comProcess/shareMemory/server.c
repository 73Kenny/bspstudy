#include "common.h"

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
	server();
	return 0;
}
