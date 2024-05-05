#include <cstdlib>
#include <iostream>
#include <minwindef.h>
#include <psdk_inc/_ip_types.h>
#include <psdk_inc/_socket_types.h>
#include <psdk_inc/_wsadata.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main(){

    SOCKET clientSocket;
    int port = 8000;

    WSADATA wsadata;
    WORD version = MAKEWORD(2, 2);
    int werr = WSAStartup(version, &wsadata);
    if(werr !=0){
        std::cout<<"DLL not found\n";
        return 0;
    }else{
        std::cout<<"DLL found\n";
        std::cout<<"[Status] : "<<wsadata.szSystemStatus<<"\n";
    }   

    //socket

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientSocket == INVALID_SOCKET){
        std::cout<<"[Error] at socket() : "<<WSAGetLastError()<<"\n";
        WSACleanup();
        return 0;
    }else{
        std::cout<<"[Sucess] : socket made\n";
    }

    //conection
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET,"127.0.0.1",&clientService.sin_addr.S_un);
    clientService.sin_port = htons(port);

    if(connect(clientSocket, (SOCKADDR*)&clientService ,sizeof(clientService)) == SOCKET_ERROR){
        std::cout<<"[Error] at connect() : "<<WSAGetLastError()<<"\n";
        closesocket(clientSocket);
        WSACleanup();
        return 0;
    }else{
        std::cout<<"[Sucess] : Connect\n";
        std::cout<<"Can send files and recive Data \n";
    }

    //sending to server
    while (true) {
    
        char buffer[200] = "";
        std::cout<<"Enter message to send : ";
        std::cin.getline(buffer,200);

        int sentbytes = send(clientSocket, buffer, 200, 0);
        if(sentbytes == SOCKET_ERROR){
            std::cout<<"[Faliure] : Unsucessful send\n";
        }else {
            std::cout<<"[Sucess] : Message sent\n";
        }
    }

    
    system("pause");
    WSACleanup();

}