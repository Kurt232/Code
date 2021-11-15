#include<stdio.h>
#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
//#pragma warning(disable:4996)

int main(int argc, char* argv[]){
    //initialization WSA
    WORD sockVersion=MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0){
        return 0;
    }

    //creat socket
    SOCKET listen_socket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listen_socket==INVALID_SOCKET){
        printf("socket error !\n");
        return 0;
    }

    //bind ip and port
    sockaddr_in sin;
    sin.sin_family=AF_INET;
    sin.sin_port=htons(8888);
    sin.sin_addr.S_un.S_addr=INADDR_ANY;
    if(bind(listen_socket, (LPSOCKADDR)&sin, sizeof(sin))==SOCKET_ERROR){
        printf("bind errpr!\n");
    }

    //start listen
    if(listen(listen_socket, 5)==SOCKET_ERROR){
        printf("listen error!\n");
        return 0;
    }

    //receiving data cyclically 
    SOCKET connect_socket;
    sockaddr_in remoteAddr;
    int nAddrLen=sizeof(remoteAddr);
    char rev_data[255];
    while(true){
        printf("waiting for connection\n");
        connect_socket=accept(listen_socket, (SOCKADDR* )&remoteAddr, &nAddrLen);
        if(connect_socket==INVALID_SOCKET){
            printf("accept error!\n");
            continue;
        }
        printf("accepted a connection: %s \r\n", inet_ntoa(remoteAddr.sin_addr));
    

        //receive data

        int ret=recv(connect_socket, rev_data, 255, 0);
        if(ret>0){
            rev_data[ret]=0x00;
            printf(rev_data);
        }

        //send data
        const char* sendData="hey!, client\n";
        send(connect_socket, sendData, strlen(sendData), 0);
        closesocket(connect_socket);
    }

    closesocket(listen_socket);
    WSACleanup();
    return 0;
}