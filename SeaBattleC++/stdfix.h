#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")

#include <windows.h>
#include <mmsystem.h>

#include "resource.h"

#pragma comment(lib, "winmm.lib")

#define ESC "\x1b"
#define CSI "\x1b["
#define ROWS 40
#define COLS 80

using namespace std;
using namespace chrono;
