#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>

#define BUFFSIZE 100
#define NAMESIZE 20

int StoHEX(char fi, char sc);
void error_hendling(char *msg);
void *send_message(void *arg);
void *recv_message(void *arg);

int main(int argc, char **argv){
    int sock;
    int i;
    struct sockaddr_in serv_addr;

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if(sock == -1){
        printf("socket() error\n");
    }
    memset(&serv_addr, 0 , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port=htons(7989);

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
        printf("connect() error\n");
    }    
    
    unsigned char msg[100] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 1,2,3,4,2,1,2,3,0x0c};
    srand(time(NULL));
    while(1){
        for(i=0; i<15;i++){
            msg[i] = rand()%0xff;
        }
        printf("send : ");
        for(i=0; i<15; i++){
            printf("%02X ", msg[i]);
        }
        printf("\n");
        write(sock, msg, 15);
        sleep(5);
    }

    close(sock);
    return 0;

}

