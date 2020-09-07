#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int sd,sd2,nsd,clilen,sport,len,port;
	char sendmsg[100],rcvmsg[100];
	struct sockaddr_in servaddr, cliaddr;
	printf("enter server port\n");
	scanf("%d",&sport);
	printf("Selected port : %d\n",sport);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd<0)
		printf("can't create\n");
	else
		printf("Socket is created\n");
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(sport);
	sd2 = bind(sd,(struct sockaddr*)&servaddr, sizeof(servaddr));
	if(sd2<0)
		printf("can't bind\n");
	else
		printf("Binded\n");
	listen(sd,5);
	clilen = sizeof(cliaddr);
	nsd = accept(sd,(struct sockaddr*)&cliaddr, &clilen);
	if(nsd<0)
		printf("can't accept");
	else
		printf("Accept");
	printf("Client address : %s",inet_ntoa(cliaddr.sin_addr));
	close(sd);
	close(nsd);
}
