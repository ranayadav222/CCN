#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

int timeout_msecs =500;

struct message
{
	int id;
	long mtype;
	char mtext[5000];
};
main()
{
	int c[4];
	struct pollfd fser ; int flag=0;
	int sid=msgget(1234,IPC_CREAT|0666);
	//c[0]=msgget(101,IPC_CREAT|0666);
	//c[1]=msgget(102,IPC_CREAT|0666);
	//c[2]=msgget(103,IPC_CREAT|0666);
	//c[3]=msgget(104,IPC_CREAT|0666);


	
	struct message sbuf,rbuf;
	
	fser.events = POLLIN;
	char *clist[]={"c1","c2","c3","c4"};
	int i=0;
	int j=0;
//	char buf[1024];
	printf("working\n");
	while(1)
	{
		//int ret = poll(&fser,1,timeout_msecs);
		
		//if(ret>0){
		
		//printf("ok%d\n",i);
		if(msgrcv(sid, &rbuf, sizeof(rbuf), 0, 0)<=0)
		{
			//printf("error!!\n");
			//flag=1;
		}
		else
		{
			flag=1;
			//printf("okk\n");
		}

		//printf("%s \n %d \n",rbuf.mtext,rbuf.id);
		//msgrcv(sid, &rbuf, sizeof(rbuf)-sizeof(long), 0, 0);	
		//fprintf(stdout,"%s",rbuf.mtext);
		sbuf.mtype=1;
		strcpy(sbuf.mtext, rbuf.mtext);
		sbuf.id=rbuf.id;
		//fprintf(stdout,"%s",sbuf.mtext);
		if(flag==1)
		{
			int ccc=msgget(sbuf.id,IPC_CREAT|0666);
			
			msgsnd(ccc,&sbuf,sizeof(sbuf),0);
			//printf("aaaaa");
		//for(j=0;j<4;j++)
		//{
				//printf("yes\n");
			
		//		msgsnd(c[j],&sbuf,sizeof(sbuf)-sizeof(long),0);
				//printf("done %d\n",j);
				//write(fds[j],buf,1024);
			
		}//
		//sbuf.mtext="";

		
	//}
	}
}