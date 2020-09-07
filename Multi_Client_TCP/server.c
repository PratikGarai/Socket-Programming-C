#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h>
     
#define PORT 60000 
     
int main(int argc , char *argv[])   
{   
    time_t ticks;
    int opt = 1;   
    int master_socket,addrlen,new_socket,client_socket[30],max_clients = 30,activity,i,valread,sd,i1;   
    int max_sd;   
    struct sockaddr_in address;   
    char buffer[1025];
    fd_set readfds;   
    char *message = "Server Acknowledgement\n";   
    for (i = 0; i < max_clients; i++)   
    {   
        client_socket[i] = 0;   
    }   
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)   
    {   
        perror("Socket error");   
        exit(1);   
    }   
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  
          sizeof(opt)) < 0 )   
    {   
        perror("Setsockopt error");   
        exit(1);   
    }   
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons( PORT );   
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)   
    {   
        perror("Bind failed");   
        exit(1);   
    }   
    printf("Listener on port %d \n", PORT);   
    if (listen(master_socket, 3) < 0)   
    {   
        perror("Listen error");   
        exit(1);   
    }   
    addrlen = sizeof(address);   
    puts("Waiting for clients ...");   
    while(1)   
    {   
        FD_ZERO(&readfds);   
        FD_SET(master_socket, &readfds);   
        max_sd = master_socket;   
        for (i=0;i<max_clients;i++)   
        {   
            sd = client_socket[i];   
            if(sd > 0)   
                FD_SET( sd , &readfds);   
            if(sd > max_sd)   
                max_sd = sd;   
        }   
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);   
        if ((activity < 0) && (errno!=EINTR))   
        {   
            printf("select error");   
        }   
        if (FD_ISSET(master_socket, &readfds))   
        {   
            if ((new_socket = accept(master_socket,  
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)   
            {   
                perror("Accept error");   
                exit(1);   
            }   
            printf("New connection in port : %d\n",ntohs(address.sin_port));   
            if(send(new_socket, message, strlen(message), 0) != strlen(message))   
            {   
                perror("Send error");   
            }   
            for(i=0;i<max_clients;i++)   
            {   
                if(client_socket[i] == 0 )   
                {   
                    client_socket[i] = new_socket;   
                    break;   
                }   
            }   
        }   
        for(i=0;i<max_clients;i++)   
        {   
            sd = client_socket[i];   
            if (FD_ISSET(sd,&readfds))   
            {   
                if ((valread = read(sd,buffer,1024))==0)   
                {   
                    getpeername(sd,(struct sockaddr*)&address,(socklen_t*)&addrlen);   
                    printf("Client disconnected from  port %d\n",ntohs(address.sin_port));   
                    close(sd);   
                    client_socket[i] = 0;   
                }   
                else 
                {   
                    buffer[valread]='\0';   
		    for(int i1=0;i1<max_clients;i1++)
	            {
			if(i1!=i)
			{
    			    char f_buffer[1031]; 
			    f_buffer[0]='U';
			    f_buffer[1]='s';
			    f_buffer[2]='e';
			    f_buffer[3]='r';
			    f_buffer[5]=':';
			    f_buffer[4] = (char)(i+1)+'0';
			    strcat(f_buffer, buffer);
                            send(client_socket[i1],f_buffer,strlen(f_buffer),0);   
			    memset(f_buffer,'\0',1031);
			}
		    }
                }   
            }   
        }   
    }   
    return 0;   
}   
