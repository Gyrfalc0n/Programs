#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define buffer_size 256

int main(int argc,char *argv[]){
    int sockfd,portno,n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[buffer_size];

    if(argc<3){
        fprintf(stderr,"usage %s hostname port\n",argv[0]);
        exit(0);
    }
    portno=atoi(argv[2]);

    /*Create a socket point*/
    sockfd=socket(PF_INET,SOCK_STREAM,0);

    server=gethostbyname(argv[1]);

    //bzero((char*)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    bzero(server, buffer_size);
    bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);//identique à memcpy
    serv_addr.sin_port=htons(portno);

    /*Now connect to the server*/
    connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    /*Now ask for a message from the user,this message will be read by server*/
    printf(" > ");
    bzero(buffer,buffer_size);
    fgets(buffer,buffer_size-1,stdin);

    /*Send message to the server*/
    n=write(sockfd,buffer,strlen(buffer));

    /*Now read server  response*/
    bzero(buffer,buffer_size);
    n=read(sockfd,buffer,buffer_size-1);

    printf("%s\n",buffer);
    return 0;
}