//both way communication between processes using shared memory 
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;
main()
{
	pid_t pid;
	int local;
	int sid1,sid2;
	sid1=shmget(IPC_PRIVATE,1024,S_IRUSR|S_IWUSR);	
	sid2=shmget(IPC_PRIVATE,1024,S_IRUSR|S_IWUSR);
	
	pid=fork();
	if(pid==0)
	{
		char *shared_memory1=(char *)shmat(sid1,NULL,0);
		char *shared_memory2=(char *)shmat(sid2,NULL,0);
		sprintf(shared_memory2,"NIT Trichy");
		cout<<shared_memory1;
		cout<<endl;
		shmdt(shared_memory1);
		shmdt(shared_memory2);
	}
	else
	{
		char *shared_memory1=(char *)shmat(sid1,NULL,0);
		sprintf(shared_memory1,"NIT WARANGAL");
		wait(&local);
		char *shared_memory2=(char *)shmat(sid2,NULL,0);
		cout<<shared_memory2;
		cout<<endl;
		shmdt(shared_memory1);
		shmdt(shared_memory2);
	}
}
