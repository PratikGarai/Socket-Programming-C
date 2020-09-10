#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int csd,cport,len,i,val,count;
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
	while(1)
	{
		printf("Enter frame number : ");
		scanf("%d", &val);
		send(csd, &val, sizeof(val), 0);
		printf("Enter data : ");
		scanf("%s", sendmsg);
		len= strlen(sendmsg);
		sendmsg[len]='\0';
		send(csd, sendmsg, sizeof(sendmsg), 0);
		if (strcmp(sendmsg,"end")==0)
			break;
		recv(csd, &count, sizeof(count), 0);
		i = recv(csd, recvmsg, sizeof(recvmsg), 0);
		recvmsg[i] = '\0';
		printf("%s %d\n",recvmsg, count);
	}

	close(csd);
}
