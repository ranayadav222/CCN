#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<cstdlib>
#include<sys/wait.h>
#include<sys/types.h>
#include<string>

using namespace std;

main()
{	
	char buf[500];
	int fd[2];
	//int local=0;
	//pipe(fd);
	if(pipe(fd)<0)
		cout<<"error";
	pid_t pid,pid1;
	pid=fork();
	if(pid==0)
	{
		//cout<<"child : "<<endl;
		//close(1);
		dup2(fd[1],1);
		execlp("who","who",NULL);
		close(fd[1]);
	}
	else
	{
		wait(NULL);
		//cout<<"parent : "<<endl;
		close(fd[1]);
		dup2(fd[0],0);
		//read(fd[0],buf,sizeof(buf));
		//cout<<buf<<endl;
		execlp("wc","wc","-l",NULL);
		//pid1=fork();
		//if(pid1==0)
	//	{
			/*close(fd[1]);
			read(fd[0],buf,10);
			cout<<buf;*/
			
		//}
	}
}
