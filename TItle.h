#pragma once
#include <stdio.h>
#include <Windows.h>



class Title
{
public:
	void get_title(int stage);

	void evolotion();

	void Color(unsigned short text) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
	}

};



