#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{
	int sd,sd2,nsd,clilen,sport,len,port,count,val,i;
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
		printf("Accept\n");
	recv(nsd, &val, sizeof(val), 0);
	count = val;
	while(1)
	{
		i = recv(nsd,rcvmsg, sizeof(rcvmsg), 0);
		rcvmsg[i]='\0';
		if(strcmp(rcvmsg,"end")==0)
		{
			printf("Finished\n");
			break;
		}
		if (count!=val)
		{
			strcpy(sendmsg, "frame missing\0");
			send(nsd,&count,sizeof(count),0);
			send(nsd,sendmsg,sizeof(sendmsg),0);
		}
		else
		{
			printf("The frame number is :%d\n\n", val);
			printf("The data is : %s\n", rcvmsg);
			count++;
			strcpy(sendmsg, "send next frame\0");
			send(nsd,&count,sizeof(count),0);
			send(nsd,sendmsg,sizeof(sendmsg),0);
		}
		printf("The expected frame now is %d\n", count);
		recv(nsd,&val,sizeof(val), 0);
	}
	close(sd);
	close(nsd);
}
