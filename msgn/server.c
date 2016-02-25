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
	c[0]=msgget(101,IPC_CREAT|0666);
	c[1]=msgget(102,IPC_CREAT|0666);
	c[2]=msgget(103,IPC_CREAT|0666);
	c[3]=msgget(104,IPC_CREAT|0666);

	//printf("%d %d %d %d",c[0],c[1],c[2],c[3]);
	
	struct message sbuf,rbuf;
	
	fser.events = POLLIN;
	//char *clist[]={"c1","c2","c3","c4"};
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
			printf("error!!\n");
			//flag=1;
		}
		else
		{
			flag=1;
			printf("okk\n");
		}

		printf("aaaaa");
		//msgrcv(sid, &rbuf, sizeof(rbuf)-sizeof(long), 0, 0);	
		fprintf(stdout,"%s",rbuf.mtext);
		sbuf.mtype=1;
		sbuf.id=rbuf.id;
		strcpy(sbuf.mtext, rbuf.mtext);
		fprintf(stdout,"%s",sbuf.mtext);
		if(flag==1)
		{
			
		//for(j=0;j<4;j++)
		//{
			fprintf(stdout,"c[j] = %d",c[j]);
			printf("sbuf = %d",sbuf.id);
				//printf("yes\n");
				if(sbuf.id!=101)
					msgsnd(c[0],&sbuf,sizeof(sbuf),0);

				if(sbuf.id!=102)
					msgsnd(c[1],&sbuf,sizeof(sbuf),0);

				if(sbuf.id!=103)
					msgsnd(c[2],&sbuf,sizeof(sbuf),0);

				if(sbuf.id!=104)
					msgsnd(c[3],&sbuf,sizeof(sbuf),0);
				//printf("done %d\n",j);
				//write(fds[j],buf,1024);
			
		//}
		//sbuf.mtext="";

		
	//}
		}
	}
}