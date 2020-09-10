#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int csd,cport,len;
	char sendmsg[100],recvmsg[100];
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
	int repeat, val, count, i, frmno;	
	repeat = 0;
	while(1)
	{
		if(repeat!=1)
		{
			printf("Enter the window size  :  ");
			scanf("%d", &val);
			printf("\n");
			send(csd, &val, sizeof(val), 0);
			if(val==0) break;
		}
		for(i=0;i<val;i++)
		{
			printf("Enter frame number  :  ");
			scanf("%d", &frmno);
			send(csd, &frmno, sizeof(frmno), 0);
		}
		recv(csd, &repeat, sizeof(repeat), 0);
		if(repeat==1) 
		{
			printf("Error! Send window again\n\n");
			continue;
		}
		printf("Window received successfully!\n\n");
		repeat = 0;
	}
	printf("Bye!\n");
	close(csd);
}
