#include "Game.h"

void Game::SetPos(int x, int y)
{
	sprintf_s(coord, "%s%d;%dH", CSI, y, x);
	printf(coord);
}

void Game::HotKeys(bool& pause)
{
	while (worldIsRun) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			worldIsRun = false;
		}
		else if (GetAsyncKeyState(0x50) & 0x8000) {
			pause = !pause;

			this_thread::sleep_for(milliseconds(1000));
		}
	}
}

void Game::DrawArea()
{
	// Set console code page to UTF-8 so console known how to interpret string data
	SetConsoleOutputCP(CP_UTF8);

	// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(IDR_TEXT1), L"TEXT");

	if (hResource)
	{
		HGLOBAL hLoadedResource = LoadResource(hInstance, hResource);

		if (hLoadedResource)
		{
			LPCSTR area = (LPCSTR)LockResource(hLoadedResource);

			if (area)
			{
				DWORD dwResourceSize = SizeofResource(hInstance, hResource);

				if (0 != dwResourceSize)
				{
					for (int i = 0; i < strnlen(area, 800); i++) {
						cout << area[i];
					}
				}
			}
		}
	}

	setvbuf(stdout, NULL, _IONBF, 0);
}

void Game::CreateWorld() {

	term.Terminal();  // Set virtual terminal settings
	term.SetScreenSize();
	term.SetConsoleFont();

	printf(CSI "?1049h"); // enable alt buffer
	printf(CSI "?25l"); // hide cursor blinking

	DrawArea();
}

void Game::DrawEndInfo(bool& restart)
{
	if (win) {
		SetPos(COLS + 1, 20);
		cout << "CONGRATULATION! YOU WIN!";
	}
	else {
		SetPos(COLS + 7, 20);
		cout << "GAME OVER!";
	}

	SetPos(COLS + 1, 23);
	cout << "PRESS ENTER TO RESTART";
	SetPos(COLS + 3, 24);
	cout << "PRESS ESC TO EXIT";

	bool pressed = false;
	restart = false;

	while (!pressed) {
		if (GetAsyncKeyState(VK_RETURN)) {
			restart = true;
			pressed = true;
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {
			restart = false;
			pressed = true;
		}
	}
}

void Game::DrawChanges()
{
	for (int y = 0; y < ROWS; y++)
	{
		for (int x = 0; x < COLS; x++)
		{
			if (prevBuf[y][x] == wData.vBuf[y][x]) {
				continue;
			}
			else {
				prevBuf[y][x] = wData.vBuf[y][x];

				SetPos(x, y);

				if ((prevBuf[y][x] >> 8) == Red) {
					printf(CSI "22;31m");
				}
				else if ((prevBuf[y][x] >> 8) == Green) {
					printf(CSI "22;32m");
				}
				else if ((prevBuf[y][x] >> 8) == Blue) {
					printf(CSI "22;34m");
				}
				else if ((prevBuf[y][x] >> 8) == Yellow) {
					printf(CSI "22;33m");
				}
				else if ((prevBuf[y][x] >> 8) == Purple) {
					printf(CSI "22;35m");
				}
				else if ((prevBuf[y][x] >> 8) == Cyan) {
					printf(CSI "22;36m");
				}
				else if ((prevBuf[y][x] >> 8) == BrRed) {
					printf(CSI "22;91m");
				}
				else if ((prevBuf[y][x] >> 8) == BrGreen) {
					printf(CSI "22;92m");
				}
				else if ((prevBuf[y][x] >> 8) == BrBlue) {
					printf(CSI "22;94m");
				}
				else if ((prevBuf[y][x] >> 8) == BrCyan) {
					printf(CSI "22;96m");
				}
				else if ((prevBuf[y][x] >> 8) == BrPurple) {
					printf(CSI "22;95m");
				}
				else if ((prevBuf[y][x] >> 8) == BrYellow) {
					printf(CSI "22;93m");
				}
				else if ((prevBuf[y][x] >> 8) == White) {
					printf(CSI "47;37m");
				}
				else printf(CSI "22; 44m");

				cout << char(prevBuf[y][x]);

				printf(CSI "1;0m");
			}
		}
	}
}

void Game::ConnectW()
{
	WSAData wsData;
	WORD ver = MAKEWORD(2, 2);
	
	int  wsResult = WSAStartup(ver, &wsData);
	if (wsResult != 0) {
		SetPos(30, 30);
		cout << "Failed to start wSock... ERROR: " << wsResult;
		return;
	}

	SOCKET conSocket = socket(AF_INET, SOCK_STREAM, NULL);
	if (conSocket == INVALID_SOCKET) {
		SetPos(30, 30);
		cout << "Socket can't be created... ERROR: " << WSAGetLastError();
		return;
	}

	sockaddr_in hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.sin_family = AF_INET;
	hints.sin_port = htons(DEFAULT_PORT);
	inet_pton(AF_INET, ipAdd.c_str(), &hints.sin_addr);

	int connRes = connect(conSocket, (sockaddr*)&hints, sizeof(hints));
	if (connRes == SOCKET_ERROR) {
		SetPos(30, 30);
		cout << "Unable connect to server, ERROR: " << connRes;
		closesocket(conSocket);
		WSACleanup();
		return;
	}

	player->SetPlState(false);

	PacketData cData;

	waiting = true;

	int cX = 0, cY = 0;
	bool gameRun = false, enemyRd = false;

	char bufByte[1024];

	do
	{
		if (!gameRun) {
			cData._x = player->GetX() + 15;
			cData._y = player->GetY();
			cData._setShip = player->isSet();
			cData._shipPos = player->GetShipPos();
			cData._prepare = player->IsReady();

			if (player->IsReady() && !player->GetEnemyState()) waiting = true;
			else if (player->IsReady() && player->GetEnemyState()) {
				waiting = false;
				gameRun = true;
			}
		}
		else {
			cData._x = player->GetX() - 15;
			cData._y = player->GetY();
			cData.win = win;
		}

		ZeroMemory(bufByte, sizeof(bufByte));
		memcpy(bufByte, &cData, sizeof(cData));

		if (sizeof(bufByte) > 0) {

			int sendRes = send(conSocket, (char*)bufByte, sizeof(bufByte), 0); // send to enemy

			if (sendRes != SOCKET_ERROR) {

				ZeroMemory(bufByte, sizeof(bufByte));
				int bytesRecv = recv(conSocket, (char*)bufByte, sizeof(bufByte), 0); // recieve from enemy
				waiting = false;


				if (bytesRecv > 0) {

					memcpy(&cData, bufByte, sizeof(cData));

					if (cData.win) {
						worldIsRun = false;
						win = false;
					}

					wData.vBuf[cY][cX] = u' ';
					cY = cData._y;
					cX = cData._x;
					wData.vBuf[cY][cX] = u'#' | (Purple << 8); // for seeing enemy cursor 
					
					if (!gameRun && cData._setShip) {
						player->SetEnemyCoord(cData._x, cData._y, cData._shipPos);
					}

					player->SetEnemyState(cData._prepare);
				}
			}
		}

	} while (worldIsRun);

	closesocket(conSocket);
	WSACleanup();
}
void Game::DrawToMem()
{
	for (int i = 0; i < allObjectList.size(); i++)
	{
		allObjectList[i]->DrawCursor();
	}
}

void Game::RunWorld(bool& restart)
{
	srand(time(NULL));
	CreateWorld();

	int tick = 0;
	bool pause = false;

	thread hotKeys([&]
		{ HotKeys(pause); }
	);

	

	player = new Player(&wData, 7, 7, Blue);
	playerList.push_back(player);
	allObjectList.push_back(player);
	
	thread mPlayer([&]
		{ ConnectW(); }
	);

	Sleep(1000);

	while (worldIsRun) {

		if (pause) {

			SetPos(COLS / 2 - 2, ROWS / 2);
			cout << "PAUSED";

			while (pause) {

			}

			SetPos(COLS / 2 - 2, ROWS / 2);
			cout << "      ";

		}
		
		if (!waiting) player->MoveCursor();
		else {
			SetPos(38, 30);
			cout << "Waiting for enemy...";
			Sleep(700);
			SetPos(38, 30);
			cout << "                    ";
			Sleep(550);
		}

		DrawToMem();

		DrawChanges();

		Sleep(60);

		tick++;

		if (player->GetEndSet(win)) {
			worldIsRun = false;
		}
	}

	DrawEndInfo(restart);

	hotKeys.join();
	mPlayer.join();

	printf(CSI "?1049l");
}