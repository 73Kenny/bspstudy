// Client1.c (Server)
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>
#include <utime.h>

void printFormatTime(char * format)
{
    time_t t;
    time(&t);

    struct tm * time_date = localtime(&t);

    int year = time_date->tm_year + 1900;
    int month = time_date->tm_mon + 1;
    int day = time_date->tm_mday;
    int hour = time_date->tm_hour;
    int minute = time_date->tm_min;
    int second = time_date->tm_sec;

    char time_str[100];
    sprintf(time_str, format, year, month, day, hour, minute, second);
    puts(time_str);
}            

typedef struct
{
	long mtype;			//消息类型
    char mtext[100];	//消息正文
} msgform;

int main()
{
    FILE *fp;
    key_t key;
    pid_t pid;
    int msgid;
    msgform msg1, msg2;
    char buf[800] = "";       // 消息缓冲区
	char my_name[20] = "";	  // 我的名字
	char other_name[20] = ""; // 其他人名字
	// key = ftok(".", 0xFF);	  // 生成
	key = 75;
	char * format = "%d年%d月%d日 %.2d:%.2d:%.2d";

    if ((msgid = msgget(key, IPC_CREAT | 0666)) < 0) // 创建消息队列
	{
        perror("msgget error");
        exit(0);
    }


    msg1.mtype = 3;					// 你的名字: 消息类型为3
    printf("please input your name: ");
    memset(msg1.mtext, 0, 100);		// 先清空消息正文缓冲区
    fgets(buf, 100, stdin);			// 将标准输入到消息缓冲区buf
    buf[strlen(buf)-1] = '\0';
    strcpy(my_name, buf);			// 把缓冲区buf中我的名字复制到my_name
    strcpy(msg1.mtext, buf);		// 把缓冲区buf中我的名字复制到消息正文mtext
    msgsnd(msgid, &msg1, sizeof(msg1.mtext), 0); //把我的名字消息my_name添加到消息队列中

    msgrcv(msgid, &msg2, 100, 4, 0); // 接收消息类型为4(对方名字)的100bytes的信息
    strcpy(other_name, msg2.mtext);
    // fflush(stdout); // 清空文件缓冲区

    //创建一个子进程
    if ((pid = fork()) < 0) 
	{
        printf("error\n");
        exit(0);
    }
	else if (pid == 0)  // 子进程
	{
        while (1) 
		{
            msg1.mtype = 1;				// 我输入的聊天信息 类型为1
            memset(msg1.mtext, 0, 100); // 清空消息正文
            printf("%s: ", my_name);	// 输出我的名字
            fgets(buf, 100, stdin);     // 输入聊天信息
            buf[strlen(buf)-1] = '\0';
            strcpy(msg1.mtext, buf);	// 将聊天信息放在缓存区mtext 
            msgsnd(msgid, &msg1, sizeof(msg1.mtext), 0); // 发送聊天信息到消息队列
        }
    }
    else // 父进程
	{
        while (1) 
		{
			msgrcv(msgid, &msg2, 100, 2, 0); // 接收type为2的消息 (接收对方的聊天消息)
            if ((fp = fopen("data.txt", "a+")) == NULL) 
			{
                perror("打开失败记录");
                return 0;
            }
            fprintf(fp, "%s: %s\n", other_name, msg2.mtext); // 将对方聊天消息保存到文件中
            fclose(fp);


			// 输出
            // printf("\r"); // 光标回到行首
            printFormatTime(format);
			printf("\r%s: %s\n%s: ", other_name, msg2.mtext, my_name);
            fflush(stdout);
        }
    }
}
