#pragma once
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE

// Windows Header Files:
#include <windows.h>
#include <winsock2.h>
#include <commctrl.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <Rpc.h> 

#pragma comment ( lib,  "Rpcrt4.lib" ) //
#pragma comment ( lib , "comctl32.lib" )
#pragma comment ( lib , "WS2_32.lib" )

static HMENU MyMenu;
static DWORD OldProtect;
static UINT_PTR MyMenuTimerID;
static UINT_PTR cPluginsTimer;
static HWND cWND;
static HINSTANCE hInst;

// Bibliotecas Nativas
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <process.h>
#include <algorithm>
#include <math.h>
#include <atltime.h>
#include <string>
#include <string.h>
#include <time.inl>

#include "User.h"
#include "Funcoes.h"
#include "Protocolo.h"
#include "SQL.h"
#include "Console.h"
#include "Common.h"
#include "Fixes.h"
#include "Comandos.h"
#include "DuelSystem.h"



//-> Carregar As Inis
#define BR_SQL				"..\\PFZPlugin\\BR_SQL.ini"
#define BR_Fixes			"..\\PFZPlugin\\BR_Fixes.ini"
#define BR_ServerInfo		".\\Data\\ServerInfo.dat"
#define BR_Common			"..\\PFZPlugin\\BR_Common.ini"
