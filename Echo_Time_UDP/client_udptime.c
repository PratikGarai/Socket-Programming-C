#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int csd,cport,len,serlen;
	char sendmsg[100],recvmsg[100];
	struct sockaddr_in servaddr, cliaddr;
	printf("Enter server port \n");
	scanf("%d",&cport);
	printf("Chose port : %d\n",cport);
	csd = socket(AF_INET, SOCK_DGRAM, 0);
	if(csd<0)
		printf("can't create\n");
	else
		printf("server is created\n");
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(cport);
	serlen = sizeof(servaddr);
	do
	{
		fgets(sendmsg,100,stdin);
		len = strlen(sendmsg);
		sendmsg[len-1]='\0';
		sendto(csd, sendmsg, 100, 0, (struct sockaddr*)&servaddr,sizeof(servaddr));
		recvfrom(csd, recvmsg, 100, 0,(struct sockaddr*)&servaddr,&serlen); 
		printf("Welcome to VIT UDP Time Server %s\n",recvmsg);
	}while(strcmp("bye",sendmsg));

	close(csd);
}
