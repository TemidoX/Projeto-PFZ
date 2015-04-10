#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#pragma once

class Functions
{
public:
	Functions();
	~Functions();
	void HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset);
	void SetNop(DWORD dwOffset, int Size);
	void SetRetn(DWORD dwOffset);
	void SetRRetn(DWORD dwOffset);
	void SetByte(DWORD dwOffset, BYTE btValue);
	char * GetMapName(int MapId);
	
private:

};

extern Functions Cfunc;

bool gObjIsConnected(DWORD wId);
void MessageAll(int Type, int Type2, LPOBJ gObj, char *Msg, ...);
void MsgSrv(LPOBJ gObj, char *Message, int Type);




#endif