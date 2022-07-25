#ifndef SYSMEN_H
#define SYSMEN_H


#include <sys/sem.h>
#include <sys/shm.h>

// 此宏用于调试使用，注销后将不显示调试信息
#define DEBUG

///////////////////////////////////////////////////////////////共享内存

// 释放共享内存，传入指定共享内存的shmid
// 释放成功将返回0，失败返回-1
int shmrls(int shmid);

// 创建并挂载共享内存
// 创建成功将返回共享内存的首地址，失败将报错并退出程序
// 参数1：用于创建共享内存的唯一键值
// 参数2：共享内存的创建大小
// 参数3：共享内存的创建方式
// 参数4：用于返回共享内存shmid
void *shmlnk(key_t key, size_t size, int shmflg, int *shmid);

// 卸载并释放共享内存
// 成功时返回0， 失败时返回-1
// 参数1：要卸载并释放的共享内存的shmid
// 参数2：共享内存的首地址
int shmnlk(int shmid, const void *addr);


//////////////////////////////////////////////////////////////信号量

// 用于更改信号量值的结构体
union semun{
	int val;	// 信号量的值
	struct semid_ds *buf;
	unsigned short *arry;	
};

// 获取信号量的值
// 成功时返回信号量的值，失败时返回-1
// 参数1：信号量集合的semid
// 参数2：指定信号量在集合中的索引（以0开头）
int get_semval(int semid, int sem_num);

// 设置信号量的值
// 成功时返回0，失败时返回-1
// 参数1：信号量集合的semid
// 参数2：指定信号量在集合中的索引（以0开头）
// 参数3：要设置的信号量的值
int set_semval(int semid, int sem_num, int val);

// 删除信号量
// 成功时返回0，失败时返回-1
// 参数1：信号量集合的semid
// 参数2：指定信号量在集合中的索引（以0开头）
int del_semval(int semid, int sem_num);

// 对指定信号量进行P操作
// 成功时返回0，失败时返回-1
// 参数1：信号量集合的semid
// 参数2：指定信号量在集合中的索引（以0开头）
int P(int semid, int sem_num);

// 对指定信号量进行V操作
// 成功时返回0，失败时返回-1
// 参数1：信号量集合的semid
// 参数2：指定信号量在集合中的索引（以0开头）
int V(int semid, int sem_num);


#endif
