#include "BookFlight.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "Utility.h"
#include "Customer.h"
#include "Flight.h"
#include "FlightSchedule.h"
#include <iomanip>


using namespace std;
bool printOutput = true;

string strconnectionID(int connection_id);
string getNextBookingID(string ID);
void formatOutput();

bool BookFlight::addBooking(char* fromairport,char* toairport, char* travel_date)
{
    Utility util;
    string dummy;
    char isEntryValid = 'N';

    calculateBookingID(booking_id);
    cin.ignore();
    while(isEntryValid == 'N')
        {
            cout << "Enter Airline ID : ";
            gets(airline_id);
            for (int i =0; i<2; i++)
                airline_id[i] = toupper(airline_id[i]);
            int result = util.checkAirlineValidity(airline_id);
            if (result > -1 )
                isEntryValid = 'Y';
            else
                cout << "Airline ID not found"<<endl;

        }
    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Enter connection ID : ";
            cin >> connection_id;
            if(util.checkConnectionValidity( airline_id + util.str2ID(connection_id)))
                isEntryValid = 'Y';
            else
                cout << "Airline " << airline_id << " does not have a connection " << connection_id<<endl;
        }
    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Enter Customer ID : ";
            cin >> customer_id;
            cin.ignore(); // To ignore the new line character from the stream for the next gets() input.
            Customer* c = (new Customer)->getCustomerbyID(customer_id);
            if (c!=NULL)
                isEntryValid = 'Y';
            else
                cout << "Customer does not exist"<<endl;
        }

    strcpy(traveldate,travel_date);

    cout << "Enter Travel Class (B for Business Class or E for Economy Class): ";
    cin >> travelclass;


    string sbookingdate = util.getCurrentDate();
    for (int i = 0; i<10; i++)
        bookingdate[i] = sbookingdate[i];
    bookingdate[10] = '\0';

    //Allocate Seat
    bool isSeatBooked = bookSeat(airline_id,connection_id,traveldate,fromairport,toairport,travelclass);

    if(isSeatBooked)
        {
            fstream fout("Bookings.dat", ios::out | ios::binary | ios::app);
            fout.write((char *)this, sizeof(BookFlight));
            fout.close();
            cout << "Booking created with id : " << booking_id <<" ."<<endl;
            return true;
        }
        else
            return false;

}

void BookFlight::formatDisplayBookings()
{
    cout << "Flight Booking Information : " << endl;
    cout.setf(ios::left);
    cout << setw(12)<<"Booking ID"<<setw(12)<<"Airline ID"<<setw(10)<<"Conn. ID"
         <<setw(13)<<"Customer ID"<<setw(14)<<"Travel Date"<<setw(14)<<"Booking Date"
         <<setw(12)<<"Travel Class"<<endl;
}

void BookFlight::displayBooking()
{
    cout.setf(ios::left);
    cout << setw(12)<< booking_id << setw(12) << airline_id << setw(10) << connection_id <<setw(13) <<
         customer_id <<setw(14) << traveldate <<setw(19)  << bookingdate <<setw(12)<< travelclass << endl;
}

void BookFlight::cancelBooking(char* id)
{
    bool bookingExist = false, isSeatCancelled = false;

    fstream fin("Bookings.dat", ios::in | ios::binary);
    fstream fout("TempBookings.dat", ios::out | ios::binary |ios::app);
    while(fin.read((char *)this,sizeof(BookFlight)))
        {
            if (strcmp(this->booking_id,id) == 0)
                {
                    bookingExist = true;
                    isSeatCancelled = cancelSeat(
                                          this->airline_id,this->connection_id,
                                          this->traveldate,this->travelclass);
                }
            else
                fout.write((char *)this, sizeof(BookFlight));
        }

    if(!bookingExist)
        cout << "Booking " << id << " does not exist!!!" <<endl;

    fin.close();
    fout.close();

    if (isSeatCancelled)
        {
            remove("Bookings.dat");
            rename("TempBookings.dat", "Bookings.dat");
            cout << "Booking " << id << " canceled successfully."<<endl;
        }
    else
        remove("TempBookings.dat");

}

void BookFlight::modiyBooking(char* id,char* travel_date, char seatingclass)
{
    Utility util;
    bool bookingExist = false, isBookingModified = false;

    fstream fio("Bookings.dat", ios::in |ios::out| ios::binary);
    while(fio.read((char *)this, sizeof(BookFlight)))
        {
            int pos = fio.tellg();
            if ( strcmp(this->booking_id,id) == 0 )
                {
                    bookingExist = true;
                    if(getFlight(this->airline_id,this->connection_id,travel_date))
                        {
                            isBookingModified = modifySeat(this->airline_id,this->connection_id,this->traveldate,travel_date,this->travelclass,seatingclass);
                            if(isBookingModified)
                                {
                                    strcpy(this->traveldate,travel_date);
                                    this->travelclass = seatingclass;
                                    string sbookingdate = util.getCurrentDate();
                                    for (int i = 0; i<10; i++)
                                        this->bookingdate[i] = sbookingdate[i];
                                    this->bookingdate[10] = '\0';
                                    fio.seekg(pos - sizeof(BookFlight)); // File pointer is moved to record to be modified, in this case backward
                                    fio.write((char *)this, sizeof(BookFlight));
                                }
                            else
                                cout << "Booking could not be modified!!!"<<endl;
                        }
                    else
                        cout << "Flight not available on " << travel_date << ", booking can not be modified!!!"<<endl;
                    break;
                }
        }
    fio.close();
    if(!bookingExist)
        cout << "Booking " << id << " does not exist!!!" <<endl;
    if (isBookingModified)
        cout << "Booking " << id << " updated successfully." <<endl;

}
void BookFlight::retrieveBookingbyID(char* id)
{
    bool bookingExist = false;
    BookFlight flightbooking;

    fstream fin("Bookings.dat", ios::in | ios::binary);
    while(fin.read((char *)&flightbooking,sizeof(BookFlight)))
        {
            //strcmp is needed to compare 2 char*
            if (strcmp(flightbooking.booking_id,id) == 0)
                {
                    bookingExist = true;
                    break;
                }
        }
    fin.close();
    if(!bookingExist)
        {
            cout << "Booking " << id << " does not exist!!!" <<endl;
        }
    else
        {
            FlightSchedule flightSchedule;
            FlightSchedule *fs=  flightSchedule.getAirportDetail
                                 (flightbooking.airline_id,flightbooking.connection_id);

            if (printOutput)
                {
                    formatOutput();
                    printOutput = false;
                }
            cout <<setw(12) <<flightbooking.booking_id<<setw(12)<<flightbooking.airline_id<<setw(10)<<flightbooking.connection_id
                 << setw(14) << fs->getFromAirport()<< setw(12) << fs->getToAirport() << setw(12) << fs->getDeptTime()
                 << setw(11) << fs->getArrTime()
                 << setw(13)<<flightbooking.customer_id
                 <<setw(14)<<flightbooking.traveldate <<setw(14)<<flightbooking.bookingdate << setw(12)
                 <<flightbooking.travelclass<<endl;

        }
}
void BookFlight::retrieveBookingbyCustomerID(int customerID)
{

    bool bookingExistforCustomerID = false;

    printOutput = true;


    Customer customer;
    Customer *c = customer.getCustomerbyID(customerID);
    if (c != NULL)
        {
            fstream fin("Bookings.dat", ios::in | ios::binary);
            while(fin.read((char *)this,sizeof(BookFlight)))
                {
                    //strcmp is needed to compare 2 char*
                    if (this->customer_id == c->getCustomerID())
                        {
                            bookingExistforCustomerID = true;
                            retrieveBookingbyID(this->booking_id);
                        }
                }
            fin.close();
            if(!bookingExistforCustomerID)
                cout << "No Booking found for Customer ID" << customerID << " !!!" <<endl;

        }
    else
        cout << "Customer ID " << customerID << " does not exist!!!"<<endl;


}

void BookFlight::retrieveBookingbyEmailID()
{
    char email[50];
    char isEntryValid;
    string dummy;
    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Email id : ";
            cin.getline(email,50);
            for (int i =0; i<49; i++)
                email[i] = tolower(email[i]);
            if (Utility::IsEmailAddressValid(email))
                isEntryValid = 'Y';
            else
                cout << email <<" is not a valid Email address\n"<<endl;
            Customer cust;
            bool customerexistbyEmailID = cust.getCustomerbyEmail(email,cust);
            if (customerexistbyEmailID)
                {
                    retrieveBookingbyCustomerID(cust.getCustomerID());
                }
            else
                cout << "Customer with Email ID " << email << " does not exist!!!"<<endl;
        }
}


BookFlight* BookFlight::getBookingbyID(char* id)
{
    bool bookingExist = false;
    fstream fin("Bookings.dat", ios::in | ios::binary);
    while(fin.read((char *)this,sizeof(BookFlight)))
        {
            //strcmp is needed to compare 2 char*
            if (strcmp(this->booking_id,id) == 0)
                {
                    bookingExist = true;
                    break;
                }
        }
    fin.close();
    if(!bookingExist)
        {
            cout << "Booking " << id << " does not exist!!!" <<endl;
            return NULL;
        }
    else
        return this;

}

void BookFlight::displayBookings()
{
    fstream fin("Bookings.dat", ios::in | ios::binary);
    while(fin.read((char *)this,sizeof(BookFlight)))
        this->displayBooking();
    fin.close();
}

void BookFlight::saveFlight()
{

}
void BookFlight::calculateBookingID(char* id)
{
    fstream fin("Bookings.dat", ios::in | ios::binary);
    if (fin.is_open())
        {
            int sizeofobj = sizeof(BookFlight);
            fin.seekg(-sizeofobj,ios_base::end); //Goto the last record
            fin.read((char *)this,sizeof(BookFlight));
            string bookingid = this->booking_id;
            fin.close();
            string bookingid_n = getNextBookingID(bookingid);
            strcpy(id,&bookingid_n[0]);
        }
    else
        {
            strcpy(id,"B1001");
        }

}

void BookFlight::displayBooking(int count)
{
    fstream fin("Bookings.dat", ios::in | ios::binary);
    fin.seekg(0, ios::end);
    int file_size = fin.tellg();
    fin.close();
    int sizeofobj = sizeof(BookFlight) * count;
    if (sizeofobj > file_size)
        displayBookings();
    else
        {
            fin.open("Bookings.dat", ios::in | ios::binary);
            if (fin.is_open())
                {

                    fin.seekg(-sizeofobj,ios_base::end); //Goto the last record
                    fin.read((char *)this,sizeof(BookFlight));
                    this->displayBooking();
                    while(fin.read((char *)this,sizeof(BookFlight)))
                        this->displayBooking();
                    fin.close();
                }
        }
}


string getNextBookingID(string ID)
{
    string bookingidint = ID.substr(1,4);
    stringstream ssint;
    ssint << bookingidint;
    int nextid = 0;
    ssint >> nextid;
    stringstream ssext;
    ssext << 'B' << ++nextid;
    string bookingid;
    ssext >> bookingid;
    return bookingid;
}

char* BookFlight::getAirlineID()
{
    return airline_id;
}

int BookFlight::getConnectionID()
{
    return connection_id;
}

char* BookFlight::getTravelDate()
{
    return traveldate;
}

void formatOutput()
{
    cout << "\nBooking Details are as follows:" << endl;
    cout.setf(ios::left);
    cout <<setw(12)<<"Booking ID"<<setw(12)<<"Airline ID"<<setw(10)<<"Conn. ID"<< setw(14) << "From Airport"
         << setw(12) << "To Airport" << setw(12) << "Dept Time"
         << setw(11) << "Arr Time" << setw(13)<<"Customer ID"<<setw(14)<<"Travel Date"
         <<setw(14)<<"Booking Date" << setw(12) <<"Travel Class"<<endl;

}
