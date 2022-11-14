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
			exit = true;
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

void Game::MainMenu()
{
	int mX = COLS / 2 - 3, startPosY = ROWS / 2, endPosY = startPosY + 4;
	int mY = startPosY;
	bool choose = false;
	do
	{
		SetPos(COLS / 2, startPosY);
		cout << "SINGLEPLAYER";
		SetPos(COLS / 2, startPosY + 2);
		cout << "MULTIPLAYER";
		SetPos(COLS / 2 + 4, startPosY + 4);
		cout << "EXIT";
		Sleep(250);
		while (true) {
			if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				if (mY == startPosY) {
					choose = true;
					singlePlayer = true;
				}
				else if (mY == startPosY + 2) singlePlayer = false;
				else if (mY == startPosY + 4) {
					worldIsRun = false;
					exit = true;
					return;
				}
				break;
			}
			SetPos(mX, mY);
			cout << "  ";
			if ((GetAsyncKeyState(VK_UP) & 0x8000) && mY > startPosY) mY -= 2;
			if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && mY < endPosY) mY += 2;
			SetPos(mX, mY);
			cout << "->";
			Sleep(60);
		}
		SetPos(mX, startPosY);
		cout << "                    ";
		SetPos(mX, startPosY + 2);
		cout << "                    ";
		SetPos(mX, startPosY + 4);
		cout << "                    ";
		Sleep(250);
		if (!singlePlayer) {
			SetPos(COLS / 2, startPosY);
			cout << "CREATE SERVER";
			SetPos(COLS / 2 + 1, startPosY + 2);
			cout << "JOIN SERVER";
			SetPos(COLS / 2 + 4, startPosY + 4);
			cout << "BACK";

			while (true) {
				if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
					if (mY == startPosY) {
						choose = true;
						create = true;
					}
					else if (mY == startPosY + 2) {
						joinS = true;
						choose = true;

						SetPos(mX, startPosY);
						cout << "                    ";
						SetPos(mX, startPosY + 2);
						cout << "                    ";
						SetPos(mX, startPosY + 4);
						cout << "                    ";

						Sleep(100);

						SetPos(COLS / 2 - 10, ROWS / 2);
						cout << "ENTER IP: ";
						FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
						cin >> ipAdd;
						SetPos(COLS / 2 - 10, ROWS / 2);
						cout << "          ";
					}
					break;
				}
				SetPos(mX, mY);
				cout << "  ";
				if ((GetAsyncKeyState(VK_UP) & 0x8000) && mY > startPosY) mY -= 2;
				if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && mY < endPosY) mY += 2;
				SetPos(mX, mY);
				cout << "->";
				Sleep(60);
			}
		}
		SetPos(mX, startPosY);
		cout << "                    ";
		SetPos(mX, startPosY + 2);
		cout << "                    ";
		SetPos(mX, startPosY + 4);
		cout << "                    ";
	} while (!choose);
}

void Game::CreateWorld() {

	term.Terminal();  // Set virtual terminal settings
	term.SetScreenSize();
	term.SetConsoleFont();

	printf(CSI "?1049h"); // enable alt buffer
	printf(CSI "?25l"); // hide cursor blinking

	DrawArea();
	MainMenu();
}

void Game::DrawEndInfo(bool& restart)
{
	if (win) {
		SetPos(COLS/3 - 1, 20);
		cout << "CONGRATULATION! YOU WIN!";
	}
	else {
		SetPos(COLS/2 - 4, 20);
		cout << "GAME OVER!";
	}

	SetPos(COLS/3 + 6, 23);
	cout << "PRESS ESC TO EXIT";

	bool pressed = false;
	restart = false;

	while (!pressed) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
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

void Game::ConnectHost()
{
	waiting = true;

	WSAData wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsResult = WSAStartup(ver, &wsData);
	if (wsResult != 0) {
		SetPos(COLS / 3, 30);
		cout << "Failed to start wSock... ERROR: " << wsResult;
		return;
	}

	SOCKET conSocket = socket(AF_INET, SOCK_STREAM, NULL);
	if (conSocket == INVALID_SOCKET) {
		SetPos(COLS / 3, 30);
		cout << "Socket can't be created... ERROR: " << WSAGetLastError();
		return;
	}

	sockaddr_in hints;
	ZeroMemory(&hints, sizeof(hints));

	hints.sin_family = AF_INET;
	hints.sin_port = htons(DEFAULT_PORT);
	hints.sin_addr.S_un.S_addr = INADDR_ANY;

	wsResult = bind(conSocket, (sockaddr*)&hints, sizeof(hints));
	if (wsResult == SOCKET_ERROR) {
		SetPos(COLS / 3, 30);
		cout << "bind error";
		return;
	}

	wsResult = listen(conSocket, SOMAXCONN);
	if (wsResult == SOCKET_ERROR) {
		SetPos(COLS / 3, 30);
		cout << "listen error";
		return;
	}

	SOCKET clSock = accept(conSocket, nullptr, nullptr);
	if (clSock == INVALID_SOCKET) {
		SetPos(COLS / 3, 30);
		cout << "Accept error. Error: " << WSAGetLastError();
		return;
	}

	player->SetPlState(false);

	PacketData cData;

	int cX = 0, cY = 0;
	bool gameRun = false, enemyRd = false;

	char bufByte[1024];

	SetPos(COLS / 3, 30);
	cout << "Connection Successful";

	player->SetState(true);

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
			cData._shot = player->isShot();
		}

		ZeroMemory(bufByte, sizeof(bufByte));
		memcpy(bufByte, &cData, sizeof(cData));

		if (sizeof(bufByte) > 0) {

			int sendRes = send(clSock, (char*)bufByte, sizeof(bufByte), 0); // send to enemy

			if (sendRes != SOCKET_ERROR) {

				ZeroMemory(bufByte, sizeof(bufByte));
				int bytesRecv = recv(clSock, (char*)bufByte, sizeof(bufByte), 0); // recieve from enemy
				waiting = false;

				if (bytesRecv > 0) {
					memcpy(&cData, bufByte, sizeof(cData));

					if (gameRun) {
						wData.vBuf[cY][cX] = u' ';
						cY = cData._y;
						cX = cData._x;
						wData.vBuf[cY][cX] = u'#' | (Purple << 8); // for seeing enemy cursor 

						if (cData._shot) player->SetEnemyShot(cData._x, cData._y);

						if (cData.win) {
							worldIsRun = false;
							win = false;
						}
					}
					else {
						player->SetEnemyState(cData._prepare);

						if (cData._setShip) player->SetEnemyCoord(cData._x, cData._y, cData._shipPos);
					}
				}
			}
		}

	} while (worldIsRun);

	closesocket(conSocket);
	WSACleanup();
}

void Game::ConnectPlayer()
{
	waiting = true;

	WSAData wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsResult = WSAStartup(ver, &wsData);
	if (wsResult != 0) {
		SetPos(COLS / 3, 30);
		cout << "Failed to start wSock... ERROR: " << wsResult;
		return;
	}

	SOCKET conSocket = socket(AF_INET, SOCK_STREAM, NULL);
	if (conSocket == INVALID_SOCKET) {
		SetPos(COLS / 3, 30);
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
		SetPos(COLS / 3, 30);
		cout << "Unable connect to server, ERROR: " << connRes;
		closesocket(conSocket);
		WSACleanup();
		return;
	}

	player->SetPlState(false);

	PacketData cData;

	int cX = 0, cY = 0;
	bool gameRun = false, enemyRd = false;

	char bufByte[1024];

	SetPos(COLS / 3, 30);
	cout << "Connection Successful";

	player->SetState(false);

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
			cData._shot = player->isShot();
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

					if (gameRun) {
						wData.vBuf[cY][cX] = u' ';
						cY = cData._y;
						cX = cData._x;
						wData.vBuf[cY][cX] = u'#' | (Purple << 8); // for seeing enemy cursor 

						if (cData._shot) player->SetEnemyShot(cData._x, cData._y);

						if (cData.win) {
							worldIsRun = false;
							win = false;
						}
					}
					else {
						player->SetEnemyState(cData._prepare);

						if (cData._setShip) player->SetEnemyCoord(cData._x, cData._y, cData._shipPos);
					}
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

	if (!singlePlayer && create) {
		thread mPlayer([&]
			{ ConnectHost(); }
		);
		mPlayer.detach();
	}
	else if (!singlePlayer && joinS) {
		thread mPlayer([&]
			{ ConnectPlayer(); }
		);
		mPlayer.detach();
	}

	Sleep(1000);

	while (worldIsRun) {
		
		if (!waiting) player->MoveCursor();
		else {
			SetPos(35, 30);
			cout << "Waiting for enemy...";
			Sleep(700);
			SetPos(35, 30);
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

	if (!exit) {
		DrawEndInfo(restart);
		Sleep(1000);
	}

	hotKeys.join();

	printf(CSI "?1049l");
}