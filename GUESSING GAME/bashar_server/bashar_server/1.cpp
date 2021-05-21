#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include<conio.h>
#include<time.h>
#pragma comment(lib,"ws2_32.lib")
DWORD WINAPI reciv(LPVOID s){
SOCKET new_client=(SOCKET) s;
char name[20];
char num[20];
int number;
int name_rec=recv(new_client,name,20,0);
name[name_rec]=NULL;
srand((unsigned) time(NULL));
int counter=1;
printf("%s is connected...\n",name);
int rand_num=rand()%1000+1;
printf("the secret number for %s is : %d\n",name,rand_num);
while(1){
	int get_size = recv(new_client , num , 20 , 0);
	if (get_size==SOCKET_ERROR){printf("%s has disconnected\n",name);return NULL;}
	number=atoi(num);
	if(number>rand_num){
		char *res="this number is bigger than our number try again..";
		send(new_client,res,strlen(res),0);
	}
	else if(number<rand_num){
		char *res="this number is smaller than our number try again..";
		send(new_client,res,strlen(res),0);
	}
	else{
		send(new_client,"ok",2,0);
		char res[]="you won the game after ";
		char r[10];
		itoa(counter, r, 10);
		strcat(res,r);
		strcat(res," tries...");
		send(new_client,res,strlen(res),0);
		rand_num=rand()%1000+1;
		counter=0;
		printf("the secret number for %s is : %d\n",name,rand_num);
	}
	counter++;
}
return NULL;
}

int main(){
 
 WSADATA wsa;
 SOCKET s , new_socket;
 struct sockaddr_in server , client;
    int c;
    char *message,server_reply[2000];

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return NULL;
    }

    printf("Initialised.\n");

    
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");

    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 2015 );

   
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
    }

    puts("Bind done");

    
    listen(s , 5);

    
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
	DWORD thread;
	while(1){
    new_socket = accept(s , (struct sockaddr *)&client, &c);
	puts("Connection accepted");
	CreateThread(NULL, 0,reciv,(LPVOID)new_socket, 0, &thread);
	} 

    
 

    closesocket(s);
    WSACleanup();

    return 0;

}