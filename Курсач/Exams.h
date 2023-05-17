#pragma once
#include <string>
using namespace std;

struct ExamsRecords {
	string name;
	int result;
	bool isEmpty;
};

class Exams
{
public:
	ExamsRecords data[9][10];

	Exams() {
		empty();
	}

	void empty() {
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 10; j++)
				data[i][j].isEmpty = true;
	}

	bool add(int sess, string item, int mark) {
		int firstEmptyRow = get1Row(sess);
		if (firstEmptyRow < 9) {
			data[sess][firstEmptyRow].isEmpty = false;
			data[sess][firstEmptyRow].name = item;
			data[sess][firstEmptyRow].result = mark;
			return true;
		}
		else
			return false;
	}
	bool add(int sess, string item, bool zach) {
		int mark = 0;
		if (zach)
			mark = 1;
		else
			mark = 0;
		int firstEmptyRow = get1Row(sess);
		if (firstEmptyRow < 9) {
			data[sess][firstEmptyRow].isEmpty = false;
			data[sess][firstEmptyRow].name = item;
			data[sess][firstEmptyRow].result = mark;
			return true;
		}
		else
			return false;
	}

	int get1Row(int sessNum) {
		for (int i = 0; i < 10; i++)
			if (data[sessNum][i].isEmpty)
				return i;
		return -1;
	}
};

