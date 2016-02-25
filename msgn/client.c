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
int flag =0;
int f,fs;
char ar[512];
struct message sbuf,rbuf;
int sid;
char cl[5];

struct message
{
	int id;
	long mtype;
	char mtext[5000];
};
void *readfifo(void *num){
		while(1){
			
				char buf[1024];
				//printf("before\n");

				if(msgrcv(f, &rbuf, sizeof(rbuf), 0, 0)>=0)
				{
					//printf("aaaaa");
					fprintf(stdout,"%s\n",rbuf.mtext);
					//printf("bbbbb");
					//sleep(0.5);
					//printf("read error\n");
				}
				
				//fprintf(stdout,"%s\n",rbuf.mtext);
		}
}
void *writefifo(void *num){
      
      while(1){
      	
      	char buf[512];
      	char b[512] ;
      	
      	

      	
      	fscanf(stdin,"%s",b);
      	
		strcpy(buf,ar);
      	strcat(buf,":-");
      	strcat(buf,b);
      	
      	
      	sbuf.id=atoi(ar);
      	sbuf.mtype=1;
		strcpy(sbuf.mtext,buf);
		//printf("sid= %d",sbuf.id);
		//printf("msg is : %s",sbuf.mtext);
		//printf("ccccc");
      	msgsnd(sid,&sbuf,sizeof(sbuf),0);
 		//printf("ddddd");
      	//write(fs,buf,sizeof(buf));
      } 
}
int main(int argc,char *argv[]){
	if(argc <2)
	{
		printf("arguement missing!! \n");
		exit(0);
	}
	//struct message sbuf,rbuf;
	strcpy(ar,argv[1]);
	sid=msgget(1234,IPC_CREAT|0666);

	//fs = open("cs",O_WRONLY);
	printf("%s\n",argv[1]);
	f=msgget(atoi(ar),IPC_CREAT|0666);
	//f = open(argv[1],O_RDONLY);
	
	
	pthread_t rthread,wthread;
	pthread_create(&rthread,NULL,readfifo,(void*)0);
	pthread_create(&wthread,NULL,writefifo,(void*)0);
	pthread_join(rthread,NULL);
	pthread_join(wthread,NULL);
}