#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>

#include "Airline.h"
#include "Airport.h"
#include "Plane.h"
#include "FlightSchedule.h"
#include "Flight.h"
#include "Utility.h"
#include "Customer.h"
#include "BookFlight.h"

using namespace std;

int processAirline();
int processAirport();
int processAircraftType();
int processFlightSchedule();
int processFlight();
int processCustomer();
int processBooking();
template <class T>
void writeFile(T t1, string filename);


int main()
{
    char ch_menu;
    string dummy;

Main_Menu:
    cout << "Main Menu"<<"\n";
    cout <<" 1. - Airline Menu"<<"\n"
         <<" 2. - Airport Menu"<<"\n"
         <<" 3. - Aircraft Menu"<<"\n"
         <<" 4. - Flight Schedule Menu"<<"\n"
         <<" 5. - Flight Details Menu"<<"\n"
         <<" 6. - Customer Details Menu"<<"\n"
         <<" 7. - Flight Booking Menu"<<"\n"
         <<" X. - Exit"<<"\n"
         <<" C. - Clear Screen"<<"\n";

    cout << "Enter your choice : ";
    cin >> ch_menu;
    getline(cin,dummy);
    ch_menu = toupper(ch_menu);

    switch(ch_menu)
        {
        case 'C':
            system("cls");
            break;
        case '1' :
            processAirline();
            break;
        case '2' :
            processAirport();
            break;
        case '3' :
            processAircraftType();
            break;
        case '4' :
            processFlightSchedule();
            break;
        case '5' :
            processFlight();
            break;
        case '6' :
            processCustomer();
            break;
        case '7' :
            processBooking();
            break;
        case 'X':
            return 0;
            break;

        default:
            cout << "Invalid Choice"<<"\n";

        }
    goto Main_Menu;

    return 0;
}

template <class T>
void writeFile(T t1, string filename)
{
    fstream file;
    // open file for writing
    file.open(filename, ios :: out | ios::binary | ios::app);

    t1.setData();
    file.write((char *)&t1,sizeof(t1));

    file.close();
}

int processAirline()
{
    Airline airline;
    string dummy;
    char ch_airline_menu;

    airline.displayall();

Airline_Menu:
    cout << "\nAirline Menu"<<"\n";
    cout <<" 1. - Add an Airline"<<"\n"
         <<" 2. - Modify an Airline"<<"\n"
         <<" 3. - Delete an Airline"<<"\n"
         <<" 0. - Return to Main Menu"<<"\n";

    cout << "Enter your choice : ";
    cin >> ch_airline_menu;
    getline(cin,dummy);
    ch_airline_menu = toupper(ch_airline_menu);

    switch(ch_airline_menu)
        {
        case '1':
            airline.addAirline();
            break;

        case '2':  //Modify Airline
            airline.modifyAirline();
            break;

        case '3' : //Delete
            airline.deleteAirline();
            break;

        case '0':
            return 0;
            break;

        default:
            cout << "Invalid Choice"<<"\n";
        }
    goto Airline_Menu;

}

int processAirport()
{
    Airport airport;
    string dummy;
    char ch_airport_menu;

    airport.displayall();

Airport_Menu:
    cout << "\nAirport Menu"<<"\n";
    cout <<" 1. - Add an Airport"<<"\n"
         <<" 2. - Modify an Airport"<<"\n"
         <<" 3. - Delete an Airport"<<"\n"
         <<" 0. - Return to Main Menu"<<"\n";

    cout << "Enter your choice : ";
    cin >> ch_airport_menu;
    getline(cin,dummy);
    ch_airport_menu = toupper(ch_airport_menu);

    switch(ch_airport_menu)
        {
        case '1':
            airport.addAirport();
            break;

        case '2':  //Modify Airport
            airport.modifyAirport();
            break;

        case '3' : //Delete
            airport.deleteAirport();
            break;

        case '0':
            return 0;
            break;

        default:
            cout << "Invalid Choice"<<"\n";
        }
    goto Airport_Menu;
}

int processAircraftType()
{
    Plane plane;
    string dummy;
    char ch_aircraft_menu;
    cout << "\nList of available Aircraft types are : "<<endl;
    plane.formatdisplayall();
    plane.displayall();

Aircraft_Menu:
    cout << "\nAircraft Menu"<<"\n";
    cout <<" 1. - Add an Aircraft Type"<<"\n"
         <<" 2. - Display an Aircraft Type"<<"\n"
         <<" 0. - Return to Main Menu"<<"\n";

    cout << "Enter your choice : ";
    cin >> ch_aircraft_menu;
    getline(cin,dummy);
    ch_aircraft_menu = toupper(ch_aircraft_menu);

    switch(ch_aircraft_menu)
        {
        case '1':
            plane.setdata();
            cout << "\nUpdated list of available Aircraft Types are : "<<endl;
            plane.formatdisplayall();
            plane.displayall();
            break;

        case '2':
            Plane *p1;
            char aircrafttype[5];
            cout << "Enter Aircraft type (4 characters staring with a letter): ";
            gets(aircrafttype);
            p1 = plane.getaircraftdata(aircrafttype);
            if (p1!=NULL)
                {
                    p1->formatdisplayall();
                    cout.setf(ios::left);
                    cout << setw(16)<< p1->PLANETYPE << setw(20) << p1->SEATSMAX << setw(20) <<
                         p1->SEATSMAX_B << endl;
                }
            else
                cout << "No aircraft of type " << aircrafttype << " found!!!"<<endl;
            break;

        case '0':
            return 0;
            break;

        default:
            cout << "Invalid Choice"<<"\n";
        }
    goto Aircraft_Menu;

}

int processFlightSchedule()
{
    FlightSchedule fs;
    string dummy;
    char ch_fltsch_menu;

FlightSchedule_Menu:
    cout << "\nFlight Schedule Menu"<<"\n";
    cout <<" 1. - Display Schedules"<<"\n"
         <<" 2. - Add a schedule"<<"\n"
         <<" 3. - Find schedule between cities"<<"\n"
         <<" 0. - Return to Main Menu"<<"\n";

    cout << "Enter your choice : ";
    cin >> ch_fltsch_menu;
    getline(cin,dummy);
    ch_fltsch_menu = toupper(ch_fltsch_menu);

    switch(ch_fltsch_menu)
        {
        case '1':
            fs.formatDisplaySchedule();
            fs.getAllSchedules();
            break;

        case '2':
            fs.addschedule();
            fs.formatDisplaySchedule();
            fs.getAllSchedules();
            break;

        case '3':
            char fromairport_id[4];
            char toairport_id[4];
            cout << "Enter From airport: ";
            gets(fromairport_id);
            for (int i =0; i<3; i++)
                fromairport_id[i] = toupper(fromairport_id[i]);
            cout << "Enter To airport: ";
            gets(toairport_id);
            for (int i =0; i<3; i++)
                toairport_id[i] = toupper(toairport_id[i]);
            fs.getAllSchedules(fromairport_id,toairport_id);
            break;

        case '0':
            return 0;
            break;

        default:
            cout << "Invalid Choice"<<"\n";
        }
    goto FlightSchedule_Menu;

}
int processFlight()
{
    Flight flight;
    Utility util;
    string dummy;
    char ch_flt_menu;
    char traveldate[11];
    char isEntryValid = 'N';

Flight_Menu:
    cout << "\nFlight Detail Menu"<<"\n";
    cout <<" 1. - Display All Flights "<<"\n"
         <<" 2. - Add a new Flight"<<"\n"
         <<" 3. - Get all flights for a given day"<<"\n"
         <<" 4. - Find flights between cities"<<"\n"
         <<" 0. - Return to Main Menu"<<"\n";

    cout << "Enter your choice : ";
    cin >> ch_flt_menu;
    getline(cin,dummy);
    ch_flt_menu = toupper(ch_flt_menu);

    switch(ch_flt_menu)
        {
        case '1':
            flight.formatDisplayFlight();
            flight.getAllFlights();
            break;

        case '2':
            flight.addFlight();
            break;

        case '3':
            while(isEntryValid == 'N')
                {
                    cout << "Enter Travel Date (in dd-mm-yyyy format) : ";
                    gets(traveldate);
                    if (util.isDateValid(traveldate))
                        isEntryValid = 'Y';
                    else
                        cout << traveldate <<" is not a valid date\n";
                }
            flight.formatDisplayFlight();
            flight.getAllFlights(traveldate);
            isEntryValid = 'N';
            break;

        case '4':
            char fromairport_id[4];
            char toairport_id[4];
            cout << "Enter From airport: ";
            gets(fromairport_id);
            for (int i =0; i<3; i++)
                fromairport_id[i] = toupper(fromairport_id[i]);
            cout << "Enter To airport: ";
            gets(toairport_id);
            for (int i =0; i<3; i++)
                toairport_id[i] = toupper(toairport_id[i]);
            flight.getAllFlights(fromairport_id,toairport_id);
            break;

        case '0':
            return 0;
            break;

        default:
            cout << "Invalid Choice"<<"\n";
        }
    goto Flight_Menu;
}
int processCustomer()
{
    Customer customer, *cust;
    int customer_id;
    string dummy;
    char ch_customer_menu;

    customer.formatDisplayCustomer();
    customer.displayAllCustomers();

Customer_Menu:
    cout << "\nCustomer Menu"<<"\n";
    cout <<" 1. - Add a Customer"<<"\n"
         <<" 2. - Modify a Customer"<<"\n"
         <<" 3. - Delete a Customer"<<"\n"
         <<" 4. - Display a Customer"<<"\n"
         <<" 0. - Return to Main Menu"<<"\n";

    cout << "Enter your choice : ";
    cin >> ch_customer_menu;
    getline(cin,dummy);
    ch_customer_menu = toupper(ch_customer_menu);

    switch(ch_customer_menu)
        {
        case '1':
            customer.addCustomer();
            customer.displayAllCustomers();
            break;

        case '2':
            customer.modifyCustomer();
            break;

        case '3' :
            customer.deleteCustomer();
            break;

        case '4' :
            cout << "Enter Customer ID : ";
            cin >> customer_id;
            cin.ignore();
            cust = customer.getCustomerbyID(customer_id);
            if (cust != NULL)
                {
                    cust->formatDisplayCustomer();
                    cust->displayCustomer();
                }
            else
                cout << "Customer ID " << customer_id << " does not exist!!!"<<endl;
            break;

        case '0':
            return 0;
            break;

        default:
            cout << "Invalid Choice"<<"\n";
        }
    goto Customer_Menu;

}

int processBooking()
{
    BookFlight bookflight; ;
    Utility util;
    Flight flight;
    string dummy;
    char fromairport_id[4];
    char toairport_id[4];
    char traveldate[11] ;
    char bookticket;
    char validDate;
    bool flightavailable = false;
    char booking_id[6];
    char ch_flightbooking_menu;

FlightBooking_Menu:
    cout << "\nFlight Booking Menu"<<"\n";
    cout <<" 1. - Retrieve a Booking"<<"\n"
         <<" 2. - Book a Flight"<<"\n"
         <<" 3. - Modify a Booking"<<"\n"
         <<" 4. - Cancel a Booking"<<"\n"
         <<" 5. - Display all Bookings"<<"\n"
         <<" 6. - Display latest Bookings"<<"\n"
         <<" 0. - Return to Main Menu"<<"\n";

    cout << "Enter your choice : ";
    cin >> ch_flightbooking_menu;
    getline(cin,dummy);
    ch_flightbooking_menu = toupper(ch_flightbooking_menu);

    switch(ch_flightbooking_menu)
        {
        case '1':
            char ch_retrieve_booking_menu;
            cout <<" A. - Retrieve Booking by Booking ID"<<"\n"
                 <<" B. - Retrieve Booking by Customer ID"<<"\n"
                 <<" C. - Retrieve Booking by Email-ID"<<"\n";

            cout << "Enter your choice : ";
            cin >> ch_retrieve_booking_menu;
            getline(cin,dummy);
            ch_retrieve_booking_menu = toupper(ch_retrieve_booking_menu);
            switch(ch_retrieve_booking_menu)
                {
                case 'A':
                    cout << "Enter Booking id : ";
                    gets(booking_id);
                    bookflight.retrieveBookingbyID(booking_id);
                    break;

                case 'B':
                    int customerID;
                    cout << "Enter Customer ID :";
                    cin >> customerID;
                    bookflight.retrieveBookingbyCustomerID(customerID);
                    break;

                case 'C':
                    bookflight.retrieveBookingbyEmailID();
                    break;

                default:
                    cout << "Invalid Choice"<<"\n";
                }

            break;
        case '2':
            validDate = 'n';
            cout << "Enter From airport: ";
            gets(fromairport_id);
            for (int i =0; i<3; i++)
                fromairport_id[i] = toupper(fromairport_id[i]);
            cout << "Enter To airport: ";
            gets(toairport_id);
            for (int i =0; i<3; i++)
                toairport_id[i] = toupper(toairport_id[i]);
            while (validDate == 'n')
                {
                    cout << "Enter Travel Date (in dd-mm-yyyy format) : ";
                    gets(traveldate);
                    if (util.isDateValid(traveldate))
                        {
                            validDate = 'Y';
                            flightavailable = flight.getAllFlights(traveldate,fromairport_id,toairport_id);
                        }
                    else
                        cout << traveldate << " is an invalid Date!!!" << endl;
                }
            if (flightavailable)
                {
                    cout << "Do you want to book a flight ticket (y/n)";
                    cin >> bookticket;
                    while (bookticket == 'y' || bookticket == 'Y')
                        {
                            system("cls");
                            flight.getAllFlights(traveldate,fromairport_id,toairport_id);
                            bool ticketBooked = bookflight.addBooking(fromairport_id,toairport_id,traveldate);
                            if (ticketBooked)
                                bookflight.displayBooking(1);
                            flight.getAllFlights(traveldate,fromairport_id,toairport_id);
                            cout << "Book another flight ticket (y/n)";
                            cin >> bookticket;

                        }
                }
            break;

        case '3':
            BookFlight *bookflight1;
            cout << "Enter Booking id : ";
            gets(booking_id);
            bookflight1 = bookflight.getBookingbyID(booking_id);
            if (bookflight1 != NULL)
                {
                    bookflight1->displayBooking();
                    char* existingTravelDate = bookflight1->getTravelDate();
                    char oldTraveldate[11],airlineID[3];
                    strcpy(oldTraveldate,existingTravelDate);
                    strcpy(airlineID,bookflight1->getAirlineID());
                    int connectionID = bookflight1->getConnectionID();
                    flight.getFlightData(bookflight1->getAirlineID(),bookflight1->getConnectionID(),existingTravelDate);
                    cout << "Enter New Travel Date (in dd-mm-yyyy format) : ";
                    gets(traveldate);
                    flightavailable = flight.getFlightData(bookflight1->getAirlineID(),bookflight1->getConnectionID(),traveldate);
                    if(flightavailable)
                        {
                            char travelclass;
                            cout << "Enter Travel Class (B for Business Class or E for Economy Class): ";
                            cin >> travelclass;
                            travelclass = toupper(travelclass);
                            bookflight.modiyBooking(booking_id,traveldate,travelclass);
                            flight.getFlightData(airlineID,connectionID,oldTraveldate);
                            flight.getFlightData(airlineID,connectionID,traveldate);
                        }
                }

            break;

        case '4' :
            cout << "Enter Booking id : ";
            gets(booking_id);
            bookflight1 = bookflight.getBookingbyID(booking_id);
            if (bookflight1 != NULL)
                {
                    char* existingTravelDate = bookflight1->getTravelDate();
                    char oldTraveldate[11],airlineID[3];
                    strcpy(oldTraveldate,existingTravelDate);
                    strcpy(airlineID,bookflight1->getAirlineID());
                    int connectionID = bookflight1->getConnectionID();
                    flight.getFlightData(bookflight1->getAirlineID(),bookflight1->getConnectionID(),existingTravelDate);
                    bookflight.cancelBooking(booking_id);
                    flight.getFlightData(airlineID,connectionID,oldTraveldate);

                }
            break;

        case '5':
            bookflight.formatDisplayBookings();
            bookflight.displayBookings();
            break;

        case '6':
            int bookingcount;
            cout << "No of bookings to be displayed? ";
            cin >> bookingcount;
            bookflight.formatDisplayBookings();
            bookflight.displayBooking(bookingcount);
            break;

        case '0':
            return 0;
            break;

        default:
            cout << "Invalid Choice"<<"\n";
        }
    goto FlightBooking_Menu;

}

