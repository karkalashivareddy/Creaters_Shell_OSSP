#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

int main(){
char *fifo1="fifo1";
char *fifo2="fifo2";
char msg[100];
mkfifo(fifo1,0666);
mkfifo(fifo2,0666);
int fd1=open(fifo1,O_RDONLY);
read(fd1,msg,sizeof(msg));
printf("Client: %s\n",msg);
close(fd1);
printf("Enter response: ");
fgets(msg,sizeof(msg),stdin);
int fd2=open(fifo2,O_WRONLY);
write(fd2,msg,strlen(msg)+1);
close(fd2);
return 0;
}
