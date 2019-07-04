// Socket_Client_end.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include<Windows.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		printf("WSAStartup failed with error: %d\n", err);
		return 1;
	}

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return 1;
	}
	else
		printf("The Winsock 2.2 dll was found okay\n");


	/* The Winsock DLL is acceptable. Proceed to use it. */

	/* Add network programming using Winsock here */

	/* then call WSACleanup when done using the Winsock dll */
	WSACleanup();
	///////////////////////////////////////////////////////////////////////
	SOCKET sockCli;
	sockCli = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSer;
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(5050);
	addrSer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int res = connect(sockCli, (SOCKADDR*)& addrSer, sizeof(SOCKADDR));
	if (res != 0)
	{
		cout << "Client Connect Server Fail" << endl;
		return 1;
	}
	else
	{
		cout << "Client Connect Server Success!" << endl;
	}

	char sendbuf[256];
	char recvbuf[256];
	while (1)
	{
		recv(sockCli, recvbuf, 256, 0);
		cout << "Ser:>" << recvbuf << endl;

		cout << "Cli:>";
		cin >> sendbuf;
		if (strcmp(sendbuf, "quit") == 0)
		{
			break;
		}
		send(sockCli, sendbuf, strlen(sendbuf)+1,0);
	}

	closesocket(sockCli);
	WSACleanup();

}

