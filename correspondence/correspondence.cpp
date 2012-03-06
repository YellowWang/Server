// block example
// client

#include "stdafx.h"
#include "winsock2.h"

#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int port = 9999;

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){ 

		printf("Ì×½Ó×Ö³õÊ¼»¯Ê§°Ü!");

	}

	SOCKET sockClient;
	if ((sockClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
	{
		return false;
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port	  = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
// 	if ((serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1")) == INADDR_NONE)
// 	{
// 		return false;
// 	}
	
	if (connect(sockClient, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		return false;
	}

	
	while (1)
	{
		char buff[32]={0};
		sprintf_s(buff, "Client send pack.\n");
		int length = send(sockClient, buff, strlen(buff), 0);
		if (length < 0)
		{
			return false;
		}

		Sleep(1000);
	}


	WSACleanup();
	return 0;
}

