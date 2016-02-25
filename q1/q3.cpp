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
int *pid,semr,semw;
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
	pid_t p;
	int shmid = init(shmkey);
//	int shmid=init(shmkey);
	semw=sem_init(semkey1,1);
	semr=sem_init(semkey2,0);
//	int shpid = init(pkey);
	char *spointer = (char*)shmat(shpid,NULL,0);
	char *bufr=new char[50];
	char *bufw=new char[50];
	int flag=0;
//	pid = (int*)shmat(shmid,NULL,0);
//	char *spointer = (char*)shmat(shpid,NULL,0);
	p=fork();
	if(p==0)
	{
		while(1)
		{
			s_wait(semr);
			cout<<"read 1 : "<<spointer<<endl;
			s_signal(semw);
			cout<<"Enter 1: ";
			cin>>bufw;
			srintf(spointer,bufw);
			s_wait(semw);
			s_signal(semr);
			sleep(1);
			s_signal(semw);

		}
	}
	else
	{
		while(1)
		{
			if(flag==1)
			{
				s_wait(semr);
				cout<<"read 2 : "<<spointer<<endl;
			}
			flag=1;

			s_wait(semw);
			cout<<"enter 2 :";
			cin>>bufw;
			srintf(spointer,bufw);
			
			s_signal(semr);
			sleep(1);
		}
	}
}