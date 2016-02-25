#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <unistd.h>
#include <sys/sem.h>
#include <fcntl.h>
#include<bits/stdc++.h>
using namespace std;
#define shmkey  1234
#define pkey 1257
#define semkey1 124
#define semkey2 156
#define shmsize 10
int *pid,sem1,sem2;
void s_wait (int semid){
	struct sembuf se = {0,-1,0};
	semop(semid,&se,1);
}
void s_signal (int semid){
	struct sembuf se = {0,1,0};
	semop(semid,&se,1);
}
int sem_init(int key,int initial_value)
{
	int semid = semget(key,1,0666|IPC_CREAT);
	if(semid == -1)
	{
		printf("semget error!!\n");
		exit(0);
	}
	semctl(semid,0,SETVAL,initial_value);
	return semid;
}
int  init(int key){
	int shmid = shmget(key,shmsize,IPC_CREAT|0666);
	if(shmid <=0){
		printf("shmget error!!\n");
		exit(0);
	}
	return shmid;
}



main()
{
	int shmid = init(shmkey);

	sem1 = sem_init(semkey1,1);
	
	while(1)
	{
		
	}
}
