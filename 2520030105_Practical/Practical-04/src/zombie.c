#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
int pid;
pid = fork();
if(pid==0)
{
printf("Child process %d\n",getpid());
exit(0);
}
else
{
printf("Parent process %d\n",getpid());
wait(NULL);
//sleep(30);
printf("Parent process completed\n");
}
} 
//ps es-l|grep Z
