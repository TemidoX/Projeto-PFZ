#include "StdAfx.h"


char Message[1024];
				   
Logger Log;	   
DWORD PiD;

#define TITTLE "[BR] PFZ Project - Beta 1.0"


Logger::Logger(){}
Logger::~Logger(){} 
void __stdcall LoggerCore(PVOID pVoid)
{					
	while (true)
	{					  
		AllocConsole();
		SetConsoleTitleA(TITTLE);	 
		Sleep(1000);
	}
	_endthread();
}			 

void Logger::LoggerInit()
{
	CreateThread( 0 , 0 , (LPTHREAD_START_ROUTINE) LoggerCore , 0 , 0 , &PiD );
	Sleep(100);
	Log.ConsoleOutPut(0, c_Grey,t_NULL,"::==========================================================================");
	Log.ConsoleOutPut(0, c_Grey,t_NULL,":: PFZ Project (c) BRTeam ");
	Log.ConsoleOutPut(0, c_Grey,t_NULL,":: GameServer 1.00.90");
	Log.ConsoleOutPut(0, c_Grey,t_NULL,":: Protocolo : JPN");
	Log.ConsoleOutPut(0, c_Grey,t_NULL,":: Versão : Open-Source Free");
	Log.ConsoleOutPut(0, c_Grey,t_NULL,":: Coder : Hugo Gomes");
	Log.ConsoleOutPut(0, c_Grey,t_NULL,":: Release : 10/04/2015");
	Log.ConsoleOutPut(0, c_Grey,t_NULL,":: Skype : hugo.alexandre.777");
	Log.ConsoleOutPut(0, c_Grey,t_NULL,"::==========================================================================");
} 		

void Logger::CheckProcent(char* message)
{
	for (UINT i = 0; i <= strlen(message); i++)
	{                          						   
		if(message[i] == '%')		  
		{
			for(UINT j = strlen(message); j >= i; j--)		  
				message[j+1] = message[j];
			i++;
		}
	}
}

void Logger::ConsoleOutPut(int WOL, sColor Color, sLogType Type, const char* Format, ...)
{					
	SYSTEMTIME t;
	GetLocalTime(&t);
	DWORD dwBytesWritten;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf_s(Message,Format, pArguments);
	CheckProcent(Message); // "%" Bug Fix 
	va_end(pArguments);

	char currdate[11] = {0};
	char outputmsg[2048];
	if(WOL == 1)
	{
		sprintf_s(currdate, "(%02d:%02d:%02d)", t.wHour, t.wMinute, t.wSecond);
		sprintf_s(outputmsg,"%s %s\n", currdate,Message);
	}
	else
		sprintf_s(outputmsg,"%s\n", Message); 

	switch(Color)
	{
	case c_Red: 
		SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case c_Green: 
		SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case c_Blue: 
		SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case c_Cyan: 
		SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case c_Yellow: 
		SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case c_Magenta: 
		SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case c_Grey:
		SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	} 

	CreateLog(Type,outputmsg); 
	WriteFile(this->Handle(FALSE), outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);
	SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return;
}

HANDLE Logger::Handle(BOOL Input)
{
	if(Input==TRUE)
		return GetStdHandle(STD_INPUT_HANDLE);
	else
		return GetStdHandle(STD_OUTPUT_HANDLE);
}

void Logger::CreateLog(sLogType Type,const char* Format, ...)
{
	SYSTEMTIME now;
	GetLocalTime(&now);  
																														 
	char ConsoleLog[55];
	char GMLog[55];
	char CommandsLog[55]; 
	char GPostLog[55];	
	char PostLog[55];	
	char DropLog[55];	  
	char BanLog[55];
	char DuelLog[55];				  
	char PcPointLog[55];	
	char IpBlockLog[55];	
	char ErrorLog[55];
	char Date[55];
	sprintf(Date, "..\\PFZPlugin\\BRLogs\\%02d-%02d-%02d\\", now.wDay, now.wMonth, now.wYear); 
	CreateDirectory(Date,NULL);
																													  
	va_list pArguments1;
	va_start(pArguments1, Format);
	vsprintf_s(Message,Format, pArguments1);
	va_end(pArguments1);

	switch (Type)
	{
		case t_NULL:
		break;

		case t_Error:
		{
		SaveFile(ErrorLog, Message);
		}
		break;
		case t_Default: 
		{
			SaveFile(ConsoleLog,Message);
		}
		break; 	
		case t_PCPOINT:
		{
			SaveFile(ConsoleLog,Message);
			SaveFile(PcPointLog,Message);
		}
		break;
		case t_IPBLOCK:
		{
			SaveFile(ConsoleLog,Message);
			SaveFile(IpBlockLog,Message);
		}
		break;
		case t_GM:
		{
			SaveFile(ConsoleLog,Message);
			SaveFile(GMLog,Message);
		}
		break;
		case t_COMMANDS:
		{									
			SaveFile(ConsoleLog,Message);
			SaveFile(CommandsLog,Message);
		}
		break;
		case t_POST: 
		{								 
			SaveFile(ConsoleLog,Message);
			SaveFile(PostLog,Message);
			SaveFile(CommandsLog,Message);
		}
		break;	
		case t_GPOST:
		{		
			SaveFile(ConsoleLog,Message);
			SaveFile(GPostLog,Message);
			SaveFile(CommandsLog,Message);	 
			SaveFile(GMLog,Message);
		}
		break;
		case t_DROP: 
		{										   
			SaveFile(ConsoleLog,Message);
			SaveFile(DropLog,Message);
			SaveFile(CommandsLog,Message);
			SaveFile(GMLog,Message);
		}
		break;
		case t_BAN: 
		{									   
			SaveFile(ConsoleLog,Message);
			SaveFile(BanLog,Message);
			SaveFile(CommandsLog,Message);
			SaveFile(GMLog,Message);
		}
		break;
		case t_Duel: 
		{									   
			SaveFile(ConsoleLog,Message);
			SaveFile(DuelLog,Message);
		}
		break;
	}
}

void Logger::SaveFile(char *logString,char *Message)
{
	FILE *stream;  
	stream=fopen(logString, "a+" );
	fprintf(stream, "%s", Message);
	fclose(stream);
}