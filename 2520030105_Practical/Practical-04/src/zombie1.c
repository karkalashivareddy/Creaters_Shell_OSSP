#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
int pid[3];
for(int i = 0;i<3;i++)
{
pid[i] = fork();
if(pid[i]==0)
{
printf("Child process %d pid = %d\n",i+1,getpid());
exit(0);
}
else{
printf("Parent process %d pid = %d\n",i+1,getpid());
sleep(40);
printf("Parent process complete\n");
}
}
}
