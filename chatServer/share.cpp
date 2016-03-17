#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
using namespace std;
main()
{
	char buf[50];
	int local;
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		int local1=5678;
		int sid=shmget(local1,1024,IPC_CREAT);
		sprintf(buf,"shared memory");
	}

	else
	{
		wait(&local);
		int shared_memory=(char *)shmat(sid,NULL,0);
		shared_memory=sprintf(shared_memory,"NIT WARANGAL");

	}
}
