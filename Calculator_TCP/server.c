#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

char a[10];
char* compute(char* message)
{
	int found1=0;
	float n1=0.0, n2=0.0, result;
	char op;
	if(strcmp(message,"")==0)
		return "";
	if(strcmp(message,"bye")==0)
		return "Thank You! ";
	for(int i=0;i<19;i++)
	{
		if(isdigit(message[i])&&found1==0)
		{
			n1 = n1*10 + (float)message[i] - 48.0;
		}
		else if(isdigit(message[i])&&found1==1)
		{
			n2 = n2*10 + (float)message[i] - 48.0;
		}
		else if(!isdigit(message[i])&&(found1==0))
		{
			op = message[i];
			printf("operator received %c\n",op);
			found1 = 1;
		}
		else if(!isdigit(message[i])&&(found1==1))
			break;
	}	
	if(op=='+')
		result = n1+n2;
	else if(op=='-')
		result = n1-n2;
	else if(op=='*')
		result = n1*n2;
	else if(op=='/')
		result = n1/n2;
	printf("result :  %f\n",result);
 	sprintf(a,"%f",result);
	return(a);
}

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
	printf("Client address : %s\n",inet_ntoa(cliaddr.sin_addr));
	while(strcmp(rcvmsg,"bye")!=0)
	{
		recv(nsd, rcvmsg, 20, 0);
		printf("%s\n",rcvmsg);
		strcpy(sendmsg,compute(rcvmsg));
		len = strlen(sendmsg);
		sendmsg[len-1]='\0';
		send(nsd,sendmsg,20,0);
	}
	close(sd);
	close(nsd);
}
