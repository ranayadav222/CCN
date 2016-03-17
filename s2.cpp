#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<pthread.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
using namespace std;
#define shmkey 1234
#define shmsize 4
int flag=0;
int cid,msqid;
char mtext[]={'1','\n'};
struct message
{
	long mtype;
	char mtext[5000];
};

struct message sbuf,rbuf;
int  init(int key){
	int shmid = shmget(key,shmsize,IPC_CREAT|0666);
	if(shmid <=0){
		printf("shmget error!!\n");
		exit(0);
	}
	return shmid;
}

void *read(void *num)
{
	while(1)
	{
		if(msgrcv(cid, &rbuf, sizeof(rbuf), 0, 0)>=0)
		{
			//cout<<66<<endl;
			cout<<rbuf.mtext<<endl;
			sbuf.mtype=1;
			strcpy(sbuf.mtext, mtext);
			msgsnd(msqid,&sbuf,sizeof(sbuf),0);		
		}
	}
}

void *write(void *num)
{
	while(1)
	{
/*		if(flag==1)
		{
			cout<<22<<endl;
			//fgets(mtext, 100, stdin);
			sbuf.mtype=1;
			strcpy(sbuf.mtext, mtext);
			msgsnd(msqid,&sbuf,sizeof(sbuf)-sizeof(long),0);
			flag=0;
			cout<<33<<endl;
		}
*/
	}
}

int main()
{
	int key =1235;
	msqid=msgget(1234,IPC_CREAT|0666);
	cid=msgget(key, IPC_CREAT|0666);
	//struct message sbuf,rbuf;
	
	//int p=0;
	//int flag=0;

	pthread_t th1,th2;
	pthread_create(&th1,NULL,read,(void *)0);
	pthread_create(&th2,NULL,write,(void *)0);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	return 0;

}

/*	p=fork();
	if(p==0)
	{
		while(1)
		{
			cout<<11<<endl;
			if(flag==1)
			{
				cout<<22<<endl;
				//fgets(mtext, 100, stdin);
				sbuf.mtype=1;
				strcpy(sbuf.mtext, mtext);
				msgsnd(msqid,&sbuf,sizeof(sbuf)-sizeof(long),0);
				flag=0;
				cout<<33<<endl;
			}
		}
	}
	else
	{	while(1)
		{
			cout<<44<<endl;
			if(flag==0)
			{
				cout<<55<<endl;
				for(int i=0;i<10000;i++)
				{
					if(msgrcv(cid, &rbuf, sizeof(rbuf)-sizeof(long), 0, 0)>=0)
					{
						cout<<66<<endl;
						flag=1;
						printf("%s\n", rbuf.mtext);
						break;
					}
				}
			}
			cout<<77<<endl;
		}
	}

	return 0;
}*/