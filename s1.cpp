#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
using namespace std;
int flag=1;
int cid,msqid,msqt;


struct message
{
	long mtype;
	char mtext[5000];
};
struct message sbuf,rbuf;
char mtext[1000];
void convert(char mtext[10],int i)
{
	int j=0;
	while(i>0)
	{
		mtext[j++]=i%10;
		i=i/10;
	}
	for(int i=0;i<j/2;i++)
	{
		mtext[i]=mtext[j-i];
	}
}


void *read(void *num)
{
	while(1)
	{
		if(flag==0)
		{
		/*for(int i=0;i<1000000;i++)
		{
			cout<<0;*/
			sleep(1);
			if(msgrcv(cid, &rbuf, sizeof(rbuf), 0, 0)>=0)
			{	
			//	cout<<6<<endl;
				flag==1;
				cout<<"ack recieved"<<endl;
				//break;
				//printf("ack recieved");
			}
		//}
		//cout<<7<<endl;
		if(flag!=1)
		{
			//cout<<8<<endl;
			printf("resending");
			flag=2;
		}
		}
	}
}

void *write(void *num)
{
	while(1)
	{
		if(flag==1)
		{
			//cout<<1<<endl;
			//int i=atoi(mtext);
			//i++;
			//convert(mtext,i);
			cout<<"enter msg : ";
			fgets(mtext, 100, stdin);
			sbuf.mtype=1;
			strcpy(sbuf.mtext, mtext);
			cout<<"sending -->>"<<sbuf.mtext<<"*"<<endl;
			msgsnd(msqid,&sbuf,sizeof(sbuf),0);
			flag=0;
			//cout<<2<<endl;
		}
		else if(flag==2)
		{
			//cout<<3<<endl;
			sbuf.mtype=1;
			strcpy(sbuf.mtext, mtext);
			//cout<<11<<endl;
			cout<<"sending -->>"<<sbuf.mtext<<"*"<<endl;
			msgsnd(msqid,&sbuf,sizeof(sbuf),0);
			flag=0;
			//cout<<4<<endl;
		}
	}
}
int main()
{
	int key =1235;
	msqid=msgget(key,IPC_CREAT|0666);
	cid=msgget(1234, IPC_CREAT|0666);
	msqt=msgget(1236,IPC_CREAT|0666);
	
	//int p=0;
	
	pthread_t th1,th2;
	pthread_create(&th1,NULL,read,(void*)0);
	pthread_create(&th2,NULL,write,(void*)0);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	return 0;
}
/*	p=fork();
	if(p==0)
	{
		while(1)
		{
			if(flag==1)
			{
				cout<<1<<endl;
				int i=atoi(mtext);
				i++;
				//convert(mtext,i);
			//fgets(mtext, 100, stdin);
				sbuf.mtype=1;
				strcpy(sbuf.mtext, mtext);
				msgsnd(msqid,&sbuf,sizeof(sbuf)-sizeof(long),0);
				flag=0;
				cout<<2<<endl;
			}
			else if(flag==2)
			{
				cout<<3<<endl;
				sbuf.mtype=1;
				strcpy(sbuf.mtext, mtext);
				msgsnd(msqid,&sbuf,sizeof(sbuf)-sizeof(long),0);
				flag=0;
				cout<<4<<endl;
			}
		}
	}
	else
	{	while(1)
		{
			cout<<5<<endl;
			for(int i=0;i<10000;i++)
			{
				if(msgrcv(cid, &rbuf, sizeof(rbuf)-sizeof(long), 0, 0)>=0)
				{	
					cout<<6<<endl;
					flag==1;
					printf("ack recieved");
				}
			}
			cout<<7<<endl;
			if(flag!=1)
			{
				cout<<8<<endl;
				printf("resending");
				flag=2;
			}
			cout<<9<<endl;
			//printf("%s\n", rbuf.mtext);
		}
	}
	return 0;
}
*/