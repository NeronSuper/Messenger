#include "../include/run.h"


namespace Messanger
{
    SOCKET initSocket()
    {
        WSADATA wsaData;
		ADDRINFO hints;
		ADDRINFO* addrResult = NULL;

		SOCKET ListenSocket = INVALID_SOCKET;
		SOCKET ClientSocket = INVALID_SOCKET;

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

		ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
		if (ListenSocket == INVALID_SOCKET) 
		{
			std::cout << "Socket creation failed" << std::endl;
			freeaddrinfo(addrResult);
			WSACleanup();
		}

		iResult = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			std::cout << "Binding socket failed" << std::endl;
			closesocket(ListenSocket);
			ListenSocket = INVALID_SOCKET;
			freeaddrinfo(addrResult);
			WSACleanup();
		}

        return ListenSocket;
    }

    void clientHendler(SOCKET ClientSocket)
    {
		CLIBaseApp cliBaseApp(ClientSocket);

		cliBaseApp.start();
    }

	void run()
    {
        BaseApp* _baseApp = BaseApp::instance();

        SOCKET ListenSocket = initSocket();
        SOCKET ClientSocket = INVALID_SOCKET;

        int iResult;

        do
        {
            iResult = listen(ListenSocket, SOMAXCONN);
			if (iResult == SOCKET_ERROR)
			{
				std::cout << "Listening socket failed" << std::endl;
				closesocket(ListenSocket);
				WSACleanup();
			}

			ClientSocket = accept(ListenSocket, NULL, NULL);
			if (ClientSocket == INVALID_SOCKET)
			{
				std::cout << "Accepting socket failed" << std::endl;
				closesocket(ListenSocket);
				WSACleanup();
			}
			std::cout << "New Client is connected\n";

			_baseApp->addSocket(ClientSocket);

			std::thread th(clientHendler, ClientSocket);
            th.detach();
        }
        while (true);
    }
}