#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler(int sig){
if(sig==SIGINT)
printf("SIGINT received\n");
else if(sig==SIGTERM)
printf("SIGTERM received\n");
else if(sig==SIGUSR1)
printf("SIGUSR1 received\n");
}

int main(){
signal(SIGINT,handler);
signal(SIGTERM,handler);
signal(SIGUSR1,handler);
printf("Process ID: %d\n",getpid());
while(1){
printf("Running...\n");
sleep(2);
}
return 0;
}
