#pragma once
#include "windows.h"
#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include "Menu.h"

using namespace std;

class AddClass
{
	string date;
	string label;

public:
	AddClass() {};
	void setLable(string lable) {
		label = lable;
	}
	void draw() {
		system("cls");
		int maxLen = label.length();
		string tempStr = "";
		tempStr = "|   ";
		tempStr = tempStr + label.c_str();
		while (tempStr.length() < maxLen + 7)
			tempStr += " ";
		tempStr += "|";
		cout << tempStr << endl;
	}

	string setdateString(string dateString) {

		label = label;
		draw();
		date = dateString;
		cout << date;
		char ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == 8) {
				string tmpString = "";
				tmpString = date;
				date = "";
				if (tmpString.length() > 0) {
					for (int i = 0; i < tmpString.length() - 1; i++)
						date = date + tmpString[i];
					draw();
					cout << date;
				}
				continue;
			}
			if (isDigit(ch) or isAlpha(ch) or isSpace(ch)) {
				cout << ch;
				date = date + ch;
			}
		}
		return date;
	}
	bool isDigit(int ch) {
		if (ch >= 48 and ch <= 57 or ch == 46 or ch == 45)
			return true;
		else
			return false;

	}
	bool isAlpha(int ch) {
		if (ch >= 65 and ch <= 90)
			return true;
		if (ch >= 97 and ch <= 122)
			return true;
		if (ch >= -200 and ch <= -1)
			return true;
		return false;
	}
	bool isSpace(char ch) {
		if (ch == 32)
			return true;
		else
			return false;
	}

	int setdateInt(int startRange, int endRange) {
		draw();
		string inString = "";
		while (inString.length() == 0) {
			cin >> inString;
			if (not isDigit(inString)) {
				inString = "";
				cout << "Введите цифры.";
				_getch();
				continue;
			}
			int tmpInt = atoi(inString.c_str());
			if ((tmpInt < startRange) or (tmpInt > endRange)) {
				inString = "";
				cout << "Дата вне диапазона";
				_getch();
				continue;
			}
		}	
		date = inString;
		return atoi(date.c_str());
	}

	bool isDigit(string inString) {
		bool flag = true;
		for (int i = 0; i < inString.length(); i++)
		{
			if (not isdigit(inString[i]))
				flag = false;
		}
		return flag;
	}
};

