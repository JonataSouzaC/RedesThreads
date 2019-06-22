/*-------------------Echo_client.cpp-------------------*/
#include <windows.h>
#include <winsock.h>
#include <iostream>
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
//#include <iostream.h>
#include <conio.h>
#include <signal.h>
#include <stdio.h>
 using namespace std;
//DECLARATIONS
    //error trapping signals
      #define SIGINT 2
      #define SIGKILL 9
      #define SIGQUIT 3
    // SOCKETS
      SOCKET sock,client;
 
void s_handle(int s)
{
    if(sock)
       closesocket(sock);
    if(client)
       closesocket(client);
    WSACleanup();
    Sleep(1000);
    cout<<"EXIT SIGNAL :"<<s;
    exit(0);
}
 
 
void s_cl(char *a, int x)
{
    cout<<a;
    s_handle(x+1000);
}
 
 
int main()
{
   HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
   SetConsoleTitle(".:: Basic Echo Client By KOrUPt 07 ::. ");
     
      srand (time(NULL));
 
    //Declarations
    DWORD poll;
    int res,i=1,port=999;
    char buf[100];
    char msg[100] = "";
    char ip[15];
    WSADATA data;
     
    signal(SIGINT,s_handle);
    signal(SIGKILL,s_handle);
    signal(SIGQUIT,s_handle);
     
    cout<<"\t\tEcho Client by KOrUPt";
     
    cout<<"\n\n\n\t\tEnter IP to connect to: ";
    gets(ip);
     
    sockaddr_in ser;
    sockaddr addr;
     
     
    ser.sin_family=AF_INET;
    ser.sin_port=htons(123);                    //Set the port
    ser.sin_addr.s_addr=inet_addr(ip);      //Set the address we want to connect to
     
    memcpy(&addr,&ser,sizeof(SOCKADDR_IN));
     
    res = WSAStartup(MAKEWORD(1,1),&data);      //Start Winsock
    cout<<"\n\nWSAStartup"
        <<"\nVersion: "<<data.wVersion
        <<"\nDescription: "<<data.szDescription
        <<"\nStatus: "<<data.szSystemStatus<<endl;
 
    if(res != 0)
        s_cl("WSAStarup failed",WSAGetLastError());
 
    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);       //Create the socket
        if(sock==INVALID_SOCKET )
            s_cl("Invalid Socket ",WSAGetLastError());
        else if(sock==SOCKET_ERROR)
            s_cl("Socket Error)",WSAGetLastError());
        else
            cout<<"Socket Established"<<endl;
     
 
     
    res=connect(sock,&addr,sizeof(addr));               //Connect to the server
        if(res !=0 )
        {
            s_cl("SERVER UNAVAILABLE",res);
        }
        else
        {
            cout<<"\nConnected to Server: ";
            memcpy(&ser,&addr,sizeof(SOCKADDR));
        }
     
    char RecvdData[100] = "";
    int ret;
	buf[0] = 'h';
	buf[1] = 'e';
	buf[2] = 'l';
	buf[3] = 'l';
	buf[4] = 'o';
	int aux=0;
    for(int i=0; i<100000; i++)
    {
        //strcpy(buf,"");
        //cout<<"\nEnter message to send ->\n";
        //fgets(buf,sizeof(buf),stdin);
        aux = rand()%7;
        
		if(aux == 0){
			buf[0] = 't';
			buf[1] = 'v';
			buf[2] = '4';
			buf[3] = '2';
			buf[4] = '\0';			 
		 }
      
	else  if(aux == 1){
			buf[0] = 'c';
			buf[1] = 'o';
			buf[2] = 'm';
			buf[3] = 'p';
			buf[4] = 'u';
			buf[5] = 't';
			buf[6] = 'a';
			buf[7] = 'd';
			buf[8] = 'o';
			buf[9] = 'r';
			buf[10] = '\0';
		 }
		 
	else if(aux == 2){
			buf[0] = 'p';
			buf[1] = 's';
			buf[2] = '4';
			buf[3] = '\0';
		 }
		 
	else	 if(aux == 3){
			buf[0] = 'c';
			buf[1] = 'e';
			buf[2] = 'l';
			buf[3] = 'u';
			buf[4] = 'l';
			buf[5] = 'a';
			buf[6] = 'r';
			buf[7] = '\0';
		 }
		 
	else	 if(aux == 4){
			buf[0] = 'x';
			buf[1] = 'b';
			buf[2] = 'o';
			buf[3] = 'x';
			buf[4] = '-';
			buf[5] = '3';
			buf[6] = '6';
			buf[7] = '0';
			buf[8] = '\0';
		 }
		 
	else	if(aux == 5){
			buf[0] = 'x';
			buf[1] = 'b';
			buf[2] = 'o';
			buf[3] = 'x';
			buf[4] = '-';
			buf[5] = 'o';
			buf[6] = 'n';
			buf[7] = 'e';
			buf[8] = '\0';
		 }
		 
		 else{
			buf[0] = 'x';
			buf[1] = '\0';
		
		 }
        //Sleep(5); 
        res = send(sock,buf,sizeof(buf),0); 
          
         if(res==0)
         {  
            //0==other side terminated conn
            printf("\nSERVER terminated connection\n");
            Sleep(40);
            closesocket(client);
            client = 0;
            break;
         }
         else if(res==SOCKET_ERROR)
         {  
            //-1 == send error
            printf("Socket error\n");
            Sleep(40);
            s_handle(res);
            break;
         }
        
       ret = recv(sock,RecvdData,sizeof(RecvdData),0);
       if(ret > 0)
       { 
        cout<<endl<<RecvdData;
        strcpy(RecvdData,"");
       }
    }   
     
    closesocket(client);
    WSACleanup();
}