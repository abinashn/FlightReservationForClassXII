#include <iostream>
#include "Flight.h"
#include "Utility.h"
#include "Plane.h"
#include "FlightSchedule.h"
#include <sstream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

void Flight::displayFlight()
{
    cout.setf(ios::left);
    cout << setw(12)<< airline_id << setw(10) << connection_id << setw(13) << fltdate << setw(15) << PLANETYPE
         << setw(8) << price << setw(10) << SEATSMAX << setw(10) << SEATSOCC << setw(10) << SEATSMAX_B
         << setw(10) << SEATSOCC_B << endl;
}

void Flight::formatDisplayFlight()
{
    cout << "Flight details are :" << endl;
    cout.setf(ios::left);
    cout << setw(12)<<"Airline ID"<<setw(10)<<"Conn. ID"<<setw(13)<<"Flight Date"<< setw(15)<<"Aircraft Type"
         <<setw(8)<<"Price"<<setw(10)<<"Max Econ"<<setw(10)<<"Occ Econ"<<
         setw(10)<<"Max Busi"<<setw(10)<<"Occ Busi"<<endl;
}

void formatDisplayFlightTruncated()
{
    cout.setf(ios::left);
    cout << setw(12) << "Airline ID" << setw(10) << "Conn. ID" << setw(13) << "Flight Date"
         << setw(12) << "Avail Econ" << setw(12) << "Avail Busi" << endl;

}

void Flight::displayFlightTruncated()
{
    cout.setf(ios::left);
    cout << setw(12) << airline_id << setw(10) << connection_id << setw(13) << fltdate
         << setw(12) << SEATSMAX - SEATSOCC << setw(12) << SEATSMAX_B - SEATSOCC_B << endl;

}

void Flight::addFlight()
{
    Utility util;
    string dummy;
    char isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Enter Airline ID : ";
            cin.getline(airline_id,3);
            for (int i =0; i<2; i++)
                airline_id[i] = toupper(airline_id[i]);
            cin.clear(); // Flush the buffer
            cin.sync();
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
            getline(cin,dummy);
            stringstream ss_connection_id;
            string s_connection_id;
            ss_connection_id << connection_id;
            ss_connection_id >> s_connection_id;
            if(util.checkConnectionValidity( airline_id + s_connection_id))
                isEntryValid = 'Y';
            else
                cout << "Airline " << airline_id << " does not have a connection " << connection_id<<endl;
        }
    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Enter Flight Date (in dd-mm-yyyy format) : ";
            cin.getline(fltdate,11);
            cin.clear(); // Flush the buffer
            cin.sync();
            if (util.isDateValid(fltdate))
                isEntryValid = 'Y';
            else
                cout << fltdate <<" is not a valid date\n";
        }
    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Aircraft Type : ";
            cin.getline(PLANETYPE,5);
            for (int i =0; i<4; i++)
                PLANETYPE[i] = toupper(PLANETYPE[i]);
            cin.clear(); // Flush the buffer
            cin.sync();
            Plane plane, *aircrafttype;
            aircrafttype = plane.getaircraftdata(PLANETYPE);
            if (aircrafttype!=NULL)
                {
                    isEntryValid = 'Y';
                    SEATSMAX = aircrafttype->SEATSMAX;
                    SEATSMAX_B = aircrafttype->SEATSMAX_B;
                    SEATSOCC = 0;
                    SEATSOCC_B = 0;
                }
            else
                cout << "Aircraft Type : " << PLANETYPE <<" does not exist." <<endl;

        }
    cout << "Enter Price : ";
    cin >> price;
    cin.ignore();
    PAYMENTSUM = (SEATSOCC + SEATSOCC_B) * price;
    saveFlight();

}

//For Flight key is combination of Airline ID + Connection ID + Flight Date
string Flight::getKey()
{
    stringstream ss_connection_id;
    string s_connection_id;
    ss_connection_id << connection_id;
    ss_connection_id >> s_connection_id;
    return airline_id + s_connection_id + fltdate;

}

void Flight::saveFlight()
{
    Flight flight;
    fstream fin("Flights.dat", ios::in | ios::binary);
    fstream fout("TempFlights.dat", ios::out | ios::binary |ios::app);

    char lastRecord='y',duplicateRecord = 'n';;

    string n_id = this->getKey();

    while(fin.read((char *)&flight, sizeof(flight)))
        {
            string f_id = flight.getKey();
            if ( n_id == f_id)
                {
                    duplicateRecord = 'y';
                    break;
                }
            else if(n_id < f_id)
                {
                    fout.write((char *)this, sizeof(Flight));
                    lastRecord = 'n';
                    break;
                }
            else
                {
                    fout.write((char *)&flight, sizeof(flight));
                }

        }
    if (duplicateRecord == 'y')
        cout << "\nDuplicate record found. Entry not made!!!";
    else if(lastRecord == 'y'&& duplicateRecord != 'y')
        fout.write((char *)this, sizeof(Flight));
    else
        {
            fout.write((char *)&flight, sizeof(flight));

            while(fin.read((char *)&flight, sizeof(flight)))
                fout.write((char *)&flight, sizeof(flight));

        }

    fin.close();
    fout.close();

    if (duplicateRecord == 'y')
        {
            remove("TempFlights.dat");
        }
    else
        {
            remove("Flights.dat");
            rename("TempFlights.dat", "Flights.dat");
            cout << "Flight record added successfully."<<endl;

        }

}


void Flight::getAllFlights()
{
    fstream fin("Flights.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(Flight)))
        this->displayFlight();
    fin.close();
}

void Flight::getAllFlights(char* fldate)
{
    bool recordavailable = false;
    fstream fin("Flights.dat", ios::in | ios::binary);


    while(fin.read((char *)this, sizeof(Flight)))
        {
            if (strcmp(this->fltdate, fldate) == 0)
                {
                    this->displayFlight();
                    recordavailable = true;
                }
        }

    fin.close();
    if(!recordavailable)
        cout << "No flights available on " << fldate <<" !!!" <<endl;

}

void Flight::getAllFlights(char* fromairport, char* toairport)
{
    bool scheduleExistFlag = false;
    FlightSchedule fs;
    fstream fin("FlightSchedule.dat", ios::in | ios::binary);
    while(fin.read((char *)&fs, sizeof(FlightSchedule)))
        {
            if ( strcmp(fs.getFromAirport(),fromairport) == 0 && strcmp(fs.getToAirport(), toairport) == 0)
                {
                    scheduleExistFlag = true;
                    getFlightData(fs.getAirlineID(),fs.getConnectionID());

                }
        }
    fin.close();

    if(!scheduleExistFlag)
        cout << "No schedule exists between " << fromairport << " and " << toairport << " !!!";
}


bool Flight::getFlightData(char* airlineid, int connectionid, char* fldate)
{
    bool isflightavailable = false;
    fstream fin("Flights.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(Flight)))
        {
            if ((strcmp(this->fltdate, fldate) == 0) &&
                    (strcmp(this->airline_id, airlineid)) == 0 &&
                    (this->connection_id == connectionid))
                {
                    isflightavailable = true;
                    break;
                }
        }
    fin.close();
    if (isflightavailable)
        {
            formatDisplayFlightTruncated();
            displayFlightTruncated();
            return true;
        }
    else
        {
            cout << "No flight available for Airline " << airlineid << " with connection "
                 << connectionid << " on " << fldate << " !!!"<< endl;
            return false;
        }
}
bool Flight::getFlightData(char* airlineid, int connectionid)
{
    bool isflightavailable = false;
    fstream fin("Flights.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(Flight)))
        {
            if ((strcmp(this->airline_id, airlineid)) == 0 &&
                    (this->connection_id == connectionid))
                {
                    isflightavailable = true;
                    displayFlightTruncated();

                }
        }
    fin.close();
    if (isflightavailable)
        {
            return true;
        }
    else
        {
            return false;
        }

}


bool Flight::getAllFlights(char* fldate,char* fromairport,char* toairport)
{
    FlightSchedule fs;
    bool recordavailable = false;

    fstream fin("Flights.dat", ios::in | ios::binary);
    cout << "Available Flights are :" << endl;
    while(fin.read((char *)this, sizeof(Flight)))
        {
            if (strcmp(this->fltdate,fldate)== 0)
                if (fs.getAllSchedules(this->airline_id,this->connection_id,fromairport,toairport))
                    {
                        cout.setf(ios::left);
                        if(!recordavailable)
                            formatDisplayFlightTruncated();
                        this->displayFlightTruncated();
                        recordavailable = true;
                    }
        }

    fin.close();
    if(!recordavailable)
        {
            cout << "No flights available between " <<  fromairport <<" and "<< toairport <<" on " << fldate <<" !!!"<<endl;
            return false;
        }
    else
        return true;
}

bool Flight::bookSeat(char* airlineid, int connectionid,
                      char* fldate,char* fromairport,
                      char* toairport, char seattype)
{

    FlightSchedule fs;
    bool validateentry = false, isseatavailable = false, seatbooked = false;
    fstream fio("Flights.dat", ios::in |ios::out | ios::binary);
    while(fio.read((char *)this, sizeof(Flight)))
        {
            int pos = fio.tellg();
            if (strcmp(this->fltdate, fldate) == 0 &&
                    strcmp(this->airline_id, airlineid) == 0 &&
                    this->connection_id == connectionid)
                if (fs.getAllSchedules(this->airline_id,this->connection_id,fromairport,toairport))
                    {
                        validateentry = true;
                        if (seattype == 'B')
                            {
                                if (SEATSOCC_B < SEATSMAX_B)
                                    {
                                        this->SEATSOCC_B = this->SEATSOCC_B + 1;
                                        seatbooked = true;
                                        isseatavailable = true;
                                    }
                                else
                                    isseatavailable = false;
                            }
                        else if (seattype == 'E')
                            {
                                if (SEATSOCC < SEATSMAX)
                                    {
                                        this->SEATSOCC = this->SEATSOCC + 1;
                                        seatbooked = true;
                                        isseatavailable = true;
                                    }
                                else
                                    isseatavailable = false;
                            }
                        if(isseatavailable)
                            {
                                fio.seekg(pos - sizeof(Flight)); // File pointer is moved to record to be modified, in this case backward
                                fio.write((char *)this, sizeof(Flight));
                                break;
                            }
                    }

        }

    if (!validateentry)
        cout << "No Flight found. Check Date and Airline details !!!"<<endl;
    if(!isseatavailable)
        cout << "No seats available !!!"<<endl;

    fio.close();

    if (seatbooked)
        return true;
    else
        return false;

}

bool Flight::getFlight(char* airlineid, int connectionid, char* fldate)
{
    bool isflightavailable = false;
    fstream fin("Flights.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(Flight)))
        {
            if ((strcmp(this->fltdate, fldate) == 0) &&
                    (strcmp(this->airline_id, airlineid)) == 0 &&
                    (this->connection_id == connectionid))
                {
                    isflightavailable = true;
                    break;
                }
        }
    fin.close();
    if (isflightavailable)
        return true;
    else
        return false;
}


bool Flight::cancelSeat(char* airlineid, int connectionid, char* fldate, char seattype)
{
    bool seatCancelled = false;
    fstream fio("Flights.dat", ios::in |ios::out | ios::binary);
    while(fio.read((char *)this, sizeof(Flight)))
        {
            int pos = fio.tellg();
            if ((strcmp(this->fltdate, fldate) == 0) &&
                    (strcmp(this->airline_id, airlineid)) == 0 &&
                    (this->connection_id == connectionid))
                {
                    if (seattype == 'B')
                        {
                            if (SEATSOCC_B < SEATSMAX_B)
                                {
                                    this->SEATSOCC_B = this->SEATSOCC_B - 1;
                                    seatCancelled = true;
                                }
                        }
                    else
                        {
                            if (SEATSOCC < SEATSMAX)
                                {
                                    this->SEATSOCC = this->SEATSOCC - 1;
                                    seatCancelled = true;
                                }
                        }
                    if(seatCancelled)
                        {
                            fio.seekg(pos - sizeof(Flight)); // File pointer is moved to record to be modified, in this case backward
                            fio.write((char *)this, sizeof(Flight));
                            break;
                        }
                }
        }


    fio.close();

    if (seatCancelled)
        return true;
    else
        return false;
}

bool Flight::bookSeat(char* airlineid, int connectionid, char* fldate, char seattype)
{
    bool seatbooked = false;
    fstream fio("Flights.dat", ios::in |ios::out | ios::binary);
    while(fio.read((char *)this, sizeof(Flight)))
        {
            int pos = fio.tellg();
            if ((strcmp(this->fltdate, fldate) == 0) &&
                    (strcmp(this->airline_id, airlineid)) == 0 &&
                    (this->connection_id == connectionid))
                {
                    if (seattype == 'B')
                        {
                            if (SEATSOCC_B < SEATSMAX_B)
                                {
                                    this->SEATSOCC_B = this->SEATSOCC_B + 1;
                                    seatbooked = true;
                                }
                        }
                    else
                        {
                            if (SEATSOCC < SEATSMAX)
                                {
                                    this->SEATSOCC = this->SEATSOCC + 1;
                                    seatbooked = true;
                                }
                        }
                    if(seatbooked)
                        {
                            fio.seekg(pos - sizeof(Flight)); // File pointer is moved to record to be modified, in this case backward
                            fio.write((char *)this, sizeof(Flight));
                            break;
                        }
                }

        }


    fio.close();

    if (seatbooked)
        return true;
    else
        return false;

}

bool Flight::bookSeat(char* airlineid, int connectionid, char* fldate, char seattype, char simulateFlag)
{
    bool seatbooked = false;
    fstream fio("Flights.dat", ios::in |ios::out | ios::binary);
    while(fio.read((char *)this, sizeof(Flight)))
        {
            if ((strcmp(this->fltdate, fldate) == 0) &&
                    (strcmp(this->airline_id, airlineid)) == 0 &&
                    (this->connection_id == connectionid))
                {
                    if (seattype == 'B')
                        {
                            if (SEATSOCC_B < SEATSMAX_B)
                                seatbooked = true;
                        }
                    else
                        {
                            if (SEATSOCC < SEATSMAX)
                                seatbooked = true;
                        }
                    break;
                }
        }


    fio.close();

    if (seatbooked)
        return true;
    else
        return false;
}


bool Flight::modifySeat(char* airlineid, int connectionid, char* existingtraveldate,char* revisedtraveldate, char existingseattype, char revisedseattype)
{
    bool isUpdated = bookSeat(airlineid,connectionid,revisedtraveldate,revisedseattype,'X');
    if (!isUpdated)
        return false;
    bool isCancelled = cancelSeat(airlineid,connectionid,existingtraveldate,existingseattype);
    if (isCancelled)
        isUpdated = bookSeat(airlineid,connectionid,revisedtraveldate,revisedseattype);

    if (isUpdated)
        return true;
    else
        return false;
}


