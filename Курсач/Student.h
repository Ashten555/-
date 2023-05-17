#pragma once
#include <string>
#include "Menu.h"
#include "AddClass.h"
#include <fstream>
#include "List.h"
#include "Exams.h"
using namespace std;

struct Date {
	int day;
	int month;
	int year;
};

const string startRecordString = "### Start Record";
const string endRecordString = "### End Record";

struct StudentNode
{
	string fName;
	string sName;
	string tName;
	string faculty;
	string department;
	string group;
	string bookNumber;
	Date birthDate;
	bool sex;
	int startYear;
	int id;
	float countMarks3;

	ExamsRecords examsRecords[9][10];

};

class Student
{
	StudentNode* sn;

public:
	List <string> list;
	List <StudentNode> DataBase;
	Student() {
		sn = new StudentNode();
	}

	~Student() {
	}

	StudentNode* getStudentNode() {
		return sn;
	}

	void newMasStud(StudentNode* sn) {
		list.clear();
		Student* stud = new Student();
		list.insert(list.begin(), stud->setParam("fName", sn->fName));
		list.insert(list.begin(), stud->setParam("sName", sn->sName));
		list.insert(list.begin(), stud->setParam("tName", sn->tName));
		list.insert(list.begin(), stud->setParam("faculty", sn->faculty));
		list.insert(list.begin(), stud->setParam("department", sn->department));
		list.insert(list.begin(), stud->setParam("group", sn->group));
		list.insert(list.begin(), stud->setParam("bookNumber", sn->bookNumber));
		list.insert(list.begin(), stud->setParam("birthDate.day", sn->birthDate.day));
		list.insert(list.begin(), stud->setParam("birthDate.month", sn->birthDate.month));
		list.insert(list.begin(), stud->setParam("birthDate.year", sn->birthDate.year));
		int Sex = 0;
		if (sn->sex)
			Sex = 1;
		else
			Sex = 0;
		list.insert(list.begin(), stud->setParam("sex", Sex));
		list.insert(list.begin(), stud->setParam("startYear", sn->startYear));

		int sem = 0;
		int num = 0;
		for (int sem = 0; sem < 9; sem++)
			for (int num = 0; num < 10; num++)
				if (not sn->examsRecords[sem][num].isEmpty) {

					list.insert(list.begin(), stud->setParam("examsResults_" + std::to_string(sem)
						+ "_" + std::to_string(num) + "_n", sn->examsRecords[sem][num].name));
					list.insert(list.begin(), stud->setParam("examsResults_" + std::to_string(sem)
						+ "_" + std::to_string(num) + "_m", std::to_string(sn->examsRecords[sem][num].result)));
				}
		delete stud;
	}

	bool setSex() {
		Menu* sexMenu = new Menu();
		int choice = 0;
		int exit = 3;
		sexMenu->addTitleItem("Пол: ");
		sexMenu->addItem("Мужской");
		sexMenu->addItem("Женский");
		while (choice != exit) {
			sexMenu->run();
			choice = sexMenu->getSelectedItem();
			switch (choice) {
			case 0:
				return false;
				choice = exit;
				break;
			case 1:
				return true;
				choice = exit;
				break;
			default:
				break;
			}
		}
		delete sexMenu;
	}

	string setDepartment() {
		Menu* DepartmentMenu = new Menu();
		string tmpStr = "";
		int choice = -1;
		int exit = 10;
		DepartmentMenu->addTitleItem("Кафедра (институт): ");
		DepartmentMenu->addItem("ИКБ :)");
		DepartmentMenu->addItem("ИИИ");
		DepartmentMenu->addItem("ИИТ");
		DepartmentMenu->addItem("ИПТИП");
		DepartmentMenu->addItem("ИРИ");
		DepartmentMenu->addItem("ИТУ");
		DepartmentMenu->addItem("ИТХТ");
		while (choice != exit) {
			DepartmentMenu->run();
			choice = DepartmentMenu->getSelectedItem();
			switch (choice) {
			case 0:
				tmpStr = "ИКБ :)";
				choice = exit;
				break;
			case 1:
				tmpStr = "ИИИ";
				choice = exit;
				break;
			case 2:
				tmpStr = "ИИТ";
				choice = exit;
				break;
			case 3:
				tmpStr = "ИПТИП";
				choice = exit;
				break;
			case 4:
				tmpStr = "ИРИ";
				choice = exit;
				break;
			case 5:
				tmpStr = "ИТУ";
				choice = exit;
				break;
			case 6:
				tmpStr = "ИТХТ";
				choice = exit;
				break;
			default: break;
			}
		}
		return tmpStr;
		delete DepartmentMenu;
	}

	void addStudent(StudentNode* sn) {
		Menu* StuMenu = new Menu();
		const int Exit = 0;
		int selectedStuMenu = -1;
		AddClass* ce = new AddClass();
		StuMenu->addItem("Выход");
		StuMenu->addItem("Введите фамилию");
		StuMenu->addItem("Введите имя");
		StuMenu->addItem("Введите отчество");
		StuMenu->addItem("Введите дату рождения");
		StuMenu->addItem("Введите номер зачетной книжки");
		StuMenu->addItem("Выберите пол");
		StuMenu->addItem("Введите факультет");
		StuMenu->addItem("Выберите кафедру");
		StuMenu->addItem("Введите год поступления");
		StuMenu->addItem("Введите группу");
		StuMenu->addItem("Добавить результаты экзаменов");
		int day, month, year;
		while (selectedStuMenu != Exit) {
			StuMenu->eraseTitle();
			StuMenu->addTitleItem("Информация:");
			StuMenu->addTitleItem("ФИО: " + sn->fName+ " " + sn->sName + " " + sn->tName);
			string sex = "";
			if (!sn->sex) { sex = "Мужской"; }
			else if (sn->sex){sex = "Женский"; }
			StuMenu->addTitleItem("Пол: " + sex); 
			StuMenu->addTitleItem("Дата рождения: " + to_string(sn->birthDate.day)
			+ "." + std::to_string(sn->birthDate.month) + "." + to_string(sn->birthDate.year));
			StuMenu->addTitleItem("Год начала обучения: " + to_string(sn->startYear));
			StuMenu->addTitleItem("Номер зачетной книжки: " + sn->bookNumber);
			StuMenu->addTitleItem("Группа: " + sn->group);
			StuMenu->addTitleItem("Факультет: " + sn->faculty);
			StuMenu->addTitleItem("Кафедра: " + sn->department);
			StuMenu->addTitleItem("");
			StuMenu->run();
			selectedStuMenu = StuMenu->getSelectedItem();
			string tmpString = "";
			ExamsRecords recordExams[9][10];
			int year = 0;
			int startYear = 0;
			switch (selectedStuMenu) {
			case 0: 
				selectedStuMenu = Exit;
				break;
			case 1:
				ce->setLable("Фамилия ");
				sn->fName = ce->setdateString(sn->fName);
				break;
			case 2:
				ce->setLable("Имя ");
				sn->sName = ce->setdateString(sn->sName);
				break;
			case 3:
				ce->setLable("Отчество ");
				sn->tName = ce->setdateString(sn->tName);
				break;
			case 4:
				ce->setLable("День ");
				sn->birthDate.day = ce->setdateInt(1, 31);
				ce->setLable("Месяц ");
				sn->birthDate.month = ce->setdateInt(1, 12);
				ce->setLable("Год ");
				sn->birthDate.year = ce->setdateInt(1900, 2010);
				break;
			case 5:
				ce->setLable("Номер зачетной книжки ");
				sn->bookNumber = ce->setdateString(sn->bookNumber);
				break;
			case 6:
				ce->setLable("Пол ");
				sn->sex = setSex();
				break;
			case 7:
				ce->setLable("Факультет ");
				sn->faculty = ce->setdateString(sn->faculty);
				break;
			case 8:
				ce->setLable("Кафедра ");
				sn->department = setDepartment();
				break;
			case 9:
				ce->setLable("Год поступления ");
				sn->startYear = ce->setdateInt(1900, 2022);
				break;
			case 10:
				ce->setLable("Группа ");
				sn->group = ce->setdateString(sn->group);
				break;
			case 11:
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 10; j++) {
						recordExams[i][j].name = sn->examsRecords[i][j].name;
						recordExams[i][j].isEmpty = sn->examsRecords[i][j].isEmpty;
						recordExams[i][j].result = sn->examsRecords[i][j].result;
					}
				}
				addExams(sn);
				break;
			default: break;
			}
		}
		delete StuMenu;
		delete ce;
	}

	void addExams(StudentNode* sn) {
		Menu* sesMenu = new Menu();
		int choice = -1;
		const int exit = 0;
		Menu* examsMenu = new Menu();
		int result = -1;
		Exams* exams = new Exams();
		sesMenu->addItem("Выход");
		for (int i = 1; i < 10; i++) {
			sesMenu->addItem("Сессия №" + to_string(i));
		}
		while (choice != exit) {
			sesMenu->eraseTitle();
			sesMenu->addTitleItem("Экзамены:");
			sesMenu->run();
			choice = sesMenu->getSelectedItem();
			if (choice == exit) {
				choice = exit;
				break;
			}
			int Sess = choice;
			if ((Sess >= 1) and (Sess <= 10)) {
				examsMenu->eraseAll();
				examsMenu->addTitleItem("Сессия №" + to_string(Sess));
				result = 1;
				while (result != exit) {
					examsMenu->eraseItem();
					examsMenu->addItem("Выход");
					examsMenu->addItem("Добавить предмет и оценку");
					examsMenu->addItem("Удалить ");
					for (int i = 0; i < 10; i++) {
						if (not sn->examsRecords[Sess - 1][i].isEmpty) 
						{
							string resultmark = "";
							int resultInt = sn->examsRecords[Sess - 1][i].result;
							if (resultInt == 0) resultmark = "Не зачёт";
							if (resultInt == 1) resultmark = "Зачёт";
							if ((resultInt >= 2) and (resultInt <= 5)) {
								resultmark = to_string(resultInt);
							}
							examsMenu->addItem("Предмет: " + sn->examsRecords[Sess - 1][i].name
								+ " Результат: " + resultmark);
						}
					}
					examsMenu->run();
					result = examsMenu->getSelectedItem();
					if (result == 0) result = exit;
					if (result == 1) {
						int num = examsMenu->getItemsCount()-4;
						if (num > 9) {
							system("cls");
							cout << "Вводить больше 9 предметов ввобдить нельзя!!!";
							_getch();
						}
						else {
							addExams(sn, Sess, num);
						}
					}
					if (result == 2) {
						DelitExam(sn, Sess);
					}
					if (result > 2) {
						addExams(sn, Sess, result - 3);
					}
				}
			}
			choice = Sess;
		}
		delete exams;
		delete sesMenu;
		delete examsMenu;
	}

	void addExams(StudentNode* sn, int Sess, int Item) {
		AddClass* ac = new AddClass();
		ac->setLable("Предмет ");
		sn->examsRecords[Sess - 1][Item].name = ac->setdateString(sn->examsRecords[Sess-1][Item].name);
		int result = -1;
		int exit = 0;
		Menu* markMenu = new Menu();
		markMenu->addTitleItem("Оценка");
		markMenu->addItem("Не зачёт"); 
		markMenu->addItem("Зачёт"); 
		markMenu->addItem("2"); 	
		markMenu->addItem("3"); 		
		markMenu->addItem("4"); 		
		markMenu->addItem("5"); 
		while (result != exit) {
			markMenu->run();
			result = markMenu->getSelectedItem();
			sn->examsRecords[Sess - 1][Item].result = result;
			result = exit;
		}
		sn->examsRecords[Sess - 1][Item].isEmpty = false;
		delete ac;
		delete markMenu;
	}

	void DelitExam(StudentNode* sn, int Sess) {
		AddClass* ac = new AddClass();
		int result = -1;
		int exit = 0;
		Menu* ExMenu = new Menu();
		ExMenu->addTitleItem("Предмет");
		while (result != exit) {
			ExMenu->eraseItem();
			ExMenu->addItem("Выход");
			for (int i = 0; i < 10; i++)
				if (not sn->examsRecords[Sess - 1][i].isEmpty)
				{
					string markString = "";
					int markInt = sn->examsRecords[Sess - 1][i].result;
					if (markInt == 0) markString = "Не зачёт";
					if (markInt == 1) markString = "Зачёт";
					if ((markInt >= 2) and (markInt <= 5)) {
						markString = to_string(markInt);
					}
					ExMenu->addItem("Предмет: " + sn->examsRecords[Sess - 1][i].name + " Результат: "
						+ markString);
				}
			ExMenu->run();
			result = ExMenu->getSelectedItem();
			if (result == exit)
				result = exit;
			else {
				sn->examsRecords[Sess - 1][result - 1].isEmpty = true;
				Exams* ex = new Exams();
				for (int i = 0; i < 10; i++) {
					if (not sn->examsRecords[Sess - 1][i].isEmpty) {
						ex->add(0, sn->examsRecords[Sess - 1][i].name,
							sn->examsRecords[Sess - 1][i].result);
					}
				}
				for (int i = 0; i < 10; i++) {
					sn->examsRecords[Sess - 1][i].isEmpty = true;
				}
				for (int i = 0; i < 10; i++) {
					if (not ex->data[0][i].isEmpty) {
						sn->examsRecords[Sess - 1][i].isEmpty = false;
						sn->examsRecords[Sess - 1][i].name = ex->data[0][i].name;
						sn->examsRecords[Sess - 1][i].result = ex->data[0][i].result;
					}
				}
				delete ex;
			}
		}
		delete ac;
		delete ExMenu;
	}

	string getName(string inString) {
		string tmpString = "000";
		int lengthName = 0;
		tmpString[0] = inString[5];
		tmpString[1] = inString[6];
		tmpString[2] = inString[7];
		lengthName = atoi(tmpString.c_str());
		tmpString = "000";
		tmpString[0] = inString[20];
		tmpString[1] = inString[21];
		tmpString[2] = inString[22];
		int lengthValue = 0;
		lengthValue = atoi(tmpString.c_str());
		int offset = 28;
		string valueString(lengthName, ' ');
		for (int i = 0; i < lengthName; i++) {
			valueString[i] = inString[i + offset - 1];
		}
		return valueString;
	}

	string getType(string inString) {
		string ch = " ";
		ch[0] = inString[16];
		if (ch.compare("i") == 0) {
			return "int";
		}
		if (ch.compare("s") == 0) {
			return "str";
		}
		return "";
	}

	string getValueStr(string inString) {
		string tmpString = "000";
		int lengthName = 0;
		tmpString[0] = inString[5];
		tmpString[1] = inString[6];
		tmpString[2] = inString[7];
		lengthName = atoi(tmpString.c_str());
		tmpString = "000";
		tmpString[0] = inString[20];
		tmpString[1] = inString[21];
		tmpString[2] = inString[22];
		int lengthValue = 0;
		lengthValue = atoi(tmpString.c_str());
		int offset = 28;
		string valueString(lengthValue, '0');
		for (int i = 0; i < lengthValue; i++) {
			valueString[i] = inString[i + offset + lengthName];
		}
		return valueString;
	}

	int getValueInt(string inString) {
		string tmpString = "000";
		int lengthName = 0;
		tmpString[0] = inString[5];
		tmpString[1] = inString[6];
		tmpString[2] = inString[7];
		lengthName = atoi(tmpString.c_str());
		tmpString = "000";
		tmpString[0] = inString[20];
		tmpString[1] = inString[21];
		tmpString[2] = inString[22];
		int lengthValue = 0;
		lengthValue = atoi(tmpString.c_str());
		int offset = 28;
		string valueString(lengthValue, '0');
		for (int i = 0; i < lengthValue; i++) {
			valueString[i] = inString[i + offset + lengthName];
		}
		return atoi(valueString.c_str());
	}

	string setParam(string name, int intvalue) {
		string outString = "name:000; value:int:000 -: ";
		string value = std::to_string(intvalue);
		int offset = outString.length(); //28
		string lengthName = std::to_string(name.length());
		if (lengthName.length() == 1) {
			outString[7] = lengthName[0];
		}
		if (lengthName.length() == 2) {
			outString[6] = lengthName[0];
			outString[7] = lengthName[1];
		}
		string lengthValue = std::to_string(value.length());
		if (lengthValue.length() == 1) {
			outString[22] = lengthValue[0];
		}
		if (lengthValue.length() == 2) {
			outString[21] = lengthValue[0];
			outString[22] = lengthValue[1];
		}
		outString = outString + name + "=" + value;
		return outString;
	}

	string setParam(string name, string value) {
		string outString = "name:000; value:str:000 -: ";
		//  0123456789012345678901234567
		int offset = outString.length(); //28
		//cout << offset;
		string lengthName = std::to_string(name.length());
		if (lengthName.length() == 1) {
			outString[7] = lengthName[0];
		}
		if (lengthName.length() == 2) {
			outString[6] = lengthName[0];
			outString[7] = lengthName[1];
		}
		string lengthValue = std::to_string(value.length());
		if (lengthValue.length() == 1) {
			outString[22] = lengthValue[0];
		}
		if (lengthValue.length() == 2) {
			outString[21] = lengthValue[0];
			outString[22] = lengthValue[1];
		}
		outString = outString + name + "=" + value;
		return outString;
	}

	int getCountMarks3(StudentNode* sn, List <int> rangeSem) {
		int count = 0;
		for (int i=0; i<2 ; i++)
			for (int j = 0; j < 10; j++)
				if (sn->examsRecords[i][j].result == 3) {
					count++;
				}
		return count;
	}

};
