#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

class Flight
{
public:
    void addFlight();
    void displayFlight();
    std::string getKey();
    void getAllFlights();
    void getAllFlights(char* fldate);
    bool getAllFlights(char* fldate,char* fromairport,char* toairport);
    void getAllFlights(char* fromairport,char* toairport);
    void displayFlightTruncated();
    void formatDisplayFlight();
    bool getFlightData(char* airlineid,int connectionid,char* fldate);

protected:
    bool getFlight(char* airlineid,int connectionid,char* fldate);
    bool bookSeat(char* airlineid,int connectionid,char* fldate,char* fromairport,char* toairport,char seattype);
    bool cancelSeat(char* airlineid,int connectionid,char* fldate,char seattype);
    bool modifySeat(char* airlineid,int connectionid,char* existingtraveldate,char* revisedtraveldate,char existingseattype, char revisedseattype);

private:
    char airline_id[3];
    int connection_id;
    char fltdate[11];
    char PLANETYPE[5];
    float price;
    int SEATSMAX; //Maximum capacity in economy class
    int SEATSOCC; //Occupied seats in economy class
    int SEATSMAX_B; // Maximum capacity in business class
    int SEATSOCC_B; // Occupied seats in business class
    double PAYMENTSUM; // Total of current bookings

    void saveFlight();
    bool bookSeat(char* airlineid,int connectionid,char* fldate,char seattype);
    bool bookSeat(char* airlineid,int connectionid,char* fldate,char seattype,char simulateFlag);
    bool getFlightData(char* airlineid,int connectionid);

};

#endif // FLIGHT_H
