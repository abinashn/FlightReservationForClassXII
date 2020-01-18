#ifndef AIRLINE_H
#define AIRLINE_H


class Airline
{
public:
    void displayall();
    void modifyAirline();
    void addAirline();
    void deleteAirline();
    char* getAirlineID();

private:
    char airline_id[3];
    char airline_name[20];
    void setData();
    void modifyData();
    void displayData();

};

#endif // AIRLINE_H
