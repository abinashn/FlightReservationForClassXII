#ifndef BOOKFLIGHT_H
#define BOOKFLIGHT_H
#include "Flight.h"

class BookFlight : public Flight
{
public:
    bool addBooking(char* fromairport,char* toairport, char* travel_date);
    void displayBooking(int count);
    void cancelBooking(char* id);
    void modiyBooking(char* id,char* travel_date, char seatingclass);
    void retrieveBookingbyID(char* id);
    void retrieveBookingbyCustomerID(int customerID);
    void retrieveBookingbyEmailID();
    BookFlight* getBookingbyID(char* id);
    void displayBookings();
    void displayBooking();
    char* getAirlineID();
    char* getTravelDate();
    int getConnectionID();
    void formatDisplayBookings();

private:

    char booking_id[6];
    char airline_id[3];
    int connection_id;
    int customer_id;
    char traveldate[11];
    char bookingdate[11];
    char travelclass;

    void calculateBookingID(char* id);
    void saveFlight();

};

#endif // BOOKFLIGHT_H
