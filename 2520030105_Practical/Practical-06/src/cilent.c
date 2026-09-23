#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(){
char *fifo1="fifo1";
char *fifo2="fifo2";
char msg[100];
printf("Enter message: ");
fgets(msg,sizeof(msg),stdin);
int fd1=open(fifo1,O_WRONLY);
write(fd1,msg,strlen(msg)+1);
close(fd1);
int fd2=open(fifo2,O_RDONLY);
read(fd2,msg,sizeof(msg));
printf("Server: %s\n",msg);
close(fd2);
return 0;
}
