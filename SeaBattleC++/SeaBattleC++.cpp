#include "Game.h"

#pragma warning(disable: 4996)

int main()
{
	WSAData wsaData;
	WORD DLLversion = MAKEWORD(2, 1);
	WSAStartup(DLLversion, &wsaData);
	if (WSAStartup(DLLversion, &wsaData) != 0) {
		cout << "ERROR" << endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int addrSize = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, addrSize) != 0) {
		cout << "Error: failed connect to server";
		return 1;
	}
	cout << "Connected Successfully";

	bool restart = false;

	do
	{
		Game gm;
		gm.RunWorld(restart);
	} while (restart);

	return 0;
}