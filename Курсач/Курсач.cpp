
#include <iostream>
#include <string>
#include "Menu.h"
#include <fstream>
#include <windows.h>
#include "Student.h"
#include "List.h"
#include <time.h>


using namespace std;

void Crypt();
void Decrypt();

class FileWork: public Student {
public:
	List <StudentNode> DataBase;
	List <int> rangeSem;
	FileWork() {
		DataBase.clear();
	}
	~FileWork() {
		DataBase.clear();
	}


	void SaveToFileBin(string Name) {
		ofstream out(Name, ios::binary | ios::app | ios::out);
		if (out.is_open()) {
			Student st = Student();
			int recordCount = getRecordCount();
			StudentNode* sn;
			for (int i = 0; i < recordCount; i++) {
				out.write(startRecordString.c_str(), sizeof(startRecordString));
				sn = &DataBase.at(i);
				st.newMasStud(sn);
				while (!st.list.empty()) {
					out.write(st.list.at(0).c_str(), sizeof(st.list.at(0)));
					st.list.erase(st.list.begin());
				}
				out.write(endRecordString.c_str(), sizeof(endRecordString));
			}
		}
		out.close();
	}

	void ReadBin(string Name) {
		ifstream in(Name, ios::binary | ios::in);
		in.read((char*)&DataBase, sizeof(DataBase));
		in.close();
	}

	void SaveToFile(string Name) {
		ofstream SaveFile;
		SaveFile.open(Name);
		if (SaveFile.is_open()) {
			Student st = Student();
			int recordsCount = getRecordCount();
			StudentNode* sn;
			for (int i = 0; i < recordsCount; i++) {
				SaveFile << startRecordString << endl;
				sn = &DataBase.at(i);
				st.newMasStud(sn);
				while (!st.list.empty()) {
					SaveFile << st.list.at(0) << endl;
					st.list.erase(st.list.begin());
				}
				SaveFile << endRecordString << endl;
			}
		}
		SaveFile.close();
		
	}

	void ReadFile(string name) {
		string str;
		int count = 0;
		ifstream File(name, ios::in);
		if (File.is_open())
		{
			bool isRecord = true;
			StudentNode* sn = new StudentNode();
			int studentId = 0;
			while (getline(File, str))
			{
				if (strcmp(startRecordString.c_str(), str.c_str()) == 0) {
					isRecord = true;
					continue;
				}
				if (strcmp(endRecordString.c_str(), str.c_str()) == 0) {
					isRecord = false;
					studentId++;
					DataBase.push_front(*sn);
					continue;
				}
				if (isRecord) {
					string valueName = getName(str);
					if (strcmp(getType(str).c_str(), "str") == 0)
					{
						string value = getValueStr(str);
						if (strcmp("fName", valueName.c_str()) == 0)
							sn->fName = value;
						if (strcmp("sName", valueName.c_str()) == 0)
							sn->sName = value;
						if (strcmp("tName", valueName.c_str()) == 0)
							sn->tName = value;
						if (strcmp("faculty", valueName.c_str()) == 0)
							sn->faculty = value;
						if (strcmp("department", valueName.c_str()) == 0)
							sn->department = value;
						if (strcmp("group", valueName.c_str()) == 0)
							sn->group = value;
						if (strcmp("bookNumber", valueName.c_str()) == 0)
							sn->bookNumber = value;
						for (int i = 0; i < 9; i++)
							for (int j = 0; j < 10; j++) {
								string testNameString = "";
								testNameString = testNameString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_n";
								string testMarkString = "";
								testMarkString = testMarkString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_m";
								if (strcmp(testNameString.c_str(), valueName.c_str()) == 0) {
									sn->examsRecords[i][j].name = value;
									sn->examsRecords[i][j].isEmpty = false;
								}
								if (strcmp(testMarkString.c_str(), valueName.c_str()) == 0) {
									sn->examsRecords[i][j].result = atoi(value.c_str());
									sn->examsRecords[i][j].isEmpty = false;
								}
							}
					}
					else {
						int value = getValueInt(str);
						if (strcmp("birthDate.day", valueName.c_str()) == 0)
							sn->birthDate.day = value;
						if (strcmp("birthDate.month", valueName.c_str()) == 0)
							sn->birthDate.month = value;
						if (strcmp("birthDate.year", valueName.c_str()) == 0)
							sn->birthDate.year = value;
						
						if (strcmp("id", valueName.c_str()) == 0)
							sn->id = studentId;
						if (strcmp("startYear", valueName.c_str()) == 0)
							sn->startYear = value;
						if (strcmp("sex", valueName.c_str()) == 0)
							if (value == 0)
								sn->sex = false;
							else
								sn->sex = true;
					}
				}
			}
			File.close();
		}
		else {
			cout << " \n Файл не открыт \n";
			_getch();
		}
		File.close();
	}

	int getRecordCount() {
		return DataBase.size();
	};

	void updateCountMarks3() {
		Student* stud = new Student();
		for (int i = 0; i < DataBase.size(); i++) {
			DataBase.at(i).countMarks3 = stud->getCountMarks3(&DataBase.at(i), rangeSem);
		}
		delete stud;
	}

	List <StudentNode>::iterator getMaxCountMarks3() {
		List<StudentNode>::iterator pos = DataBase.begin();
		List<StudentNode>::iterator mMinPos = pos;
		while (pos != DataBase.end()) {
			if ((*pos).countMarks3 > (*mMinPos).countMarks3)
				mMinPos = pos;
			++pos;
		}
		return mMinPos;
	}

	void sortByCountMarks3() {

		List<StudentNode>::iterator pos = getMaxCountMarks3();
		List <StudentNode> sortedLst;
		
		while (!DataBase.empty()) {
			sortedLst.push_front(*getMaxCountMarks3());
			DataBase.erase(getMaxCountMarks3());
		}
		for (auto item : sortedLst) {
			DataBase.push_front(item);
		}

	}



	void print_Student_countMarks3_man() {
		for (auto item : DataBase) {
			if (item.sex == false) {
				cout << item.fName + " " + item.sName + " " + item.tName + " " + to_string(item.countMarks3/0.2) << "%" << endl;
			}
		}
	}

	void print_Student_countMarks3_women() {
		for (auto item : DataBase) {
			if (item.sex == true) {
				cout << item.fName + " " + item.sName + " " + item.tName + " " + to_string(item.countMarks3/0.2) + "%" << endl;
			}
		}
	}

};

int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string FileName_bin = "Database.bin";
	string FileName = "Database.txt";
	Menu* MainMenu = new Menu();
	StudentNode* sn = new StudentNode();
	Student* stud = new Student();
	FileWork* studlist = new FileWork();
	Menu* sortMenu = new Menu();
	Decrypt();
	studlist->ReadFile(FileName);
	MainMenu->addTitleItem("Основное меню:");
	MainMenu->addItem("Посмотреть весь список студентов (удалить или изменить данные)");
	MainMenu->addItem("Добавить данные о студенте");
	MainMenu->addItem("Сохранить всё в файл");
	MainMenu->addItem("Выполнить 37 вариант");
	MainMenu->addItem("Выход");
	MainMenu->run();
	Menu* StudentMenu = new Menu();
	Menu* DelitStudent = new Menu();
	Menu* sMenu = new Menu();
	int selectedItem = 0;
	int exit = 4;
	int selectedItemStudent = -1;
	int exitStudent = 0;
	int choice = -1;
	int s = -1;
	List<StudentNode>::iterator pos();
	while (selectedItem != exit) {
		MainMenu->run();
		selectedItem = MainMenu->getSelectedItem();
		switch (selectedItem) {
		case 0:
			selectedItemStudent = 0;
			while (selectedItemStudent != exit) {
				StudentMenu->eraseItem(); 
				StudentMenu->addItem("Выход");
				StudentMenu->addItem("Удалить студентов");
				for (int i = 0; i < studlist->DataBase.size(); i++) {
					sn = &studlist->DataBase.at(i);
					string tmpString = sn->fName + " " + sn->sName + " " + sn->tName + " " + sn->bookNumber;
					StudentMenu->addItem(tmpString);
				}
				StudentMenu->run();
				selectedItemStudent = StudentMenu->getSelectedItem();
				if (selectedItemStudent == exitStudent) {
					break;
				}
				if (selectedItemStudent == 1) {
					DelitStudent->eraseAll();
					DelitStudent->addTitleItem("Выберите студента для удаления данных");
					DelitStudent->addItem("Выход");
					int resultDel = 1;
					const int exitDel = 0;
					for (int i = 0; i < studlist->DataBase.size(); i++) {
						sn = &studlist->DataBase.at(i);
						string tmpString = sn->fName + " " + sn->sName + " " + sn->tName;
						DelitStudent->addItem(tmpString);
					}
					while (resultDel != exitDel) {
						DelitStudent->run();
						resultDel = DelitStudent->getSelectedItem();
						if (resultDel == exitDel) {
							break;
						}
						else {
							int num = resultDel - 1;
							studlist->DataBase.erase(next(studlist->DataBase.begin(), num));
							break;
						}
					}
				}
				if (selectedItemStudent > 1) {
					int ind = selectedItemStudent - 2;
					sn = &studlist->DataBase.at(ind);
					string bookNum = "";
					bookNum = sn->bookNumber;
					stud->addStudent(sn);
				}
			}
			break;
		case 1:
			sn = new StudentNode();
			stud->addStudent(sn);
			studlist->DataBase.push_front(*sn);
			break;
		case 2:
			studlist->SaveToFile(FileName);
			studlist->SaveToFileBin(FileName_bin);
			break;
		case 3:
			choice = -1;
				while (choice != 0) {
					sortMenu->eraseAll();
					sortMenu->addTitleItem("Выберите пол для сортировки");
					sortMenu->addItem("Выход");
					sortMenu->addItem("Мужской");
					sortMenu->addItem("Женский");
					sortMenu->run();
					choice = sortMenu->getSelectedItem();
					if (choice == 0) {;
						break;
					}
					if (choice == 1) {
						s = -1;
						while (s != 0) {
							sMenu->eraseItem();
							sMenu->addItem("Выход");
							studlist->updateCountMarks3();
							studlist->print_Student_countMarks3_man();
							studlist->sortByCountMarks3();
							cout << "\n\nОтсортированный список" << endl;
							studlist->print_Student_countMarks3_man();
							system("pause");
							sMenu->run();
							s = sMenu->getSelectedItem();
							if (s == 0) {
								break;
							}
						}
					}
					if (choice == 2) {
						s = -1;
						while (s != 0) {
							sMenu->eraseItem();
							sMenu->addItem("Выход");
							studlist->updateCountMarks3();
							studlist->print_Student_countMarks3_women();
							studlist->sortByCountMarks3();
							cout << "\n\nОтсортированный список" << endl;
							studlist->print_Student_countMarks3_women();
							system("pause");
							sMenu->run();
							s = sMenu->getSelectedItem();
							if (s == 0) {
								break;
							}
						}
					}
				}
				break;
		case 4:
			Crypt();
			break;
		}
	}
	delete MainMenu;
	delete stud;
	delete studlist;
	delete StudentMenu;
	delete DelitStudent;
	delete sortMenu;
	
}


void Crypt() {
	string pass = "";
	cout << "Введите пароль для шифрования" << endl;
	cin >> pass;


	string command = "openssl\\bin\\openssl.exe aes-256-cbc -salt -a -e -in Database.txt -out Database.txt.enc -pass pass:";
	command += pass; 
	system(command.c_str());

	if (remove("Database.txt") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}

	ofstream passFile;
	passFile.open("p.txt");
	passFile.write(pass.c_str(), 10);
	passFile.close();
	
	string new_command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in p.txt -out p.txt.enc";
	//system(new_command.c_str());
	//if (remove("p.txt")!=0) {
	//	cout << "deleting file error;\n";
	//}
}

void Decrypt() {
	string new_command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in p.txt.enc -out p.txt";
	//system(new_command.c_str());

	//if (remove("p.txt.enc")) {
	//	cout << "[ERROR] - delering file" << endl;
	//}

	char* password = new char[10];
	ifstream file_with_pass;
	file_with_pass.open("p.txt", ios::binary);
	file_with_pass.read(password, 11);
	bool flag = false;
	while (!flag) {
		string pass = "";
		cout << "Введите пароль для расшифровки " << endl;
		cin >> pass;
		if (pass == password) {
			flag = true;
			string command = "openssl\\bin\\openssl.exe aes-256-cbc -salt -a -d -in Database.txt.enc -out Database.txt -pass pass:";
			command += pass;
			system(command.c_str());
			continue;
		}
		else {
			cout << "Неправильный пароль!!!" << endl;
			system("pause");
			exit(3);
			flag = false;
			break;
		}
	}

	//if (remove("p.txt") != 0) {
	//	cout << "deleting file error;\n";
	//}
	
	if (remove("Database.txt.enc") != 0) {
		cout << "deleting file error;\n";
	}
}