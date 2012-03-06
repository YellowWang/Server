// tcp_server1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "winsock2.h"

#pragma comment(lib,"ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	int	servSock;
	int  conSock;
	struct  sockaddr_in echoServAddr;
	struct	sockaddr_in echoClentAddr;
	int		serverPort;
	int		clentLen;

	serverPort = 9999;

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){ 

		printf("Ì×½Ó×Ö³õÊ¼»¯Ê§°Ü!");

	}

	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		int err = WSAGetLastError();
		return false;
	}

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	echoServAddr.sin_port		 = htons(serverPort);

	if (bind(servSock, (sockaddr*)&echoServAddr, sizeof(echoServAddr)) < 0)
	{
		return false;
	}

	if (listen(servSock, 5) < 0)
	{
		return false;
	}

	int	clientSock[5];
	for (int i = 0; i < 5; i++)
	{
		clientSock[i] = -1;
	}

	fd_set allset, rset;
	FD_ZERO(&allset);
	FD_SET(servSock, &allset);
	int	maxfd = servSock;
	while (1)
	{
		rset = allset;
		int ready = select(maxfd+1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(servSock, &rset))
		{
			clentLen = sizeof(echoClentAddr);
			if ((conSock = accept(servSock, (sockaddr*)&echoClentAddr, &clentLen)) < 0 )
			{
				return false;
			}

			int i = 0;
			for (i = 0; i < 5; i++)
			{
				if (clientSock[i] < 0)
				{
					clientSock[i] = conSock;
					break;
				}
			}
			if (i >= 5)
			{
				printf("No more a valid socket!\n");
				continue;
			}
			
			printf("Client %d is coming.\n", i);

			FD_SET(conSock, &allset);
			maxfd = max(conSock, maxfd);

			if (--ready <= 0)
				continue;
		}

		for (int i = 0; i < 5; i++)
		{
			if (clientSock[i] <= 0)
			{
				continue;
			}
			if (FD_ISSET(clientSock[i], &rset))
			{
				char recvBuff[64]={0};
				if (recv(clientSock[i], recvBuff, 64, 0) < 0)
				{
					FD_CLR(clientSock[i], &allset);
					clientSock[i] = -1;
					printf("Client %d closed.\n", i);
				}
				else
					printf("Client %d say: %s\n", i, recvBuff);
				
			}

			if (--ready <= 0)
				continue;
		}
	}

	WSACleanup();
	return 0;
}

