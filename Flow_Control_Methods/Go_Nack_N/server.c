#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

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
		printf("Accept\n");
	int repeat, val, count, i, frmno,flag;	
	repeat=0;

	while(1)
	{
		if (repeat!=1)   
		{
			recv(nsd, &val, sizeof(val), 0);
			printf("\nWindow size will be : %d\n", val);
		}
		if(val==0) break;
		count = -1, flag=0;
		for(i=0;i<val;i++)
		{
			recv(nsd, &frmno, sizeof(frmno), 0);
			count++;
			if(frmno!=count && flag!=1) 
			{
				flag=1;
				printf("Not received %d\n", count);
			}
			if(flag==0) printf("Received : %d\n",frmno);
			if(flag==1) printf("Discarded : %d\n",frmno);
		}
		if(flag==1){
			repeat = 1;
			printf("Error detected, requesting resend\n");
			send(nsd, &repeat, sizeof(repeat), 0);
			continue;
		}
		repeat = 0;
		printf("Success ! \n");
		send(nsd, &repeat, sizeof(repeat), 0);
	}
	printf("Bye\n");
	close(sd);
	close(nsd);
}
