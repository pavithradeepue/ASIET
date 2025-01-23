#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
void main(){
	int status,pid,child_pid;
	pid = fork();
	if(pid == -1)
	{
		printf("Child process creation Failed!\n");
		exit(0);
	}
	else if(pid == 0){
		printf("Child process id: %d\n",getpid());
		execl("/bin/date","date",NULL);
		exit(0);
	}
	else{
		child_pid=wait(&status);
		printf("Inside child process id: %d\n",getpid());
		printf("Child Process created successfully.\n");
	}
}
