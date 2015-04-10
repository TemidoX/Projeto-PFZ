#include "StdAfx.h"

char Messages[1024];

Functions::Functions(){}
Functions::~Functions(){}
Functions Cfunc;

void Functions::HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset)
{
	*(DWORD*)(dwJmpOffset + 1) = dwMyFuncOffset-(dwJmpOffset+5);
}

void Functions::SetNop(DWORD dwOffset, int Size)
{
	for(int n=0; n < Size; n++)
		*(BYTE*)(dwOffset+n) = 0x90;
}

void Functions::SetRetn(DWORD dwOffset)
{
	*(BYTE*)(dwOffset) = 0xC3;
}

void Functions::SetRRetn(DWORD dwOffset)
{
	*(BYTE*)(dwOffset)=0xC3;
	*(BYTE*)(dwOffset+1)=0x90;
	*(BYTE*)(dwOffset+2)=0x90;
	*(BYTE*)(dwOffset+3)=0x90;
	*(BYTE*)(dwOffset+4)=0x90;
}

void Functions::SetByte(DWORD dwOffset, BYTE btValue)
{
	*(BYTE*)(dwOffset) = btValue;
}

char* Functions::GetMapName(int MapId)
{
	switch (MapId)
	{
	case -1:
		return "All Maps";
	case 0:
		return "Lorencia";
	case 1:
		return "Dungeon";
	case 2:
		return "Devais";
	case 3:
		return "Noria";
	case 4:
		return "Lost Tower";
	case 5:
		return "Null";
	case 6:
		return "Arena";
	case 7:
		return "Atlans";
	case 8:
		return "Tarkan";
	case 9:
		return "Devil Square";
	case 10:
		return "Icarus";
	case 30:
		return "Valley of Loren";
	case 31:
		return "Land of Trial";
	case 32:
		return "Devil Square";
	case 33:
		return "Aida";
	case 34:
		return "Crywolf";
	case 35:
		return "Null";
	case 36:
		return "Kalima";
	case 37:
		return "Kantru1";
	case 38:
		return "Kantru2";
	case 39:
		return "Kantru3";
	case 40:
		return "Silent";
	case 41:
		return "Barracks";
	case 42:
		return "Refuge";
	case 43:
		return "Null";
	case 44:
		return "Null";
	case 51:
		return "Elbeland";
	case 52:
		return "Blood Castle";
	case 53:
		return "Chaos Castle";
	case 56:
		return "Swamp of Calmness";
	case 57:
		return "Raklion";
	case 58:
		return "Raklion Boss";
	case 62:
		return "Santa Town";
	case 63:
		return "Vulcanus";
	case 64:
		return "Coliseum";
	}
	if (MapId >= 11 && MapId <= 17)
		return "Blood Castle";

	if (MapId >= 18 && MapId <= 23)
		return "Chaos Castle";

	if (MapId >= 24 && MapId <= 29)
		return "Kalima";

	if (MapId >= 45 && MapId <= 50)
		return "Illusion Temple";

	return "Unknown";
}

bool gObjIsConnected(DWORD wId)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(wId);
	if (pObj->Connected >= 1)
	{
		return true;
	}
	return false;
}

void MessageAll(int Type, int Type2, LPOBJ gObj, char *Msg, ...)
{
	Messages[0] = 0;
	char Temp[255];

	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1);

	if(Type == 2)
	{
		MsgSrv(gObj,Messages,Type2);
	}
	else
	{
		for(int i = OBJECT_MIN;i <= OBJECT_MAX;i++)
		{
			OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

			if(gObj->Connected < PLAYER_PLAYING) continue;

			GCServerMsgStringSend(Messages, i, Type);
		}
	}
}

void MsgSrv(LPOBJ gObj, char *Message, int Type)
{
	if (gObj != nullptr)
	{
		BYTE *Packet = (BYTE*)malloc(200);

		if (Packet != nullptr)
		{
			memset(Packet,0x00,200);
			*Packet = 0xC1;

			if (Type)
			{
				*(Packet + 2) = 0x02;
			}
			else
			{
				*(Packet + 2) = 0x00;
			}

			memcpy((Packet + 3), gObj->Name, strlen(gObj->Name));
			memcpy((Packet + 13), Message, strlen(Message));
			int Len = (strlen(Message) + 0x13);
			*(Packet + 1) = Len;
			DataSendAll(Packet, Len);
			free(Packet);
		}
	}
}


