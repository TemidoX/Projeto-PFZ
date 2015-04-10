#ifndef FIXES_H
#define FIXES_H
#pragma once
#include "User.h"

class cFixes
{
public:
	cFixes();
	~cFixes();
	void LoadFixes();
private:
	int varsFixes[20];
	void FixesSeason4();
	
};
extern cFixes fixes;













#endif // !_FIXES_H