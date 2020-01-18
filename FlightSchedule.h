#ifndef FLIGHTSCHEDULE_H
#define FLIGHTSCHEDULE_H

#include <string>
#include <vector>

class FlightSchedule
{
public:
    void addschedule();
    void displayschedule();
    void formatDisplaySchedule();
    void getAllSchedules();
    std::string getKey();
    std::vector<FlightSchedule> getAllSchedules(std::string,std::string);
    bool getAllSchedules(char* airlineid,int connectionid,char* fromairport,char* toairport);
    void getAllSchedules(char* fromairport,char* toairport);
    char* getFromAirport();
    char* getToAirport();
    char* getDeptTime();
    char* getArrTime();
    char* getAirlineID();
    int getConnectionID();
    FlightSchedule* getAirportDetail(char* airlineid,int connectionid);

private:
    char airline_id[3];
    int connection_id;
    char fromairport_id[4];
    char toairport_id[4];
    char depttime[6];
    char arrtime[6];
    float distance;

    void saveSchedule();
};

#endif // FLIGHTSCHEDULE_H
