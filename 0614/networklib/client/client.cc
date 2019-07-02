#include "../../../spellcorrectServer/include/json/json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
using namespace std;
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);

int main(int argc, const char *argv[])
{
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("101.132.112.0"); //localhost
    //addr.sin_addr.s_addr = INADDR_ANY; //localhost
    addr.sin_port = htons(8888);
    socklen_t len = sizeof addr;
    if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
        ERR_EXIT("Connect");

	char buf[1024];
	memset(buf, 0, sizeof(buf));
    int slen ;
    read(peerfd, (char*)&slen, 4);
	read(peerfd, buf, slen);
	printf("%s\n", buf);

    do_service(peerfd);
    return 0;
}



void do_service(int sockfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while(1)
    {
        fgets(sendbuf, sizeof sendbuf, stdin);
        write(sockfd, sendbuf, strlen(sendbuf));
		//sleep(5);

        //read
        int nread = read(sockfd, recvbuf, 102400);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("read");
        }
        else if(nread == 0) //代表链接断开
        {
            printf("server close!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }
        cout << string(recvbuf) << endl;
#if 0
        Json::Reader readd;
        Json::Value val;
        readd.parse(recvbuf,val);
        Json::StyledWriter writ;
        cout << writ.write(val) << endl;
        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
#endif
    }
}




