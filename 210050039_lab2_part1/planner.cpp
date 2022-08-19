#include <iostream>
#include <fstream>
#include "planner.h"
using namespace std;

int main()
{
    Planner plan;
    ifstream sample("sample-planner.txt");
    string command;
    while (sample >> command)
    {
        if (command == "ADD")
        {
            Journey j;
            sample >> j.station_one >> j.start_time >> j.station_two >> j.finish_time;
            plan.add(j);
        }
        else if (command == "QUERY_STATION")
        {
            string station_one;
            float start_time;
            sample >> station_one >> start_time;
            plan.query_station(station_one, start_time);
        }
        else if (command == "QUERY_JOURNEY")
        {
            string station_one, station_two;
            float start_time;
            sample >> station_one >> start_time >> station_two;
            plan.query_journey(station_one, start_time, station_two);
        }
        else if (command == "EXIT")
            return 0;
    }
}
