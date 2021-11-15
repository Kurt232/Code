#include<STDIO.H>
#include<WINSOCK2.H>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
//不行
#pragma commint(lib, "ws2_32.lib")

int main(){
    //initialization
    WORD sockVersion=MAKEWORD(2,2);
    WSADATA data;
    if(WSAStartup(sockVersion, &data)!=0){
        return 0;
    }
    while(true){
        SOCKET client_socket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(client_socket==INVALID_SOCKET){
            printf("invalid socket!\n");
            return 0;
        }

        sockaddr_in server_addr;
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(8888);
        server_addr.sin_addr.S_un.S_addr=inet_addr("192.168.3.25");
        /*
        server ipconfig
        fe80::4c29:fe1f:1e7a:157c%17
        IPv4 地址 . . . . . . . . . . . . : 192.168.3.25
        子网掩码  . . . . . . . . . . . . : 255.255.255.0
        默认网关. . . . . . . . . . . . . : 192.168.3.1
        */
        if(connect(client_socket, (sockaddr *)&server_addr, sizeof(server_addr))==SOCKET_ERROR){
            printf("connect error!\n");
            closesocket(client_socket);
            return 0;
        }

        //send data to server
        string data;
        cin>>data;
        const char* send_data;
        send_data=data.c_str();

        send(client_socket, send_data, strlen(send_data), 0);

        //recive data
        char recData[255];
        int ret=recv(client_socket, recData, 255, 0);
        if(ret>0){
            recData[ret]=0x00;
            printf(recData);
        }
        closesocket(client_socket);
    }

    WSACleanup();
    return 0;
}