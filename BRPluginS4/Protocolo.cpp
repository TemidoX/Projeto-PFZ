#include "StdAfx.h"

void ProtocolCore (BYTE protoNum, LPBYTE aRecv, DWORD aLen, int aIndex, DWORD Encrypt, int Serial)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	switch(BYTE(protoNum))
	{
	case 0x00:
		{
		ChatDataSend(aIndex,aRecv);
		}
		break; 

	case 0x02:
		{

		}break;
	case 0x03:
		{
			GCServerMsgStringSend("Testando -> Hugo",aIndex,0);
		}break;
	case 0xF1:
		{  
			
		}
		break;

	case 0xDB:
		{
			
		}
		break;

	}


	DataRecv(protoNum, aRecv, aLen, aIndex, Encrypt, Serial);
}