#include "StdAfx.h"

extern "C"__declspec(dllexport) void Init()
{
if(VirtualProtect(LPVOID(0x401000),3543191,PAGE_EXECUTE_READWRITE,&OldProtect))
{
		//Carregamentos das Funções Aqui Abaixo ;)
		
		Log.LoggerInit();
		fixes.LoadFixes();
		LoadQuery();
		DuelSystem.Load();
	
		//Colocar Abaixo Todos os Hooks Do GameServer
		Cfunc.HookThis((DWORD)&ProtocolCore, 0x004038BE);
		Cfunc.HookThis((DWORD)&GCDamageSend,0x00403BA7);
		
}
}
