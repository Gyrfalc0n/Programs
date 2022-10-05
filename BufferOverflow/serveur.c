#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define buffer_size 10

void doprocessing (int sock){
    int n;
    char buffer[buffer_size];
    bzero(buffer,buffer_size);
    n=read(sock,buffer,buffer_size-1);
    printf(" Client > %s\n",buffer);
    n=write(sock,"Server > OK",20);
}

int main(int argc, char* argv[]){
    int sockfd, newsockfd, portno;
    unsigned int clilen;
    char buffer[buffer_size];
    struct sockaddr_in serv_addr,cli_addr;
    int n;
    pid_t pid;

    /* First call to socket() function */ 
    sockfd = socket(PF_INET, SOCK_STREAM, 0); 
     
    /* Initialize socket structure */ 
    bzero((char *) &serv_addr, sizeof(serv_addr)); 
    portno = 1234; 
     
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(portno); 
     
    /* Now bind the host address using bind() call.*/ 
    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
     
    /* Now start listening for the clients, here 
     * process will go in sleep mode and will wait 
     * for the incoming connection */ 
    printf("Server listening on port %d...\n", portno);
    listen(sockfd,5); 
    clilen = sizeof(cli_addr); 
     
    while(1) { 
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); 
         
        /* Create child process */ 
        pid = fork(); 
         
        if (pid == 0) { 
            /* This is the client process */ 
            close(sockfd); 
            doprocessing(newsockfd); 
            exit(0); 
        } 
        else { 
            close(newsockfd); 
        } 
    } /* end of while */ 
}