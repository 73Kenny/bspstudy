#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "sysmen.h"

///////////////////////////////////////////////////////////////共享内存
int shmrls(int shmid){
	if(shmctl(shmid, IPC_RMID, NULL) == -1){
#ifdef DEBUG
		printf("release shared memory failed, shmid:%d\n", shmid);
		perror("shctl: ");
#endif
		return -1;
	}else{
#ifdef DEBUG
		printf("release shared memory succeed, shmid:%d\n", shmid);
#endif
		return 0;
	}
}

void *shmlnk(key_t key, size_t size, int shmflg, int *shmid){
	*shmid = shmget(key, size, shmflg);
	if(*shmid == -1){
#ifdef DEBUG
		printf("get shared memory failed, key:%d\n", key);
		perror("shmget: ");
#endif
		exit(1);
	}else{
#ifdef DEBUG
		printf("get shared memory succeed, key:%d, shmid:%d\n", key, *shmid);
#endif
	}
	void *addr = shmat(*shmid, NULL, 0);
	if((long)addr == -1){
#ifdef DEBUG
		printf("link to shared memory failed, shmid:%d\n", *shmid);
		perror("shmat: ");
#endif
		exit(1);
	}else{
#ifdef DEBUG
		printf("link to shared memory succeed, shimd:%d\n", *shmid);
#endif
	}
	return addr;
}

int shmnlk(int shmid, const void *addr){
	if(shmdt(addr) == -1){
#ifdef DEBUG
		printf("unlink from shared memory faild, shmid:%d\n", shmid);
		perror("shmdt: ");
#endif
		return -1;
	}else{
#ifdef DEBUG
		printf("unlink from shared memory succeed, shmid:%d\n", shmid);
#endif
	}
	return shmrls(shmid);
}



//////////////////////////////////////////////////////////////信号量
int get_semval(int semid, int sem_num){
	union semun sem_union;
	int value;
	if((value = semctl(semid, sem_num, GETVAL, sem_union)) == -1){
#ifdef DEBUG
		printf("get semaphore value failed, semid:%d, sem_num:%d\n", semid, sem_num);
		perror("semctl: ");
#endif
		return -1;
	}else{
#ifdef DEBUG
		printf("get semaphore value succeed, semid:%d, sem_num:%d\n", semid, sem_num);
#endif
	}
	return value;
}

int set_semval(int semid, int sem_num, int val){
	union semun sem_union;
	sem_union.val = val;
	if(semctl(semid, sem_num, SETVAL, sem_union) == -1){
#ifdef DEBUG
		printf("set semaphore value failed, semid:%d, sem_num:%d\n", semid, sem_num);
		perror("semctl: ");
#endif	
		return -1;
	}else{
#ifdef DEBUG
		printf("set semaphore value succeed, semid:%d, sem_num:%d\n", semid, sem_num);
#endif
	}
	return 0;
}

int del_semval(int semid, int sem_num){
	union semun sem_union;
	if(semctl(semid, sem_num, IPC_RMID, sem_union) == -1){
#ifdef DEBUG
		printf("delete semaphore value failed, semid:%d, sem_num:%d\n", semid, sem_num);
		perror("semctl: ");
#endif
		return -1;
	}else{
#ifdef DEBUG
		printf("delete semaphore value succeed, semid:%d, sem_num:%d\n", semid, sem_num);
#endif
	}
	return 0;
}

int P(int semid, int sem_num){
	struct sembuf sem_buf;
	sem_buf.sem_num = sem_num;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;
	if(semop(semid, &sem_buf, 1) == -1){
#ifdef DEBUG
		printf("set semaphore operation P failed, semid:%d, sem_num:%d\n", semid, sem_num);
		perror("semop: ");
#endif
		return -1;
	}else{
#ifdef DEBUG
		printf("set semaphore operation P failed, semid:%d, sem_num:%d\n", semid, sem_num);
#endif
	}
	return 0;
}

int V(int semid, int sem_num){
	struct sembuf sem_buf;
	sem_buf.sem_num = sem_num;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = SEM_UNDO;
	if(semop(semid, &sem_buf, 1) == -1){
#ifdef DEBUG
		printf("set semaphore operation V, semid:%d, sem_num:%d\n", semid, sem_num);
		perror("semop: ");
#endif
		return -1;
	}else{
#ifdef DEBUF
		printf("set semaphore operation V, semid:%d, sem_num:%d\n", semid, sem_num);
#endif
	}
	return 0;
}
