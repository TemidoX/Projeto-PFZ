#include "StdAfx.h"

sPlayersStruct PlayersStruct[OBJECT_MAX];

void PHeadSetB(LPBYTE lpBuf, BYTE head, int size)
{
	lpBuf[0] =0xC1;		// Packets
	lpBuf[1] =size;
	lpBuf[2] =head;
}


void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
{
	lpBuf[0] =0xC1;	// Packets
	lpBuf[1] =size;
	lpBuf[2] =head;
	lpBuf[3] =sub;
}

static unsigned char bBuxCode[3]={0xFC, 0xCF, 0xAB};	// Xox Key for some interesting things :)
void BuxConvert(char* buf, int size)
{
	int n;

	for (n=0;n<size;n++)
	{
		buf[n]^=bBuxCode[n%3] ;		// Nice trick from WebZen
	}
}


struct PMSG_ATTACKRESULT
{
	PBMSG_HEAD h; // C1:DC
	BYTE NumberH; // 3
	BYTE NumberL; // 4
	BYTE DamageH; // 5
	BYTE DamageL; // 6
	BYTE DamageType; // 7
	BYTE btShieldDamageH; // 8
	BYTE btShieldDamageL; // 9
	float Life; //A
	float MaxLife; //E
	float AddLife;  
};

void GCDamageSend(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage, int iShieldDamage)
{

	PMSG_ATTACKRESULT pResult;

	PHeadSetB((LPBYTE)&pResult, 0x11, sizeof(pResult));
	pResult.NumberH = SET_NUMBERH(TargetIndex);
	pResult.NumberL = SET_NUMBERL(TargetIndex);
	pResult.DamageH = SET_NUMBERH(AttackDamage);
	pResult.DamageL = SET_NUMBERL(AttackDamage);
	pResult.btShieldDamageH = SET_NUMBERH(iShieldDamage);
	pResult.btShieldDamageL = SET_NUMBERL(iShieldDamage);

	if ( MSBFlag != FALSE )
	{
		pResult.NumberH &= 0x7F;
		pResult.NumberH |= 0x80;
	}

	pResult.DamageType = MSBDamage;


	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT * gTarg = (OBJECTSTRUCT*)OBJECT_POINTER(TargetIndex);

	pResult.Life = gTarg->Life;
	pResult.MaxLife = gTarg->MaxLife + gTarg->AddLife;  

	if(gTarg->Type == OBJECT_USER )
	{
		DataSend(TargetIndex, (LPBYTE)&pResult, pResult.h.size);
	}

	if(gObj->Type == OBJECT_USER )
	{
		DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
	}
}