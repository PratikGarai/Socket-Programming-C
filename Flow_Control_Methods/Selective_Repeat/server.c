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
	int repeat,val,i,frmno,size, nxt=0;	
	repeat=0;
	printf("Enter the window size\n");
	scanf("%d",&size);
	send(nsd, &size, sizeof(size), 0);
	int a[size];
	for(i=0;i<size;i++) a[i]=0;
	do{
		repeat = 0;
		for(i=0;i<size;i++)
		{
			if(a[i]==1)  continue;
			if(a[i]==0 && nxt==1)    printf("Resend frame %d\n",i);
			else     printf("Expected frame number : %d\n",i);
			printf("Enter frame : ");
			scanf("%d",&frmno);
			send(nsd, &frmno, sizeof(frmno), 0);
			recv(nsd, &val, sizeof(val), 0);
			if(val==0) repeat = 1;
			a[i] = val;
		}
		nxt = 1;
	}while(repeat==1);
		printf("Bye\n");
	close(sd);
	close(nsd);
}
