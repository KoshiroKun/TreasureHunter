/*
@author Kuroud0
@version 1.00
@date 05/03/2018
*/
#pragma once
#include <iostream>
#include <string>
#define int32 int
#define FText std::string

class Utils
{
public:
	int32 static CaptureIntFromUser(FText message);
	void static ClearScreen();
private:
};