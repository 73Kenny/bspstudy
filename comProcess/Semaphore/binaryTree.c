#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define KEY (key_t)14010322

union semun
{
	int val;
	struct semid_ds* buf;
	unsigned short* arry;
};

static int sem_id = 0;
static int set_semvalue();
static void del_semvalue();
static void semaphore_p();
static void semaphore_v();


int main(int argc, char** argv)
{
	int semid;
	pid_t pid;

	if (-1 == (semid = semget(KEY, 3, IPC_CREAT | 0660))) // 创建信号量
    {
        printf("ERROR\n");
        return -1;
    }

    union semun arg[3];

    arg[0].val = 1; // mutex = 1
    arg[1].val = 5; // empty = 5
    arg[2].val = 0; // full = 0

    for (int i = 0; i < 3; i++)
    {
        semctl(semid, i, SETVAL, arg[i]); // 用于初始化信息量，在使用信号量前必须这么做
    }


	for (int i = 0; i < 2; ++i)
	{
		pid = fork();
		if (-1 == pid)
		{
			perror("fork");
			exit(1);
		}

		if (0 == pid)
		{
			break;
		}
	}

	if (pid > 0)
	{
        sleep(2);
        semaphore_p(semid, 1); // p(empty)
        semaphore_p(semid, 0); // p(mutex)
		printf("Parent:   pid=%d, ppid=%d\n", getpid(), getppid());
		semaphore_v(semid, 0); // v(mutex)
        semaphore_v(semid, 1); // v(empty)
        sleep(5);
		exit(0);
	}
	else if (0 == pid)
	{
        sleep(2);
        semaphore_p(semid, 1); // p(empty)
        semaphore_p(semid, 0); // p(mutex)
		printf("Children: pid=%d, ppid=%d\n",  getpid(), getppid());
        semaphore_v(semid, 0); // v(mutex)
        semaphore_v(semid, 1); // v(empty)
        sleep(5);
	}

	return 0;
}

static void del_semvalue()
{
    union semun sem_union;
    if (-1 == semctl(sem_id, 0, IPC_RMID, sem_union))
    {
        fprintf(stderr, "Failed to delete semaphore\n");
    }
}

static int set_semvalue()
{
    union semun sem_union;
    sem_union.val = 1;
    if (-1 == semctl(sem_id, 0, SETVAL, sem_union))
    {
        return 0;
    }
    return 1;
}

void semaphore_p(int sem_id, int semNum)
{
    struct sembuf sem_b;
    sem_b.sem_num = semNum;
    sem_b.sem_op = -1; // P()
    sem_b.sem_flg = SEM_UNDO;

    if (-1 == semop(sem_id, &sem_b, 1))
    {
        fprintf(stderr, "semaphore_p failed\n");
    }
}

void semaphore_v(int sem_id, int semNum)
{
    struct sembuf sem_b;
    sem_b.sem_num = semNum;
    sem_b.sem_op = 1; // V()
    sem_b.sem_flg = SEM_UNDO;

    if (-1 == semop(sem_id, &sem_b, 1))
    {
        fprintf(stderr, "semaphore_p failed\n");
    }
}

