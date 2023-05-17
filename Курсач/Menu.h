#pragma once
#include "windows.h"
#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
using namespace std;

class Menu
{
private:
    int itemsCount;
    int titleItemCount;
    int selectedItem;
    string items[300][50];
    string TitelStrings[50][60];

    void draw() {
        system("cls");
        int maxLength = getMaxLength();
        for (int i = 0; i < titleItemCount; i++) {
            string tmpString = "";
            tmpString = "|   ";
            tmpString = tmpString + TitelStrings[i]->c_str();
            while (tmpString.length() < maxLength + 7)
                tmpString += " ";
            tmpString += "|";
            cout << tmpString << endl;
        }
        for (int i = 0; i < itemsCount; i++) {
            if (i == selectedItem) {

                cout << "|";

                cout << " > " << items[i]->c_str();
                string tmpString = "";
                while (tmpString.length() < maxLength - items[i]->length() + 3)
                    tmpString += " ";
                tmpString += "|";
                cout << tmpString << endl;
            }
            else {
                string tmpString = "";
                tmpString = "|   ";
                tmpString = tmpString + items[i]->c_str();
                while (tmpString.length() < maxLength + 7)
                    tmpString += " ";
                tmpString += "|";
                cout << tmpString << endl;
            }
        }
    }
    int getMaxLength() {
        int maxLength = 0;
        for (int i = 0; i < 300; i++)
            if (items[i]->length() > maxLength)
                maxLength = items[i]->length();
        for (int i = 0; i < 50; i++)
            if (TitelStrings[i]->length() > maxLength)
                maxLength = TitelStrings[i]->length();
        return maxLength;
    }
public:
    Menu() {
        selectedItem = 0;
        itemsCount = 0;
        titleItemCount = 0;
    }
    int getItemsCount() { // количество вариантов
        return itemsCount;
    }
    void eraseTitle() { // очистить заголовок
        titleItemCount = 0;
    }
    void eraseItem() { // очистить вырианты
        itemsCount = 0;
    }
    void eraseAll() { // очистить все 
        eraseTitle();
        eraseItem();
    }
    int getSelectedItem() { // вернуть выбранный вариант
        return selectedItem;
    }
    void addItem(string inString) { // добавить вариант
        items[itemsCount]->assign(inString.c_str());
        itemsCount++;
    }
    void addTitleItem(string inString) { // добавить заголовок
        TitelStrings[titleItemCount]->assign(inString.c_str());
        titleItemCount++;
    }
    void setDown() { 
        selectedItem++;
        if (selectedItem > itemsCount - 1)
            selectedItem = 0;
    }
    void setUp() {
        selectedItem--;
        if (selectedItem < 0)
            selectedItem = itemsCount - 1;
    }

    void run() { // запуск
        char ch = ' ';
        draw();
        while (ch != 13) {
            ch = _getch();
            if (ch == 80) {
                setDown();
                draw();
            }
            if (ch == 72) {
                setUp();
                draw();
            }
        }
    }

};

