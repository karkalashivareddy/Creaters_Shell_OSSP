#include <stdio.h>
#include <unistd.h>
#include <stdio.h> 
#include <sys/wait.h>
#include<time.h>
int main()
{
int fd[2];
int data;
int start, end;
double eff;
double time;
pipe(fd);
start = clock();
if(fork()==0)
{
close(fd[1]);
printf("Consumer\n");
for(int i = 0;i<5;i++)
{
read(fd[0],&data,sizeof(data));
printf("Consumed %d\n",data);
}
close(fd[0]);
}
else
{
close(fd[0]);
printf("Producer \n");
for(int i = 1;i<=5;i++)
{
data = i * 10;
write(fd[1],&data,sizeof(data));
printf("Prodeuced %d\n",data);
}
close(fd[1]);
wait(NULL);
end = clock();
time = (double)(end-start)/CLOCKS_PER_SEC;
printf("Communication time is %lf\n",time);
eff = (double)5 / time;
printf("Communication Efficiency is %lf\n",eff);
}
}
