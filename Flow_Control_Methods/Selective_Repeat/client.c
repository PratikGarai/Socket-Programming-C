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
	int repeat,val,i,frmno, size, nxt =0;	
	repeat=0;
	recv(csd,&size, sizeof(size), 0);
	int a[size];
	for(i=0;i<size;i++) a[i]=0;
	do{
		repeat = 0;
		for(i=0;i<size;i++)
		{
			if(a[i]==1)  continue;
			if(a[i]==0 && nxt==1)    printf("Requesting re-send %d\n",i);
			val = 1;
			recv(csd, &frmno, sizeof(frmno), 0);
			printf("Frame number received : %d",frmno);
			if(frmno!=i){
				val = 0;
				printf("   Wrong frame");
				repeat = 1;
			}
			printf("\n");
			send(csd, &val, sizeof(val), 0);
			a[i] = val;
		}
		nxt = 1;
	}while(repeat==1);

	printf("Bye!\n");
	close(csd);
}
