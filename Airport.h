#ifndef AIRPORT_H
#define AIRPORT_H

class Airport
{
public:
    void setData(); // get student data from user
    void displayData(); // display data
    char* getAirportID();
    void modifyData();
    void displayall();
    void addAirport();
    void modifyAirport();
    void deleteAirport();


private:
    char airport_id[4];
    char airport_name[30];
};

#endif // AIRPORT_H
