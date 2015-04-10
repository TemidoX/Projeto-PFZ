#include "StdAfx.h"

cFixes::cFixes(){}
cFixes::~cFixes(){}
cFixes fixes;

void __declspec(naked) FixNewPetDurabDown()
{
	_asm
	{
		//Angel
		MOV EDX,DWORD PTR SS:[EBP-0xC]
		MOVSX EAX,WORD PTR DS:[EDX+0x6]
		CMP EAX,0x1A00
			JE CallDurDown

			//Panda
			MOV EDX,DWORD PTR SS:[EBP-0xC]
		MOVSX EAX,WORD PTR DS:[EDX+0x6]
		CMP EAX,0x1A50
			JE CallDurDown 

			//1 Offset
			mov edi, 0x005116E0;
		jmp edi;
CallDurDown:
		//2 Offset
		mov edi, 0x005116EF;
		jmp edi;
	}
} 


void cFixes::LoadFixes()
{
	for (int i = 0; i < 20;i++) //RESETA VARS :D
		this->varsFixes[i] = 0;
	
	this->varsFixes[1] = GetPrivateProfileInt("Fixes","UseCheckSum",0,BR_Fixes);
	this->varsFixes[2] = GetPrivateProfileInt("Fixes","PersonalIDBypasser",0,BR_Fixes);
	this->varsFixes[3] = GetPrivateProfileInt("Fixes","GuildIDBypasser",0,BR_Fixes);
	this->varsFixes[4] = GetPrivateProfileInt("Fixes","DisableLogs",0,BR_Fixes);
	this->varsFixes[5] = GetPrivateProfileInt("Fixes","ChaosCastleAllowingPlayers",2,BR_Fixes);
	this->varsFixes[6] = GetPrivateProfileInt("Fixes","BloodCastleAllowingPlayers",2,BR_Fixes);
	this->varsFixes[7] = GetPrivateProfileInt("Fixes","DevilSquareAllowingPlayers",2,BR_Fixes);
	this->varsFixes[8] = GetPrivateProfileInt("Fixes","BloodCastleMasterEnterType",1,BR_Fixes);
	this->varsFixes[9] = GetPrivateProfileInt("Fixes","EldaradoEventType",		   1,BR_Fixes);
	this->varsFixes[10] = GetPrivateProfileInt("Fixes","AllowExeAnc",		   1,BR_Fixes);
	this->varsFixes[11] = GetPrivateProfileInt("Fixes","AllowJohAnc",		   1,BR_Fixes);
	this->varsFixes[12] = GetPrivateProfileInt("Fixes","AllowExeSock",		   1,BR_Fixes);
	this->varsFixes[13] = GetPrivateProfileInt("Fixes","380OptDisable",		   1,BR_Fixes);
	this->varsFixes[14] = GetPrivateProfileInt("Fixes","HarmonyOptDisable",		   1,BR_Fixes);
	this->varsFixes[15] = GetPrivateProfileInt("Fixes","CSSkillsOnNOrmal",		   1,BR_Fixes);
	this->varsFixes[16] = GetPrivateProfileInt("Fixes","MaxLifeOpt",		   1,BR_Fixes);
	this->varsFixes[17] = GetPrivateProfileInt("Fixes","Enable65kStats",		   1,BR_Fixes);
	this->varsFixes[18] = GetPrivateProfileInt("Fixes","DisableDump",		   1,BR_Fixes);
	this->FixesSeason4();
}


void cFixes::FixesSeason4()
{
	
	BYTE IOCPResponceErrorJump[] = {0xE9, 0xC3, 0x02, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90};
	memcpy((int*)0x004B1D9E, IOCPResponceErrorJump, sizeof(IOCPResponceErrorJump));

	BYTE IOCPAdd79Error[] = {0x81, 0x7D, 0xD0, 0xE3, 0x03, 0x00, 0x00, 0x0F, 0x84, 0x66, 0xFD, 0xFF,
                0xFF, 0x83, 0x7D, 0xD0, 0x79, 0x0F, 0x84, 0x5C, 0xFD, 0xFF, 0xFF, 0xE9,
                0x25, 0xFD, 0xFF, 0xFF};
	memcpy((int*)0x004B2066, IOCPAdd79Error, sizeof(IOCPAdd79Error));
	
	//*********************************************************************************************************************************

	//Hook JGPGetCharInfoEx (GS,GSCS)
	BYTE CharWingsEx[] =  {	0x8D, 0xBD, 0xEC, 0xFE, 0xFF, 0xFF, 0x57, 0xFF, 
							0x75, 0x08, 0xFF, 0xB5, 0x94, 0xFE, 0xFF, 0xFF, 
							0xFF, 0x15, 0x00, 0xB2, 0x71, 0x00, 0xE9, 0x37, 
							0xE2, 0xFF, 0xFF, 0x8A, 0x8D, 0xE8, 0xFE, 0xFF, 
							0xFF, 0x88, 0x8D, 0xD5, 0xFE, 0xFF, 0xFF, 0x6A, 
							0x07, 0x8D, 0x95, 0xD4, 0xFE, 0xFF, 0xFF, 0x52, 
							0x8D, 0x85, 0xEC, 0xFE, 0xFF, 0xFF, 0x50, 0xE8, 
							0x3C, 0xA1, 0x1E, 0x00, 0x83, 0xC4, 0x0C, 0x8B, 
							0x8D, 0xE8, 0xFE, 0xFF, 0xFF, 0x51, 0x8D, 0x95, 
							0xEC, 0xFE, 0xFF, 0xFF, 0x52, 0x8B, 0x85, 0xE0, 
							0xFE, 0xFF, 0xFF, 0x50, 0xE8, 0xDE, 0x86, 0xFD, 
							0xFF, 0x83, 0xC4, 0x0C, 0x5F, 0x5E, 0x5B, 0x8B, 
							0xE5, 0x5D, 0xC3 };
	memcpy((int*)0x0042CE88,CharWingsEx,sizeof(CharWingsEx));

	//JGPGetCharInfoEx
	Cfunc.SetByte(0x0042B03A+1,0xA5);
	Cfunc.SetByte(0x0042B0C8+2,0xD5);
	Cfunc.SetByte(0x0042B0FA+2,0xA3);


	// PetDurablity
	BYTE FixPetDur[] = { 0xFF, 0x25, 0x50, 0xB5, 0x71, 0x00, 0x90, 0x90 };
	memcpy((int*)0x005116D2,FixPetDur,sizeof(FixPetDur));
	*(unsigned int*)0x0071B550 = (unsigned int)FixNewPetDurabDown;


	BYTE ViewPortPatch[] = { 0xFF, 0x75, 0xF8, 0xFF, 0x15, 0x50, 
							 0xB0, 0x71, 0x00, 0x5F, 0x5E, 0x5B, 
							 0x8B, 0xE5, 0x5D, 0xC3 };
	memcpy((int*)0x00527237,ViewPortPatch,sizeof(ViewPortPatch));


	// CheckSum
	if (this->varsFixes[1] == 1)
		Cfunc.SetByte(0x00438D3A, 0x74);// CheckSum On
	else
		Cfunc.SetByte(0x00438D3A, 0xEB);// CheckSum Off

	// Personal ID
	if (this->varsFixes[2] == 1)
		Cfunc.SetNop(0x0043B9D6, 5);// Personal ID Fix

	// Guild ID
	if (this->varsFixes[3] == 1)
	{
		Cfunc.SetNop(0x004504E9, 2);// Guild ID Fix
		Cfunc.SetNop(0x00450376, 6);// Guild ID Fix
	}

	// Disable Logs
	if (this->varsFixes[4] == 1)
	{
		Cfunc.SetNop(0x0050D1C6,6);
		Cfunc.SetNop(0x00582C56,6);
		Cfunc.SetNop(0x005938D6,6);
		Cfunc.SetNop(0x005C27D8,6);
		Cfunc.SetNop(0x005E6F60,6);
		Cfunc.SetNop(0x004B8685,6);
	}

	// Chaos Castle Phonoman PK Level Entrance (All)
	if (this->varsFixes[5])
	{
		Cfunc.SetByte(0x00460B1C+2,0x07);       
		Cfunc.SetByte(0x0046303A+2,0x07);
		Cfunc.SetByte(0x004632A3+2,0x07);
		Cfunc.SetByte(0x0046327B+2,0x07);
		Cfunc.SetByte(0x005D945C,0x07); // Enter
		Cfunc.SetByte(0x005DAA33,0x07); // NPC
	}

	// Chaos Castle Phonoman Just PK Level Entrance
	if (this->varsFixes[5] == 2)
	{
		Cfunc.SetByte(0x00460B1C+2,0x06);       
		Cfunc.SetByte(0x0046303A+2,0x06);
		Cfunc.SetByte(0x004632A3+2,0x06);
		Cfunc.SetByte(0x0046327B+2,0x06);
		Cfunc.SetByte(0x005D945C,0x06); // Enter
		Cfunc.SetByte(0x005DAA33,0x06); // NPC
	}

	// Blood Castle Phonoman PK Level Entrance (All)
	if (this->varsFixes[6])
	{
		Cfunc.SetByte(0x0046227E, 0x07); // Enter
		Cfunc.SetByte(0x00460A20, 0x07); // Time
		Cfunc.SetByte(0x005A5714, 0x07); // NPC
	}

	// Blood Castle Phonoman Just PK Level Entrance
	if (this->varsFixes[6] == 2)
	{
		Cfunc.SetByte(0x0046227E, 0x06); // Enter
		Cfunc.SetByte(0x00460A20, 0x06); // Time
		Cfunc.SetByte(0x005A5714, 0x06); // NPC
	}

	// Devil Square Phonoman PK Level Entrance (All)
	if (this->varsFixes[7])
	{
		Cfunc.SetByte(0x0045FF36, 0x07); // Enter
		Cfunc.SetByte(0x00460957, 0x07); // Time
		Cfunc.SetByte(0x005A444E, 0x07); // NPC
	}

	// Devil Square Phonoman Just PK Level Entrance
	if (this->varsFixes[7] == 2)
	{
		Cfunc.SetByte(0x0045FF36, 0x06); // Enter
		Cfunc.SetByte(0x00460957, 0x06); // Time
		Cfunc.SetByte(0x005A444E, 0x06); // NPC
	}

	 // Allow Excellent Ancient
	if (this->varsFixes[10] == 1)
		Cfunc.SetByte(0x0054EFC6,0xEB);

	// Allow Jewel of Harmony Ancient
	if (this->varsFixes[11] == 1)
		Cfunc.SetByte(0x005C600A,0xEB);

	// Allow Exelent Socket   
	if (this->varsFixes[12] == 1)
		Cfunc.SetByte(0x0054F06F,0xEB);

	if (this->varsFixes[13] == 1)
	{
		Cfunc.SetNop(0x004EB921,5);
	}	
	if(this->varsFixes[14] == 1)
	{
		Cfunc.SetNop(0x004EB92D,5);
	}
	//Fix Golden Invasion Message
	BYTE FixGoldenInvMsg[] = { 0xEB, 0x51, 0x90 };
	memcpy((int*)0x0048018A,FixGoldenInvMsg,sizeof(FixGoldenInvMsg));

	BYTE FixGoldenInvMsg1[] = { 0x00, 0x00, 0x83, 0xC4, 0x08, 0x50, 0xE8, 0xED, 0x3F, 0xF8, 0xFF, 0xEB, 0xA5, 0x00, 0x00 };
	memcpy((int*)0x004801DB,FixGoldenInvMsg1,sizeof(FixGoldenInvMsg1));

	// Old KOR Style Eldarado Event
	if (this->varsFixes[9] == 1)
	{
		//Fix tantalos from drop +3, back to +5
		BYTE FixGoldenTantalosDrop[7]={0xC7, 0x45, 0xEC, 0x0C, 0x00, 0x00, 0x00};
		memcpy((int*)0x0041EB27,FixGoldenTantalosDrop,sizeof(FixGoldenTantalosDrop));

		//Fix Titan, +2BOK
		BYTE FixGoldenTitanDrop[7]={0xC7, 0x45, 0xEC, 0x09, 0x00, 0x00, 0x00};
		memcpy((int*)0x0041E962,FixGoldenTitanDrop,sizeof(FixGoldenTitanDrop));

		//Fix randomizer on +3BOK
		BYTE FixGoldenDerconDrop[7]={0xBA, 0x0A, 0x00, 0x00, 0x00, 0x90, 0x90};
		memcpy((int*)0x0041EDF5,FixGoldenDerconDrop,sizeof(FixGoldenDerconDrop));

		//Fix looping from 5 rep. to 1
		BYTE FixGoldenDerconDropLOOP[7]={0x83, 0xBD, 0xF8, 0xFE, 0xFF, 0xFF, 0x01};
		memcpy((int*)0x0041ED91,FixGoldenDerconDropLOOP,sizeof(FixGoldenDerconDropLOOP));

		//Fix Lizard King
		BYTE FixGoldenLizardDrop[7]={0xC7, 0x45, 0xEC, 0x0B, 0x00, 0x00, 0x00};
		memcpy((int*)0x0041EA44,FixGoldenLizardDrop,sizeof(FixGoldenLizardDrop));

		//Fix Golden Budge Dragon
		BYTE FixGoldenBudgeDragonDrop[7]={0xC7, 0x45, 0xEC, 0x00, 0x00, 0x00, 0x00}; 
		memcpy((int*)0x0041E8A6,FixGoldenBudgeDragonDrop,sizeof(FixGoldenBudgeDragonDrop)); 

		//Fix Golden Soldier
		BYTE GoldenSoldierFix[6]={0xE9, 0x97, 0x00, 0x00, 0x00, 0x90}; 
		memcpy((int*)0x0041E93B,GoldenSoldierFix,sizeof(GoldenSoldierFix)); 

		Cfunc.SetNop(0x0041EAC7,2); //Golden Wheel FIX
		Cfunc.SetNop(0x0041E9F7,2); //Golden Vepar FIX 
		Cfunc.SetNop(0x0041EADA,2); //Golden Golem FIX
	}

	if (this->varsFixes[15] == 1)
	{
		Cfunc.SetByte(0x004E0D09,0xEB);
		Cfunc.SetByte(0x004E0D19,0xEB);
		Cfunc.SetByte(0x004E0C09,0xEB);
		Cfunc.SetByte(0x004E0C19,0xEB);
		Cfunc.SetByte(0x004E0E26,0xEB);
		Cfunc.SetByte(0x004E0E36,0xEB);
		Cfunc.SetByte(0x004E0F29,0xEB);
		Cfunc.SetByte(0x004E0F19,0xEB);
		Cfunc.SetByte(0x004E1039,0xEB);
		Cfunc.SetByte(0x004E1049,0xEB);
		Cfunc.SetByte(0x004E1136,0xEB);
		Cfunc.SetByte(0x004E1146,0xEB);
	}

	if (this->varsFixes[16] == 1)
	{
		//Options +28
		BYTE Opt28[2] = { 0x90,0x90};
		memcpy((int*)0x0042F2F4,Opt28,sizeof(Opt28));

		BYTE Opt282[2] = { 0x90,0x90};
		memcpy((int*)0x005573C4,Opt282,sizeof(Opt282));
	
		BYTE Opt281[2] = { 0x90,0x90};
		memcpy((int*)0x00501F4C,Opt281,sizeof(Opt281));

		BYTE Opt283[1] = { 0x07};
		memcpy((int*)0x005378D0,Opt283,sizeof(Opt283));

		BYTE Opt284[1] = { 0x07};
		memcpy((int*)0x00501F89,Opt284,sizeof(Opt284));
	}

	// Maximum Stats (65535)
	if (this->varsFixes[17] == 1)
	{
		Cfunc.SetByte(0x004567F3+1,0xB7);
		Cfunc.SetByte(0x004592A2+1,0xB7);
		Cfunc.SetByte(0x0045CBB1+1,0xB7);
		Cfunc.SetByte(0x004AD9A7+1,0xB7);
		Cfunc.SetByte(0x004CF77C+1,0xB7);
		Cfunc.SetByte(0x004CFD34+1,0xB7);
		Cfunc.SetByte(0x004CFD9C+1,0xB7);
		Cfunc.SetByte(0x004CFE05+1,0xB7);
		Cfunc.SetByte(0x004CFE5A+1,0xB7);
		Cfunc.SetByte(0x004D27D6+1,0xB7);
		Cfunc.SetByte(0x004D43E4+1,0xB7);
		Cfunc.SetByte(0x004D4485+1,0xB7);
		Cfunc.SetByte(0x004D44FF+1,0xB7);
		Cfunc.SetByte(0x004D4FCB+1,0xB7);
		Cfunc.SetByte(0x004D62FF+1,0xB7);
		Cfunc.SetByte(0x004D633A+1,0xB7);
		Cfunc.SetByte(0x004D7536+1,0xB7);
		Cfunc.SetByte(0x004D75C9+1,0xB7);
		Cfunc.SetByte(0x004E8F32+1,0xB7);
		Cfunc.SetByte(0x004E8FC4+1,0xB7);
		Cfunc.SetByte(0x004EE5D2+1,0xB7);
		Cfunc.SetByte(0x004EEF9C+1,0xB7);
		Cfunc.SetByte(0x004EF1C3+1,0xB7);
		Cfunc.SetByte(0x004F0A8E+1,0xB7);
		Cfunc.SetByte(0x004F9680+1,0xB7);
		Cfunc.SetByte(0x00502B48+1,0xB7);
		Cfunc.SetByte(0x00506051+1,0xB7);
		Cfunc.SetByte(0x0051CB84+1,0xB7);
		Cfunc.SetByte(0x0053AEFB+1,0xB7);
		Cfunc.SetByte(0x0053B1E0+1,0xB7);
		Cfunc.SetByte(0x0053B440+1,0xB7);
		Cfunc.SetByte(0x0053CB58+1,0xB7);
		Cfunc.SetByte(0x0053D760+1,0xB7);
		Cfunc.SetByte(0x0053D90B+1,0xB7);
		Cfunc.SetByte(0x00547BA7+1,0xB7);
		Cfunc.SetByte(0x005650B7+1,0xB7);
		Cfunc.SetByte(0x0058E7C9+1,0xB7);
		Cfunc.SetByte(0x0058EA18+1,0xB7);
		Cfunc.SetByte(0x0058ECB7+1,0xB7);
		Cfunc.SetByte(0x005D473C+1,0xB7);

		Cfunc.SetByte(0x0045680D+1,0xB7);
		Cfunc.SetByte(0x0045CC3A+1,0xB7);
		Cfunc.SetByte(0x004CF795+1,0xB7);
		Cfunc.SetByte(0x004CFABA+1,0xB7);
		Cfunc.SetByte(0x004CFD48+1,0xB7);
		Cfunc.SetByte(0x004CFDB0+1,0xB7);
		Cfunc.SetByte(0x004CFE19+1,0xB7);
		Cfunc.SetByte(0x004CFE6E+1,0xB7);
		Cfunc.SetByte(0x004D6315+1,0xB7);
		Cfunc.SetByte(0x004D6350+1,0xB7);
		Cfunc.SetByte(0x004D7516+1,0xB7);
		Cfunc.SetByte(0x004D75A9+1,0xB7);
		Cfunc.SetByte(0x004D79AC+1,0xB7);
		Cfunc.SetByte(0x004D79E8+1,0xB7);
		Cfunc.SetByte(0x004D7A1A+1,0xB7);
		Cfunc.SetByte(0x004D7A56+1,0xB7);
		Cfunc.SetByte(0x004D7A8E+1,0xB7);
		Cfunc.SetByte(0x004D7ABD+1,0xB7);
		Cfunc.SetByte(0x004D7B07+1,0xB7);
		Cfunc.SetByte(0x004D7B3B+1,0xB7);
		Cfunc.SetByte(0x004D7B6F+1,0xB7);
		Cfunc.SetByte(0x004D7BA6+1,0xB7);
		Cfunc.SetByte(0x004D7BDA+1,0xB7);
		Cfunc.SetByte(0x004D7C0F+1,0xB7);
		Cfunc.SetByte(0x004DB029+1,0xB7);
		Cfunc.SetByte(0x004E4AF6+1,0xB7);
		Cfunc.SetByte(0x004E8F4B+1,0xB7);
		Cfunc.SetByte(0x004E8FAE+1,0xB7);
		Cfunc.SetByte(0x004EE59C+1,0xB7);
		Cfunc.SetByte(0x004EE63E+1,0xB7);
		Cfunc.SetByte(0x004EEFE1+1,0xB7);
		Cfunc.SetByte(0x004EF1D9+1,0xB7);
		Cfunc.SetByte(0x004F0AA7+1,0xB7);
		Cfunc.SetByte(0x004F279C+1,0xB7);
		Cfunc.SetByte(0x004F27D8+1,0xB7);
		Cfunc.SetByte(0x004F280A+1,0xB7);
		Cfunc.SetByte(0x004F2846+1,0xB7);
		Cfunc.SetByte(0x004F287E+1,0xB7);
		Cfunc.SetByte(0x004F28AD+1,0xB7);
		Cfunc.SetByte(0x004F28F7+1,0xB7);
		Cfunc.SetByte(0x004F292B+1,0xB7);
		Cfunc.SetByte(0x004F295F+1,0xB7);
		Cfunc.SetByte(0x004F2996+1,0xB7);
		Cfunc.SetByte(0x004F29CA+1,0xB7);
		Cfunc.SetByte(0x004F29FF+1,0xB7);
		Cfunc.SetByte(0x004F96A5+1,0xB7);
		Cfunc.SetByte(0x004FAA86+1,0xB7);
		Cfunc.SetByte(0x00502B7B+1,0xB7);
		Cfunc.SetByte(0x00506046+1,0xB7);
		Cfunc.SetByte(0x00502B7B+1,0xB7);
		Cfunc.SetByte(0x00506046+1,0xB7);
		Cfunc.SetByte(0x0051CBBC+1,0xB7);
		Cfunc.SetByte(0x0053AF05+1,0xB7);
		Cfunc.SetByte(0x0053B1EA+1,0xB7);
		Cfunc.SetByte(0x0053B44A+1,0xB7);
		Cfunc.SetByte(0x0053CB0F+1,0xB7);
		Cfunc.SetByte(0x0053D78C+1,0xB7);
		Cfunc.SetByte(0x0053D8CD+1,0xB7);
		Cfunc.SetByte(0x00547BEF+1,0xB7);
		Cfunc.SetByte(0x005650A0+1,0xB7);
		Cfunc.SetByte(0x0058E7AE+1,0xB7);
		Cfunc.SetByte(0x0058E9FD+1,0xB7);
		Cfunc.SetByte(0x0058EC9C+1,0xB7);
		Cfunc.SetByte(0x005D4724+1,0xB7);

		Cfunc.SetByte(0x004CF7AE+1,0xB7);
		Cfunc.SetByte(0x004CFD5C+1,0xB7);
		Cfunc.SetByte(0x004CFDC4+1,0xB7);
		Cfunc.SetByte(0x004CFE2D+1,0xB7);
		Cfunc.SetByte(0x004CFE82+1,0xB7);
		Cfunc.SetByte(0x004DAD53+1,0xB7);
		Cfunc.SetByte(0x004E8F64+1,0xB7);
		Cfunc.SetByte(0x004E9031+1,0xB7);
		Cfunc.SetByte(0x004EE674+1,0xB7);
		Cfunc.SetByte(0x004EF0D9+1,0xB7);
		Cfunc.SetByte(0x004EF1F1+1,0xB7);
		Cfunc.SetByte(0x004F0AC0+1,0xB7);
		Cfunc.SetByte(0x004F8142+1,0xB7);
		Cfunc.SetByte(0x004FB3F1+1,0xB7);
		Cfunc.SetByte(0x00502BAD+1,0xB7);
		Cfunc.SetByte(0x00504249+1,0xB7);
		Cfunc.SetByte(0x0050603B+1,0xB7);
		Cfunc.SetByte(0x0051CC2B+1,0xB7);
		Cfunc.SetByte(0x0053AF11+1,0xB7);
		Cfunc.SetByte(0x0053B1F6+1,0xB7);
		Cfunc.SetByte(0x0053B456+1,0xB7);
		Cfunc.SetByte(0x0053CAC6+1,0xB7);
		Cfunc.SetByte(0x0053D7B5+1,0xB7);
		Cfunc.SetByte(0x0053D88C+1,0xB7);
		Cfunc.SetByte(0x0053E628+1,0xB7);
		Cfunc.SetByte(0x0053E644+1,0xB7);
		Cfunc.SetByte(0x0053E660+1,0xB7);
		Cfunc.SetByte(0x0053E67C+1,0xB7);
		Cfunc.SetByte(0x00547C37+1,0xB7);
		Cfunc.SetByte(0x00565089+1,0xB7);
		Cfunc.SetByte(0x0058E793+1,0xB7);
		Cfunc.SetByte(0x0058E9E2+1,0xB7);
		Cfunc.SetByte(0x0058EC81+1,0xB7);
		Cfunc.SetByte(0x005D470C+1,0xB7);

		Cfunc.SetByte(0x004567D9+1,0xB7);
		Cfunc.SetByte(0x004CF7C7+1,0xB7);
		Cfunc.SetByte(0x004CFD70+1,0xB7);
		Cfunc.SetByte(0x004CFDD8+1,0xB7);
		Cfunc.SetByte(0x004CFE41+1,0xB7);
		Cfunc.SetByte(0x004CFE96+1,0xB7);
		Cfunc.SetByte(0x004D0BE5+1,0xB7);
		Cfunc.SetByte(0x004D0CD0+1,0xB7);
		Cfunc.SetByte(0x004D0D37+1,0xB7);
		Cfunc.SetByte(0x004D0ED1+1,0xB7);
		Cfunc.SetByte(0x004D0F10+1,0xB7);
		Cfunc.SetByte(0x004D0F8F+1,0xB7);
		Cfunc.SetByte(0x004D0FD0+1,0xB7);
		Cfunc.SetByte(0x004D10BD+1,0xB7);
		Cfunc.SetByte(0x004D10FC+1,0xB7);
		Cfunc.SetByte(0x004D1170+1,0xB7);
		Cfunc.SetByte(0x004D118C+1,0xB7);
		Cfunc.SetByte(0x004D11A7+1,0xB7);
		Cfunc.SetByte(0x004D11F5+1,0xB7);
		Cfunc.SetByte(0x004D1210+1,0xB7);
		Cfunc.SetByte(0x004D122B+1,0xB7);
		Cfunc.SetByte(0x004D133B+1,0xB7);
		Cfunc.SetByte(0x004D137A+1,0xB7);
		Cfunc.SetByte(0x004D13EE+1,0xB7);
		Cfunc.SetByte(0x004D140A+1,0xB7);
		Cfunc.SetByte(0x004D1425+1,0xB7);
		Cfunc.SetByte(0x004D1473+1,0xB7);
		Cfunc.SetByte(0x004D148E+1,0xB7);
		Cfunc.SetByte(0x004D14A9+1,0xB7);
		Cfunc.SetByte(0x004D17DF+1,0xB7);
		Cfunc.SetByte(0x004D1818+1,0xB7);
		Cfunc.SetByte(0x004D18BC+1,0xB7);
		Cfunc.SetByte(0x004D44A5+1,0xB7);
		Cfunc.SetByte(0x004D451F+1,0xB7);
		Cfunc.SetByte(0x004D5B70+1,0xB7);
		Cfunc.SetByte(0x004D5BA7+1,0xB7);
		Cfunc.SetByte(0x004D5D17+1,0xB7);
		Cfunc.SetByte(0x004D5D4A+1,0xB7);
		Cfunc.SetByte(0x004DAD73+1,0xB7);
		Cfunc.SetByte(0x004DAD9D+1,0xB7);
		Cfunc.SetByte(0x004DB049+1,0xB7);
		Cfunc.SetByte(0x004DB06E+1,0xB7);
		Cfunc.SetByte(0x004DB218+1,0xB7);
		Cfunc.SetByte(0x004DB519+1,0xB7);
		Cfunc.SetByte(0x004DC333+1,0xB7);
		Cfunc.SetByte(0x004DC477+1,0xB7);
		Cfunc.SetByte(0x004DFA4F+1,0xB7);
		Cfunc.SetByte(0x004DFA72+1,0xB7);
		Cfunc.SetByte(0x004E430B+1,0xB7);
		Cfunc.SetByte(0x004E4323+1,0xB7);
		Cfunc.SetByte(0x004E44BD+1,0xB7);
		Cfunc.SetByte(0x004E44D5+1,0xB7);
		Cfunc.SetByte(0x004E4ABB+1,0xB7);
		Cfunc.SetByte(0x004E4B10+1,0xB7);
		Cfunc.SetByte(0x004E4D7C+1,0xB7);
		Cfunc.SetByte(0x004E4DB5+1,0xB7);
		Cfunc.SetByte(0x004E4E0C+1,0xB7);
		Cfunc.SetByte(0x004E5AFE+1,0xB7);
		Cfunc.SetByte(0x004E5B16+1,0xB7);
		Cfunc.SetByte(0x004E5B2B+1,0xB7);
		Cfunc.SetByte(0x004E6F71+1,0xB7);
		Cfunc.SetByte(0x004E70BF+1,0xB7);
		Cfunc.SetByte(0x004E7229+1,0xB7);
		Cfunc.SetByte(0x004E8F7D+1,0xB7);
		Cfunc.SetByte(0x004E901B+1,0xB7);
		Cfunc.SetByte(0x004EE608+1,0xB7);
		Cfunc.SetByte(0x004EF026+1,0xB7);
		Cfunc.SetByte(0x004EF209+1,0xB7);
		Cfunc.SetByte(0x004F0AD9+1,0xB7);
		Cfunc.SetByte(0x004F8214+1,0xB7);
		Cfunc.SetByte(0x004FA007+1,0xB7);
		Cfunc.SetByte(0x004FAAA6+1,0xB7);
		Cfunc.SetByte(0x004FAB01+1,0xB7);
		Cfunc.SetByte(0x004FAC94+1,0xB7);
		Cfunc.SetByte(0x004FAE11+1,0xB7);
		Cfunc.SetByte(0x004FB411+1,0xB7);
		Cfunc.SetByte(0x004FB43E+1,0xB7);
		Cfunc.SetByte(0x004FCF73+1,0xB7);
		Cfunc.SetByte(0x004FD2A7+1,0xB7);
		Cfunc.SetByte(0x00502BDF+1,0xB7);
		Cfunc.SetByte(0x005042F3+1,0xB7);
		Cfunc.SetByte(0x00506030+1,0xB7);
		Cfunc.SetByte(0x0051CC55+1,0xB7);
		Cfunc.SetByte(0x00535B4D+1,0xB7);
		Cfunc.SetByte(0x00536074+1,0xB7);
		Cfunc.SetByte(0x005366A3+1,0xB7);
		Cfunc.SetByte(0x0053AF1D+1,0xB7);
		Cfunc.SetByte(0x0053B202+1,0xB7);
		Cfunc.SetByte(0x0053B462+1,0xB7);
		Cfunc.SetByte(0x0053CA7D+1,0xB7);
		Cfunc.SetByte(0x0053D7DE+1,0xB7);
		Cfunc.SetByte(0x0053D84B+1,0xB7);
		Cfunc.SetByte(0x00547C7C+1,0xB7);
		Cfunc.SetByte(0x00565072+1,0xB7);
		Cfunc.SetByte(0x0058E778+1,0xB7);
		Cfunc.SetByte(0x0058E9C7+1,0xB7);
		Cfunc.SetByte(0x0058EC66+1,0xB7);
		Cfunc.SetByte(0x005D46F4+1,0xB7);
	}
	
	//Fix Party
	BYTE cFixPartyZen[31] = {0x8B,0x4D,0xE4,0x8B,0x55,0x0C,0x03,0xC9,0x03,0xC9,0x03,0xC9,0x03,0xC9,0x81,0xC1,0x00,0x24,0x00,0x00,0x89,0x8A,0xD8,0x00,0x00,0x00,0xE9,0x83,0xFC,0xFF,0xFF}; 
    memcpy((int*)0x005174E7,cFixPartyZen,sizeof(cFixPartyZen));
	BYTE cFixPartyZen2[12] = {0xE9,0x65,0x03,0x00,0x00,0x90,0x90,0x90,0x90,0x90,0x90,0x90};
    memcpy((int*)0x0051717D,cFixPartyZen2,sizeof(cFixPartyZen2));

	//BATTLE SOCCER
	*(BYTE*)(0x00560E5F) = 0x45;
	*(BYTE*)(0x00560E60) = 0x10;
	*(BYTE*)(0x00560F18) = 0x8C;
	*(BYTE*)(0x00560F19) = 0x0F;

	//Fix Ring 40
    BYTE ring40[5] = {0xE8, 0xD9, 0x23, 0xFC, 0xFF};
    memcpy((int*)0x004419F9,ring40,sizeof(ring40));

	//*********************************************************************************************************************************

	Cfunc.SetRRetn(0x00403233);		// Destroy Giocp
	Cfunc.SetRRetn(0x004069AB);		// Serial 0x00000000 fix
	Cfunc.SetRRetn(0x00404584);		// HACK TOOL DC Fix

	Cfunc.SetByte(0x00579CFF,0x74);	// Fix DevilSquareEventConnect=1

	Cfunc.SetByte(0x004369B7,0xEB);	// Socket Serial
	Cfunc.SetByte(0x0043880E,0x90);	// Hack reporting FIX
	Cfunc.SetByte(0x0043880F,0x90);	//
	Cfunc.SetByte(0x00438830,0xE9);	//
	Cfunc.SetByte(0x00438831,0x74);	//
	Cfunc.SetByte(0x00438832,0x01);	//
	Cfunc.SetByte(0x00438833,0x00);	//
	Cfunc.SetByte(0x00438835,0x90);	//

	//Cfunc.SetByte(0x004B406F,0xEB);	// Core - error-L1 : CloseClient connect error <--- походу в этом совершенно нет надобности
	Cfunc.SetNop(0x0052DE2F,6); //LogAddTD(lMsg.Get(542),lpObj->m_Index,lpObj->AccountID,lpObj->Name,lpObj->Ip_addr);
	Cfunc.SetNop(0x0052DE85,6); //LogAddTD(lMsg.Get(543),lpObj->m_Index,lpObj->AccountID,lpObj->Name,lpObj->Ip_addr);


	Cfunc.SetNop(0x00458612,27);		// Protocol Error FIX
	Cfunc.SetNop(0x004B33DE,6);		// error-L2 : Index(%d) %x %x %x FIX
	Cfunc.SetByte(0x004B409F,0x90);	// Invalid Socket FIX
	Cfunc.SetByte(0x004B40A0,0x90);	//
	Cfunc.SetByte(0x004B41CF,0xEB);	//

    Cfunc.SetNop(0x0056D6F3,5);		// ggauth.dll Unload 
    Cfunc.SetByte(0x0056D708,0xEB);	//

	if (this->varsFixes[8] == 1)
	{
		Cfunc.SetByte(0x0057FDB3,0x33);    // BC Master Enter FIX
		Cfunc.SetByte(0x0057FDB4,0xC0);    //
		Cfunc.SetByte(0x0057FDB5,0x90);    //
		Cfunc.SetByte(0x0057FE6D,0x33);    //
		Cfunc.SetByte(0x0057FE6E,0xC0);    //
		Cfunc.SetByte(0x0057FE6F,0x90);    //
	}

    Cfunc.SetByte(0x005B031C,0xFF);	// AiElement Error
    Cfunc.SetByte(0x005D9771,0xEB);	// Illusion Temple enter
    Cfunc.SetByte(0x0061018E,0x81);	// Raklion Fix
    Cfunc.SetByte(0x0061018F,0x51);	//
    Cfunc.SetByte(0x00610190,0x01);	//

    Cfunc.SetNop(0x004A17D0,7);		// Drop W/ luck Fix
	Cfunc.SetByte(0x004D6b46,0x3F);	// Arena cannot pvp

    // GM TRansform Ring Fixing
    BYTE JumpGMCode[] = {0xE9,0x3E,0x08,0x00,0x00,0x90,0x90,0x90};
    memcpy((int*)0x0052FAB8,JumpGMCode,sizeof(JumpGMCode));

    BYTE PachtGMCode[] = {0x83,0xC2,0x2E,0x89,0x95,0x6C,0xEC,0xFF,0xFF,0xE9,0xB7,0xF7,0xFF,0xFF};
    memcpy((int*)0x005302FB,PachtGMCode,sizeof(PachtGMCode));

    // Bypass MonsterSkill.txt max Monster 
    Cfunc.SetByte(0x005AAA3C,0x58); 
    Cfunc.SetByte(0x005AAA3D,0x02);

	Cfunc.SetNop(0x0053F5CE,7); // Kun Dun Drop ANC + Luck Fix
    Cfunc.SetNop(0x004A23BA,7); // Selupan Drop Luck Fix 
    Cfunc.SetNop(0x0049E008,7); // Fix Maya Hand Drop Luck 
    Cfunc.SetNop(0x0049E378,7); // Fix NightMare Drop Luck 
    Cfunc.SetNop(0x0049DC81,7); // Fix Boss Crywolf Drop Luck 
    Cfunc.SetNop(0x0049D881,7); // Fix Dark Elf Crywolf Drop Luck 
     
    Cfunc.SetNop(0x0049AA55,7); // Fix Green Ribbon Box Drop Luck 
    Cfunc.SetNop(0x0049AF25,7); // Fix Blue Ribbon Box Drop Luck 

    Cfunc.SetNop(0x0049B875,7); // Red Chocolate Box Drop Luck Fix 
    Cfunc.SetNop(0x0049BD45,7); // Blue Chocolate Box Drop Luck Fix 

    Cfunc.SetNop(0x0049C695,7); // Vermilion Box Drop Luck Fix 
    Cfunc.SetNop(0x0049CB65,7); // Deep Blue Box Drop Luck Fix 
    Cfunc.SetNop(0x004A00A1,7); // GM Box Drop Luck Fix 

    Cfunc.SetNop(0x004A054D,7); // Green Chaos Box Drop Luck Fix 
    Cfunc.SetNop(0x004A09DD,7); // Red Chaos Box Drop Luck Fix 
    Cfunc.SetNop(0x004A0E6D,7); // Puple Chaos Box Drop Luck Fix 

    Cfunc.SetByte(0x005609DB,0xE9); // GM Move M key
    Cfunc.SetByte(0x005609DC,0xF5); // GM Move M key
    Cfunc.SetByte(0x005609DD,0x00); // GM Move M key
    Cfunc.SetByte(0x005609E0,0x90); // GM Move M key
    Cfunc.SetByte(0x005609E1,0x8B); // GM Move M key

	// Fix Potions Bugs;
	BYTE FixPotions[] = {0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90};
	memcpy((int*)0x0042F64B, FixPotions, sizeof(FixPotions));
	memcpy((int*)0x0050223E, FixPotions, sizeof(FixPotions));
	memcpy((int*)0x00502334, FixPotions, sizeof(FixPotions));
	memcpy((int*)0x005023D6, FixPotions, sizeof(FixPotions));

	Cfunc.SetByte(0x004403C2,0xEB);	// Item drop 
	Cfunc.SetByte(0x00520085,0xEB);	// Move item 
	Cfunc.SetByte(0x00523844,0xEB);	// Trade 1  
	Cfunc.SetByte(0x00524168,0xEB);	// Trade 2 
	Cfunc.SetByte(0x0054AFD6,0xEB);	// Mix Jawel 
	Cfunc.SetByte(0x0054B966,0xEB);	// Unmix Jawel 

    //GM can kill, Enter (w7 fix) 
    BYTE FixGMEnter[2] = { 0xEB, 0x42 }; 
    memcpy((int*)0x0050514B,FixGMEnter,sizeof(FixGMEnter)); 

    //Fix Summoner Berserker 65k+ Damage
    BYTE FixBerserker[] = { 0x68, 0xBC, 0x02, 0x00, 0x00 };
    memcpy((int*)0x004E5B45,FixBerserker,sizeof(FixBerserker));

    //Fix Mana Shield 32k+ Stats 
    BYTE FixMShield1[] = { 0xB9, 0xBC, 0x02, 0x00, 0x00 };
    memcpy((int*)0x004DB03D,FixMShield1,sizeof(FixMShield1));
    memcpy((int*)0x004FAA9A,FixMShield1,sizeof(FixMShield1));   
	BYTE FixMShield2[] = { 0xBE, 0x20, 0x03, 0x00, 0x00 };
    memcpy((int*)0x004DB05D,FixMShield2,sizeof(FixMShield2));
    memcpy((int*)0x004FAABA,FixMShield2,sizeof(FixMShield2));
	
	//Serial Fix
    BYTE SERIAL_0[9] = {0xE9,0x90,0x00,0x00,0x00,0x90,0x90,0x90,0x90};
    memcpy((int*)0x00542BD0,SERIAL_0,sizeof(SERIAL_0));

    //Serial 0 when use item 
    BYTE Serial0UseItem[6] = {0xE9,0xAD,0x00,0x00,0x00,0x90}; 
    memcpy ((int*)0x0045A3B2, Serial0UseItem, sizeof(Serial0UseItem));

    //Serial 0 when sell item 
    BYTE Serial0SelItem[6] = {0xE9,0x81,0x00,0x00,0x00,0x90}; 
    memcpy ((int*)0x00446676, Serial0SelItem, sizeof(Serial0SelItem)); 

    //Serial 0 Personal Shop 
    BYTE Serial0PSHop[6] = {0xE9,0xB0,0x00,0x00,0x00,0x90};     
    memcpy ((int*)0x0044A55A, Serial0PSHop, sizeof(Serial0PSHop)); 

    //Serial 0 Buy in Personal Shop 
    BYTE Serial0BPSHop[6] = {0xE9,0xAE,0x00,0x00,0x00,0x90}; 
    memcpy ((int*)0x0044C494, Serial0BPSHop, sizeof(Serial0BPSHop)); 

	// Fix Party Kill Murder -> PK;
	BYTE FixPartyKILL[] = {0xEB , 0x19};
	memcpy((int*)0x0050F27F, FixPartyKILL, sizeof(FixPartyKILL));

    // Fix Party Fono;
    BYTE FixPartyPKKILL[] = {0x74 , 0x07};
    memcpy((int*)0x004D69E4 , FixPartyPKKILL , sizeof(FixPartyPKKILL));
    BYTE FixPartyPKKILL2[] = {0x83 , 0xF9 , 0x64};
    memcpy((int*)0x004D69F9 , FixPartyPKKILL2 , sizeof(FixPartyPKKILL2));
    BYTE FixPartyPKKILL3[] = {0xEB , 0x07};
    memcpy((int*)0x004D6A05 , FixPartyPKKILL3 , sizeof(FixPartyPKKILL3));
    BYTE FixPartyPKKILL4[] = {0x83 , 0xF9 , 0x00};
    memcpy((int*)0x004D6A3C , FixPartyPKKILL4 , sizeof(FixPartyPKKILL4));
    BYTE FixPartyPKKILL5[] = {0x83 , 0xF8 , 0x00};
    memcpy((int*)0x004D6A4B , FixPartyPKKILL5 , sizeof(FixPartyPKKILL5));
    BYTE FixPartyPKKILL6[] = {0x83 , 0xFA , 0x3F};
    memcpy((int*)0x004D6B44 , FixPartyPKKILL6 , sizeof(FixPartyPKKILL6));
    BYTE FixPartyPKKILL7[] = {0xE9 , 0x1D , 0x01 , 0x00 , 0x00 , 0x90};
    memcpy((int*)0x004D6D56 , FixPartyPKKILL7 , sizeof(FixPartyPKKILL7));
    memcpy((int*)0x004D6DC3 , FixPartyPKKILL , sizeof(FixPartyPKKILL));
    BYTE FixPartyPKKILL8[] = {0x83 , 0xFA , 0x64};
    memcpy((int*)0x004D6DD8 , FixPartyPKKILL8 , sizeof(FixPartyPKKILL8));
    memcpy((int*)0x004D6DE4 , FixPartyPKKILL3 , sizeof(FixPartyPKKILL3));
    BYTE FixPartyPKKILL9[] = {0xEB , 0x0B , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90};
    memcpy((int*)0x004D6E4D , FixPartyPKKILL9 , sizeof(FixPartyPKKILL9));
    memcpy((int*)0x004D6E66 , FixPartyPKKILL8 , sizeof(FixPartyPKKILL8));
    BYTE FixPartyPKKILL10[] = {0xEB , 0x0B , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0xEB , 0x90};
    memcpy((int*)0x004D6E6B, FixPartyPKKILL10, sizeof(FixPartyPKKILL10));

    // Fix PK Party Shop and Move;
    BYTE FixPKPartyMove[] = {0x83 , 0xF8 , 0x08};
    memcpy((int*)0x00560C66, FixPKPartyMove, sizeof(FixPKPartyMove));
    BYTE FixPKPartyMShop[] = {0xEB , 0x28};
    memcpy((int*)0x004450EE, FixPKPartyMShop, sizeof(FixPKPartyMShop));

	// Murder Move
	Cfunc.SetByte(0x00560C90, 0x06);
	
	//Fix Packet Per Second
	BYTE cFixPacketPerSecond[6] = {0xE9,0x42,0x01,0x00,0x00,0x90};
	memcpy((int*)0x004B10FB,cFixPacketPerSecond,sizeof(cFixPacketPerSecond));

	//Marlon Quest Fix
    Cfunc.SetByte(0x005044B8,0xEB);
    Cfunc.SetByte(0x00504519,0xEB); 

	// Fix Crash Dump File
	if(this->varsFixes[18] == 1)
	{
		Cfunc.SetByte(0x004C7041,0xE9);
		Cfunc.SetByte(0x004C7042,0x2E);
		Cfunc.SetByte(0x004C7043,0x01);
		Cfunc.SetByte(0x004C7044,0x00);
		Cfunc.SetByte(0x004C7046,0x90);
	}

	// 3rd Class Entra Devil Square
    BYTE CLASSDS[2] = {0xEB, 0x1D};
    memcpy((int*)0x00460396,CLASSDS,sizeof(CLASSDS));

	//-- 3rd Wings Mix Fix & Crash
	*(BYTE*)(0x005F27B6) = 0x64;
	*(BYTE*)(0x005F27B7) = 0xEB;
	*(BYTE*)(0x005F2EB9) = 0xEB;
	*(BYTE*)(0x005F2EBB) = 0x8B;
	*(BYTE*)(0x005F2EBC) = 0x4D;
	*(BYTE*)(0x005F2EBD) = 0x08;
	*(BYTE*)(0x005F2EBE) = 0xC7;
	*(BYTE*)(0x005F2EBF) = 0x81;
	*(BYTE*)(0x005F2EC0) = 0xD8;
	*(BYTE*)(0x005F2EC1) = 0x0E;
	*(BYTE*)(0x005F2EC2) = 0x00;
	*(BYTE*)(0x005F2EC3) = 0x00;
	*(BYTE*)(0x005F2EC4) = 0x28;
	*(BYTE*)(0x005F2EC5) = 0x00;
	*(BYTE*)(0x005F2EC6) = 0x00;
	*(BYTE*)(0x005F2EC7) = 0x00;
	*(BYTE*)(0x005F27B9) = 0x8B;
	*(BYTE*)(0x005F27BA) = 0x4D;
	*(BYTE*)(0x005F27BB) = 0x08;
	*(BYTE*)(0x005F27BC) = 0xC7;
	*(BYTE*)(0x005F27BD) = 0x81;
	*(BYTE*)(0x005F27BE) = 0xD8;
	*(BYTE*)(0x005F27BF) = 0x0E;
	*(BYTE*)(0x005F27C0) = 0x00;
	*(BYTE*)(0x005F27C1) = 0x00;
	*(BYTE*)(0x005F27C2) = 0x3C;
	*(BYTE*)(0x005F27C3) = 0x00;
	*(BYTE*)(0x005F27C4) = 0x00;
	*(BYTE*)(0x005F27C5) = 0x00;




}

