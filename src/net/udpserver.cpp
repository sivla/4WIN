#include "../h/net/udpserver.h"
#include "../h/sys/FourWinExceptions.h"

#include <netdb.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>

UdpServer::UdpServer(int port) : Server4Win(UDP,port)
{
    //do Nothing...
}

UdpServer::~UdpServer()
{
    //kein new...
}


void UdpServer::connect()
{
    Server4Win::connect();
    pthread_create(&serverThread, 0, startUdpServerThread, this);
    pthread_detach(serverThread);
}

void *UdpServer::startUdpServerThread(void *ptr)
{
    int sock = ((UdpServer*)ptr)->getSock();

    struct sockaddr_in sender;
    sender.sin_family = AF_INET;
    socklen_t sendsize = sizeof(sender);
    bzero(&sender, sizeof(sender));

    connection_t * connection;
    cout << "server gestartet!" << endl;
    while (true)
    {
        cout << "warte auf Broadcast..." << endl;
        connection = (connection_t *)malloc(sizeof(connection_t));

        NetworkMessage incomingMessage(LOGINREQUEST);
        connection->sock = recvfrom(sock,&incomingMessage,sizeof(NetworkMessage),MSG_WAITSTREAM,(struct sockaddr*)&sender, &sendsize);
        if (connection->sock <= 0){
             free(connection);
        }
        else{

            if(!isOwnAdress(sender)){
                cout << "Verbindungen eingegangen(UDP)..SOCK: " << connection->sock << endl;
                char* ip = inet_ntoa(sender.sin_addr);
                string ipstr(ip);
                cout << "Adresse : " << ipstr << endl;
                cout << "ID " << incomingMessage.getId() << endl;

                processThread((struct sockaddr_in)sender,ptr,incomingMessage,object);
                close(connection->sock);
                free(connection);
            }

        }
        cout << "Boradcast eigegangen!" << endl;
    }
}

void *UdpServer::processThread(struct sockaddr_in sender,void *ptr, NetworkMessage mid, string object)
{
    switch(mid.getId()){
    case UDPHELLO:
                   cout << "HELLO FROM BROADCAST" << endl;
                   int sock = ((UdpServer*)ptr)->sock;
                   NetworkMessage msg(UDPHELLO);
                   if(sendto(sock, &msg, sizeof(NetworkMessage), 0, (struct sockaddr *) &sender, sizeof(sender)) != sizeof(NetworkMessage))
                   {
                        perror("socket");
                        printf("sendto() failed");
                   }

        break;
    }
}




bool UdpServer::isOwnAdress(sockaddr_in address)
{
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);

    struct sockaddr_in SocketAddress;
    struct hostent* pHost = gethostbyname(hostname);
    if(pHost)
    {
        for(int iCnt = 0; ((pHost->h_addr_list[iCnt]) && (iCnt < 10)); ++iCnt)
        {
          memcpy(&SocketAddress.sin_addr, pHost->h_addr_list[iCnt], pHost->h_length);
          if(SocketAddress.sin_addr.s_addr == address.sin_addr.s_addr)
              return true;
        }
    }
    return false;
}
