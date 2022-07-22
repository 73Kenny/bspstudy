// Client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MSGKEY 75

struct msgform
{
	long mtype; // 消息类型
	char mtext[1000]; // 消息正文
} msg;

int msgqid;

void client()
{
	int i;
	msgqid = msgget(MSGKEY, 0777); // 创建值为75的消息队列

	for (i = 10; i >= 1; i--)
	{
		msg.mtype = i; // 消息i放到缓冲区 
		msgsnd(msgqid, &msg, 1024, 0); // 发送消息 
		printf("(client)sent msg type %ld.\n", msg.mtype); // 客户端发送消息
	}

	exit(0);
}

int main()
{
	client();

	return 0;
}
