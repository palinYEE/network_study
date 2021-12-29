#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLEN_MAX 10

int g_clnt_socks[CLEN_MAX];
int g_clnt_count = 0;

int main(int argc, char ** argv){
    int serv_sock;
    int clnt_sock;
    int clnt_addr_size;
    int i=0;
    struct sockaddr_in serv_addr, clnt_addr;
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // ipv4를 사용하고 tcp 통신 사용, 0을 넣음으로써 앞에 변수를 참조해서 해당 프로토콜을 넣어준다.

    /* 바인드 정보 */ 
    serv_addr.sin_family = AF_INET; 
    /* 소켓 바인드 할 떄 어떤 주소로 할것인가. */
    /* htonl(INADDR_ANY): 현재 내 pc ip 주소*/
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* 포드 번호 */
    serv_addr.sin_port = htons(7989);

    if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
        printf("bind error\n");
    }

    /* queue 크기? */
    if(listen(serv_sock, 5) == -1){
        printf("listen error\n");
    }

    char buff[200];
    int recv_len = 0;
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        

    //g_clnt_socks[g_clnt_count++] = clnt_sock;
    while(1){
        recv_len = read(clnt_sock, buff, 200);
        if(recv_len > 0){
            printf("recv : ");
            for(i=0; i<recv_len; i++){
                printf("%02X ", (unsigned char)buff[i]);
            }
            printf("\n");
        }

    }
}