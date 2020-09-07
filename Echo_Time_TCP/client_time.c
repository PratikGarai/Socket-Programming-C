#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int csd,cport,len;
	char sendmsg[150],recvmsg[150];
	struct sockaddr_in servaddr, cliaddr;
	printf("Enter server port \n");
	scanf("%d",&cport);
	printf("Chose port : %d\n",cport);
	csd = socket(AF_INET, SOCK_STREAM, 0);
	if(csd<0)
		printf("can't create\n");
	else
		printf("server is created\n");
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(cport);
	if(connect(csd,(struct sockaddr*)&servaddr, sizeof(servaddr))<0)
		printf("can't connect\n");
	else
		printf("Connected\n");
	do
	{
		fgets(sendmsg,100,stdin);
		len = strlen(sendmsg);
		sendmsg[len-1]='\0';
		send(csd,sendmsg,100,0);
		recv(csd, recvmsg, 100, 0);
		printf("Welcome to VIT Time Server : %s\n",recvmsg);
	}while(strcmp("bye",sendmsg));

	close(csd);
}
