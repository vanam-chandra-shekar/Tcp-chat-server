#include <cstdlib>
#include <cstring>
#include <minwindef.h>
#include <psdk_inc/_ip_types.h>
#include <psdk_inc/_socket_types.h>
#include <psdk_inc/_wsadata.h>
#include <winsock2.h>
#include <iostream>
#include <ws2tcpip.h>

using namespace std;

int main(){

    SOCKET serverSocket , acceptSocket;
    int port = 8080;

    WSADATA wsadata;
    WORD version = MAKEWORD(2, 2);

    //loading dll
    int werr = WSAStartup(version, &wsadata);
    if(werr != 0){
        cout<<"[Failure] DLL Not Loaded\n";
        WSACleanup();
    }else {
        cout<<"[Sucess] DLL Found\n";
    }

    //making socket
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverSocket == INVALID_SOCKET){
        cout<<"[Failure] At Socket()\n";
        WSACleanup();
    }else {
        cout<<"[Sucess] Socket made\n";
    }

    //Binding server
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET,"127.0.0.1",&service.sin_addr.S_un);
    service.sin_port = htons(port);

    if(bind(serverSocket,(SOCKADDR*)&service, sizeof(service))){
        cout<<"[Failure] At Bind\n";
        closesocket(serverSocket);
        WSACleanup();
    }else{
        cout<<"[Sucess] Binded\n";
    }

    //Listining
    if(listen(serverSocket, 1) == SOCKET_ERROR){
        cout<<"[Failure] At Listen\n";
        closesocket(serverSocket);
        WSACleanup();
    }else{
        cout<<"[Sucess] Listening\n";
    }

    //accepting

    acceptSocket = accept(serverSocket, NULL, NULL);
    if(acceptSocket == INVALID_SOCKET){
        cout<<"[Failure] At Accept\n";
        closesocket(serverSocket);
        WSACleanup();
    }else{
        cout<<"[Sucess] Accepting\n";
    }

    char buffer[200] = "";
    int recBytes = recv(acceptSocket, buffer, 200, 0);

    if(recBytes == SOCKET_ERROR){
        cout<<"[Faliure] : Unsucessful Recieve\n";
    }else {
        cout<<"[Sucess] : Message Recieved\n";
        cout<<"[Message] : ";

        printf("%s\n",buffer);

        const char* mssg = "HTTP/1.1 200 OK\r\n\r\nHello world!";

        send(acceptSocket, mssg, strlen(mssg), 0);

    }

    system("pause");
    closesocket(acceptSocket);
    closesocket(serverSocket);
    WSACleanup();
}