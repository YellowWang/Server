// tcp_server1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "winsock2.h"

#pragma comment(lib,"ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	int	servSock;
	int  clentSock;
	struct  sockaddr_in echoServAddr;
	struct	sockaddr_in echoClentAddr;
	int		serverPort;
	int		clentLen;

	serverPort = 9999;
	
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){ 

		printf("�׽��ֳ�ʼ��ʧ��!");

	}
	// test to add comments
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

	
	clentLen = sizeof(echoClentAddr);
	if ((clentSock = accept(servSock, (sockaddr*)&echoClentAddr, &clentLen)) < 0 )
	{
		return false;
	}
	
	printf("Come from client ip=%s port=%d\n", inet_ntoa(echoClentAddr.sin_addr), 
		echoClentAddr.sin_port);

	for (;;)
	{
		char recvBuff[64]={0};
		recv(clentSock, recvBuff, 64, 0);
		printf(recvBuff);
	}

	WSACleanup();
	return 0;
}

