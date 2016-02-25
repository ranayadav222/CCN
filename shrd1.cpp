#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
using namespace std;
struct message
{
	long mtype;
	char mtext[5000];
};
int main()
{
	int key =1235;
	int msqid=msgget(1234,IPC_CREAT|0666);
	int cid=msgget(key, IPC_CREAT|0666);
	struct message sbuf,rbuf;
	char mtext[1000];
	int p=0;
	p=fork();
	if(p==0)
	{
		while(1)
		{
			fgets(mtext, 100, stdin);
			sbuf.mtype=1;
			strcpy(sbuf.mtext, mtext);
			msgsnd(msqid,&sbuf,sizeof(sbuf)-sizeof(long),0);
		}
	}
	else
	{	while(1)
		{
			msgrcv(cid, &rbuf, sizeof(rbuf)-sizeof(long), 0, 0);
			printf("%s\n", rbuf.mtext);
		}
	}
	return 0;
}