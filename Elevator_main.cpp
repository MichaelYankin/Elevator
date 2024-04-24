
// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "cElevator.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;

/* Вывод сообщения о доступных командах */
void printCommands() {
    
    cout << "Available commands:\n";
    cout << "    - Fx - elevator request on the floor x;\n";
    cout << "    - Cx - passenger request to the floor x;\n";
    cout << "    - none - no command for 1 second of elevator movement;\n";
    cout << "    - exit - quit program.\n";

}

int main()
{
    
    bool flag = true;
    std::string command;
    int floors = 0, currentFloor = 0;

    /* Ввод количества этажей с проверкой на ошибки */
    /* В примере работы программы этажность задается двумя цифрами*/
    /* Будем считать, что максимальное число этажей - 99 */
    while (flag) {

        cout << "Enter maximum amount of floors in the building: ";
        std::string tmp;
        cin >> tmp;
        floors = atoi(tmp.c_str());
        if (floors > 1 && floors < 100)
            flag = false;
        else
            cout << "Input error, enter integer higher than 1!\n";

    }
    
    /* Ввод текущего этажа с проверкой на ошибки */
    while (!flag) {

        cout << "Enter the current floor: ";
        std::string tmp;
        cin >> tmp;
        currentFloor = atoi(tmp.c_str());
        if (currentFloor > 0 && currentFloor <= floors)
            flag = true;
        else
            cout << "Input error, enter integer higher than 0 and less than maximum floors!\n";

    }

    /* Выводим доступные команды */
    printCommands();

    /* Запускаем лифт */
    cElevator currentElevator(currentFloor, floors);

    /* Запускаем цикл работы, один проход цикла - 1 секунда работы лифта */
    while (flag) {

        /* Взаимодействие с пользователем */
        cout << "<Press any key to enter new command>";
        cin.sync();
        char temp;
        cin.get(temp);
        bool validCommand = false;
        /* Ввод команды с проверкой на ошибки */
        while (!validCommand) {

            cout << "\nCommand: ";
            cin >> command;
            if (command.length() > 2 && command.length() < 5)
                validCommand = true;
            else {
                cout << "Invalid command. Enter again.\n";
                printCommands();
            }

        }
        
        /* Ввод команды с проверкой результата, если false - выходим из программы */
        if (!currentElevator.command(command))
            flag = false;

    }

}
