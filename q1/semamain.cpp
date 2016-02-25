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
int *pid,sem1,sem2;
void s_wait (int semid){
	struct sembuf se = {0,-1,0};
	semop(semid,&se,1);
}
void s_signal (int semid){
	struct sembuf se = {0,1,0};
	semop(semid,&se,1);
}


main()
{
	int i=0;
	fstream f;
	int j;
	
	s_wait(sem1);
	
	while(i<5)
	{
		f.open("File.txt",ios::in);
		while(!f.eof())
				f>>j;
		j++;
		f.close();
		cout<<"Writing "<<j<<endl;
		f.open("File.txt",ios::out);
		f<<j;
		f.close();
				sleep(1);
		i++;
	}

s_signal(sem1);
}