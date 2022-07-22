// Server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MSGKEY 75

struct msgform
{
	long mtype;
	char mtext[1000];
} msg;

int msgqid;

void server()
{
	msgqid = msgget(MSGKEY, 0777 | IPC_CREAT); // 如果消息队列不存在就创建一个，否则打开

	do
	{
		msgrcv(msgqid, &msg, 1030, 0, 0); // 从消息队列读取消息，读取后把此消息从消息队列中删除
		printf("(server)receviced msg type %ld.\n", msg.mtype); // 服务器端接收消息

	} while (1 != msg.mtype); // 消息接收到1为止

	msgctl(msgqid, IPC_RMID, 0); // 删除消息队列

	exit(0);
}

int main()
{
	server();

	return 0;
}
