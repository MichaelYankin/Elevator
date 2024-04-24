#include <iostream>

using std::cout;
using std::cin;

class cElevator
{

private:

    /* направление движения: 0 - без движения, 1 - движение вниз, 2 - движение вверх */
    int movementDirection;
    /* этажи, на которых нужно высадить пассажира */
    bool* passengerRequests;
    /* этажи, на которых нужно посадить пассажира */
    bool* passengerCalls;
    /* текущий этаж */
    int floor;
    /* макс. этажей */
    int maxFloors;

    /* Вывод состояния лифта */
    void printState();

    /* Вызовы на этажи */
    /* Поиск вызовов лифтра */
    bool anyCalls(int startFloor, int endFloor, int& calledFloor);
    int nearestCall();

    /* Запросы пассажиров на движение на этажи */    
    /* Поиск указаний пассажиров */
    bool anyRequests(int startFloor, int endFloor, int& calledFloor);
    int nearestRequest();

public:

    cElevator();
    cElevator(int floor, int max_floors);
    ~cElevator();
    bool command(std::string cmd);
    
};