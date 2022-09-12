#include "../include/run.h"


namespace Messanger
{
    SOCKET initSocket()
    {
        WSADATA wsaData;
		ADDRINFO hints;
		ADDRINFO* addrResult = NULL;

		SOCKET ServerSocket = INVALID_SOCKET;

		int iResult;

		iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (iResult != 0) 
		{
			std::cout << "WSAStartup failed, result = " << iResult << std::endl;
		}
		
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		iResult = getaddrinfo("localhost", PORT, &hints, &addrResult);
		if (iResult != 0) 
		{
			std::cout << "getaddrinfo failed, result = " << iResult << std::endl;
			WSACleanup();
		}

		ServerSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
		if (ServerSocket == INVALID_SOCKET) 
		{
			std::cout << "Socket creation failed" << std::endl;
			freeaddrinfo(addrResult);
			WSACleanup();
		}

		iResult = connect(ServerSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			std::cout << "Unable connect to server" << std::endl;
			closesocket(ServerSocket);
			ServerSocket = INVALID_SOCKET;
			freeaddrinfo(addrResult);
			WSACleanup();
		}

        return ServerSocket;
    }

	void run()
    {
        BaseApp* _baseApp = BaseApp::instance();

        SOCKET ServerSocket = initSocket();

		CLIBaseApp cliBaseApp(ServerSocket);
		cliBaseApp.start();
	}
}