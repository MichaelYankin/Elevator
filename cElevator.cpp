#include "cElevator.h"

/* Измлечение данных из команды */
void parseCommand(std::string cmd, int& cmdNumber, int& floor) {

    if (cmd == "none")
        cmdNumber = 2;
    else if (cmd == "exit")
        cmdNumber = 3;
    /* Вызов лифта на этаже */
    else if (cmd[0] == 'f' || cmd[0] == 'F') {
        /* Проверяем, является ли введенная команда числом */
        if (int(cmd[1]) < 48 || int(cmd[1]) > 58 || int(cmd[2]) < 48 || int(cmd[2]) > 58)
            /* Если нет - считаем, что получена неизвестная команда */
            cmdNumber = 4;
        else {
            int tmp_floor = 10 * (int(cmd[1]) - 48) + int(cmd[2]) - 48; /* преобразование в номер этажа */
            /* Проверяем корректность введенного числа */
            if (tmp_floor > 0 && tmp_floor < 100) {
                cmdNumber = 0;
                floor = tmp_floor;
            }
            else
                cmdNumber = 4;
        }
    }
    /* Выбор этажа в лифте */
    else if (cmd[0] == 'c' || cmd[0] == 'C') {
        /* Проверяем, является ли введенная команда числом */
        if (int(cmd[1]) < 48 || int(cmd[1]) > 58 || int(cmd[2]) < 48 || int(cmd[2]) > 58)
            /* Если нет - считаем, что получена неизвестная команда */
            cmdNumber = 4;
        else {
            int tmp_floor = 10 * (int(cmd[1]) - 48) + int(cmd[2]) - 48; /* преобразование в номер этажа */
            /* Проверяем корректность введенного числа */
            if (tmp_floor > 0 && tmp_floor < 100) {
                cmdNumber = 1;
                floor = tmp_floor;
            }
            else
                cmdNumber = 4;
        }
    }
    else
        cmdNumber = 4; /* Неизвестная команда */
}

/* Конструктор по умолчанию */
cElevator::cElevator() :
    movementDirection(0),
    floor(1),
    maxFloors(9)
{
    /* На всех этажах нажаты кнопки и в лифте нажаты кнопки всех этажей */
    passengerRequests = new bool[maxFloors];
    passengerCalls = new bool[maxFloors];
    for (int i = 0; i < maxFloors; i++) {
        passengerCalls[i] = false;
        passengerRequests[i] = false;
    }
    printState();
};

/* Конструктор инициализации */
cElevator::cElevator(int floor, int max_floors) :
    movementDirection(0),
    floor(floor),
    maxFloors(max_floors)
{
    /* На всех этажах нажаты кнопки и в лифте нажаты кнопки всех этажей */
    passengerRequests = new bool[maxFloors];
    passengerCalls = new bool[maxFloors];
    for (int i = 0; i < maxFloors; i++) {
        passengerCalls[i] = false;
        passengerRequests[i] = false;
    }
    printState();
};

/* Деструктор */
cElevator::~cElevator() {
    delete[] passengerRequests;
}

/* Вывод состояния */
void cElevator::printState() {

    cout << "Cabin on floor " << floor << ". ";
    if (movementDirection) {
        movementDirection == 1 ? cout << "Going Down. " : cout << "Going Up. ";
    }
    else {
        cout << "Stopped. ";
        passengerCalls[floor - 1] || passengerRequests[floor - 1] ? cout << "Doors Opened. " : cout << "Doors Closed. ";
    }

}

/* Поиск вызовов лифта на любых этажах */
bool cElevator::anyCalls(int startFloor, int endFloor, int &calledFloor)
{
    int i = startFloor;
    bool found = false;
    while (i < endFloor && !found) {
        if (passengerCalls[i]) {
            found = true;
            calledFloor = i + 1;
        }
        i++;
    }
    return found;
}

/* Поиск номера близжайшего этажа */
int cElevator::nearestCall()
{
    int tmpFloorL = 0; int tmpFloorH = 0;
    /* Ищем запросы на этажах ниже */
    bool callsL = anyCalls(0, floor, tmpFloorL);
    /* Ищем запросы на этажах выше */
    bool callsH = anyCalls(floor, maxFloors, tmpFloorH);
    
    /* Сравниваем расстояние от запросов до текущего этажа */
    if (callsL && callsH) {
        /* Возвращаем номер близжайшего этажа */
        if (floor - tmpFloorL < tmpFloorH - floor)
            return tmpFloorL;
        else
            return tmpFloorH;
    }
    /* Если запрос только на этаже ниже - возвращаем его номер */
    else if (callsL)
        return tmpFloorL;
    /* Если запрос только на этаже выше - возвращаем его номер */
    else if (callsH)
        return tmpFloorH;
    /* Если нет запросов, возвращаем 0 */
    else
        return 0;

}

/* Ищем в стеке запросов любой запрос от startFloor до endFloor */
bool cElevator::anyRequests(int startFloor, int endFloor, int& calledFloor)
{
    int i = startFloor; 
    bool found = false;
    while (i < endFloor && !found) {
        if (passengerRequests[i]) {
            found = true;
            calledFloor = i + 1;
        }
        i++;
    }
    return found;
}

int cElevator::nearestRequest()
{
    int tmpFloorL = 0; int tmpFloorH = 0;
    /* Ищем запросы на этажах ниже */
    bool callsL = anyRequests(0, floor, tmpFloorL);
    /* Ищем запросы на этажах выше */
    bool callsH = anyRequests(floor, maxFloors, tmpFloorH);

    /* Сравниваем расстояние от запросов до текущего этажа */
    if (callsL && callsH) {
        /* Возвращаем номер близжайшего этажа */
        if (floor - tmpFloorL < tmpFloorH - floor)
            return tmpFloorL;
        else
            return tmpFloorH;
    }
    /* Если запрос только на этаже ниже - возвращаем его номер */
    else if (callsL)
        return tmpFloorL;
    /* Если запрос только на этаже выше - возвращаем его номер */
    else if (callsH)
        return tmpFloorH;
    /* Если нет запросов, возвращаем 0 */
    else
        return 0;
}

/* Выполнение команды */
bool cElevator::command(std::string cmd) {

    /*
    Список команд:
        - Fx - вызов лифта на этаже x (0)
        - Cx - команда подняться на этаж x (1)
        - none - бездействие в течение одной секунды (2)
        - exit - выход из программы (3)
        - <unknown> - неизвестная команда (бездействие) (4)
    */
    int newFloor = 0;
    int cmdNumber = 0;

    /* Извлекаем значение команды */
    parseCommand(cmd, cmdNumber, newFloor);

    /* Алгоритм работы лифта при выполнении команды */

    /* Если команда выхода - возвращаем false */
    if (cmdNumber == 3)
        return false;
    else if (cmdNumber == 0)
        /* Добавляем вызов */
        passengerCalls[newFloor - 1] = true;
    else if (cmdNumber == 1)
        /* Добавляем запрос */
        passengerRequests[newFloor - 1] = true;

    int tmp = 0;

    switch (movementDirection)
    {
        /* Если стоим - смотрим есть ли запросы / вызовы */
    case 0:

        /* Если есть запрос или вызов на этаж - открываем двери */
        if (passengerCalls[floor - 1] || passengerRequests[floor - 1]) {
            printState();
            /* Выпускаем / впускаем пассажира */
            passengerCalls[floor - 1] = false;
            passengerRequests[floor - 1] = false;
            printState();
        }

        /* На текущем этаже запросов нет - смотрим есть ли еще где-то */
        /* Если есть запросы - двигаемся в направлении ближайшего */
        if (anyRequests(0, maxFloors, tmp)) {
            tmp = nearestRequest();
            if (tmp < floor) {
                movementDirection = 1;
                floor--;
                printState();
            }
            else {
                movementDirection = 2;
                floor++;
                printState();
            }
        }
        /* Если нет запросов, но есть вызовы - двигаемся в направлении ближайшего */
        else if (anyCalls(0, maxFloors, tmp)) {
            tmp = nearestCall();
            if (tmp < floor) {
                movementDirection = 1;
                floor--;
                printState();
            }
            else {
                movementDirection = 2;
                floor++;
                printState();
            }
        }
        /* Нет ни запросов, ни вызовов - остаемся на месте */
        else
            printState();
        break;

    /* Двигаемся вниз - смотрим есть ли запросы / вызовы */
    case 1:

        /* Если есть запрос или вызов на этаж - открываем двери */
        if (passengerCalls[floor - 1] || passengerRequests[floor - 1]) {
            /* Останавливаемся */
            movementDirection = 0;
            printState();
            /* Выпускаем / впускаем пассажира */
            passengerCalls[floor - 1] = false;
            passengerRequests[floor - 1] = false;
            printState();
        }

        /* Теперь на текущем этаже запросов и вызовов нет - смотрим есть ли еще где-то */
        /* Если есть запросы - двигаемся в направлении нижнего */
        if (anyRequests(0, maxFloors, tmp)) {
            /* Если запросов снизу нет - останавливаемся */
            if (!anyRequests(0, floor, tmp)) {
                movementDirection = 0;
                printState();
                /* Т.к. есть запросы сверху - начинаем подниматься наверх */
                movementDirection = 2;
                floor++;
            }
            else {
                /* Продолжаем движение вниз */
                floor--;
                printState();
            }
        }
        /* Если нет запросов, но есть вызовы - двигаемся в направлении ближайшего */
        else if (anyCalls(0, maxFloors, tmp)) {
            tmp = nearestCall();
            if (tmp < floor) {
                /* Продолжаем движение вниз */
                floor--;
            }
            else {
                /* Останавливаемся */
                movementDirection = 0;
                printState();
                /* Двигаемся вверх */
                movementDirection = 2;
                floor++;
                printState();
            }
        }
        /* Нет ни запросов, ни вызовов - остаемся на месте */
        else {
            movementDirection = 0;
        }
        break;

    /* Двигаемся вверх - смотрим есть ли запросы / вызовы */
    case 2:

        /* Если есть запрос или вызов на этаж - открываем двери */
        if (passengerCalls[floor - 1] || passengerRequests[floor - 1]) {
            /* Останавливаемся */
            movementDirection = 0;
            printState();
            /* Выпускаем / впускаем пассажира */
            passengerCalls[floor - 1] = false;
            passengerRequests[floor - 1] = false;
            printState();
        }

        /* Теперь на текущем этаже запросов нет - смотрим есть ли еще где-то */
        /* Если есть запросы - двигаемся в направлении верхнего */
        if (anyRequests(0, maxFloors, tmp)) {
            /* Если запросов и вызовов сверху нет - останавливаемся */
            if (!anyRequests(floor, maxFloors, tmp)) {
                /* Смотрим есть ли вызовы сверху */
                if (anyCalls(floor, maxFloors, tmp)) {
                    /* Продолжаем двигаться наверх */
                    movementDirection = 2;
                    floor++;
                    printState();
                }
                else {
                    /* Останавливаемся, если нет ни запросов, не вызовов сверху */
                    movementDirection = 0;
                    printState();
                    /* Запросы вниз есть - начинаем спускаться */
                    movementDirection = 1;
                    floor--;
                    printState();
                }
            }
            else {
                /* Продолжаем движение */
                if (floor < maxFloors) {
                    movementDirection = 2;
                    floor++;
                }
                else {
                    movementDirection = 0;
                }
                printState();
            }
                
        }
        /* Если нет запросов, но есть вызовы - двигаемся в направлении верхнего */
        else if (anyCalls(0, maxFloors, tmp)) {
            if (tmp > floor) {
                /* Продолжаем движение вверх */
                floor++;
                printState();
            }
            else {
                /* Наверху нет ни запросов, ни вызовов, но есть снизу - меняем направление движения */
                /* Останавливаемся */
                movementDirection = 0;
                printState();
                /* Двигаемся вверх */
                movementDirection = 1;
                floor--;
                printState();
            }
        }
        /* Нет ни запросов, ни вызовов - остаемся на месте */
        else {
            movementDirection = 0;
        }
        break;
    }
    return true;

}