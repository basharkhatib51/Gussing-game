#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
	char name[20],num[10],s_r[100];
	char ip[20];
    int recv_size;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");

	printf("enter server ip : ");
	gets(ip);
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons( 2015 );

   
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

	puts("enter your name :");
	gets(name);

	send(s , name , strlen(name) , 0);
	printf("try to guess our number its between 1 and 1000:\n");
	bool is_win=false;
	while(1){
	printf("enter number:\n");
	gets(num);
	send(s , num , strlen(num) , 0);
	recv_size=recv(s,s_r,100,0);
	if(s_r[0]=='o' && s_r[1]=='k'){
		is_win=true;
		recv_size=recv(s,s_r,100,0);
		s_r[recv_size]=NULL;
		printf("%s\n",s_r);
	}
	else{
		s_r[recv_size]=NULL;
		printf("%s\n",s_r);
	}
	if(is_win==true){
		puts("play another game..");
		is_win=false;
	}
	}
    return 0;
	
}