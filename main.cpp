#include "cElevator/cElevator.cpp"
#include <iostream>
#include <string>
#include <thread>
#include <conio.h>
#include <time.h>

using std::cout;
using std::cin;
bool pause = false;

/* Функция задержки */
static void delay(int milliseconds)
{
    /* Текущее время */
    clock_t start_time = clock();

    /* Цикл прерывается когда пройдет нужное число миллисекунд */
    while (clock() < start_time + milliseconds)
        ;
}

/* Поток для ввода данных. При введенном символе меняет глобальную переменную pause на true */
static void threadEntry() {

    while (!_kbhit())
        ;

    pause = true;

}


/* Вывод сообщения о доступных командах */
static inline void printCommands() {
    
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
    command = "none";

    /* Запускаем поток */
    std::thread userInput(threadEntry);

    /* Запускаем цикл работы, один проход цикла - 1 секунда работы лифта */
    while (flag ) {

        /* Взаимодействие с пользователем */
        if (pause) {
            bool validCommand = false;

            /* Ввод команды с проверкой на ошибки */
            while (!validCommand) {

                cout << "\nCommand: ";
                cin >> command;
                if (command.length() > 1 && command.length() < 5)
                    validCommand = true;
                else {
                    cout << "Invalid command. Enter again.\n";
                    printCommands();
                }

            }
        }
        /* Ввод команды с проверкой результата, если false - выходим из программы */
        if (!currentElevator.command(command)) {
            return 0;
            userInput.detach();
        }
        else {
            pause = false;
            command = "none";
            /* Запускаем поток заново */
            userInput.detach();
            userInput = std::thread(threadEntry);
        }
            
        /* Задержка 1 секунда */
        delay(1000);

    }

    userInput.detach();
}
