#include "FlightSchedule.h"
#include "Airport.h"
#include "Utility.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

int checkAirportValidity(char* );

Utility util;

void FlightSchedule::addschedule()
{
    string dummy;
    char isEntryValid = 'N';
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
    cout << "Enter connection ID (3 digit number): ";
    cin >> connection_id;
    getline(cin,dummy);
    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Enter from airport (Airport ID) : ";
            gets(fromairport_id);
            for (int i =0; i<3; i++)
                fromairport_id[i] = toupper(fromairport_id[i]);
            int result = checkAirportValidity(fromairport_id);
            if (result > -1 )
                isEntryValid = 'Y';
            else
                cout << "Airport ID not found"<<endl;
        }
    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Enter to airport (Airport ID) : ";
            gets(toairport_id);
            for (int i =0; i<3; i++)
                toairport_id[i] = toupper(toairport_id[i]);
            int result = checkAirportValidity(toairport_id);
            if (result > -1 )
                isEntryValid = 'Y';
            else
                cout << "Airport ID not found"<<endl;
        }

    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Enter Departure time (in hh:mm format) : ";
            gets(depttime);
            if (util.isTimeValid(depttime))
                isEntryValid = 'Y';
            else
                cout << depttime <<" is not a valid time\n";
        }
    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Enter Arrival time (in hh:mm format) : ";
            gets(arrtime);
            if (util.isTimeValid(arrtime))
                isEntryValid = 'Y';
            else
                cout << arrtime <<" is not a valid time\n";
        }

    cout << "Enter Distance (in K.M.) : ";
    cin >> distance;
    saveSchedule();

}

void FlightSchedule::formatDisplaySchedule()
{
    cout << "\nAvailable schedules are :" << endl;
    cout.setf(ios::left);
    cout << setw(12) << "Airline ID" << setw(10) << "Conn. ID" << setw(14) << "From Airport"
    << setw(12) << "To Airport" << setw(11) << "Dept Time" << setw(11) << "Arr Time" << setw(16)
    << "Distance(KM)" << endl;

}


void FlightSchedule::displayschedule()
{
    cout.setf(ios::left);
    cout << setw(12) << airline_id << setw(10);
    cout << connection_id<< setw(14);
    cout << fromairport_id << setw(12);
    cout << toairport_id << setw(11);
    cout << depttime << setw(11);
    cout << arrtime << setw(16);
    cout << distance << endl;
}
/*
Uses binary search from utility class to check if an airport ID exist based on
records in Airport data file.
*/
int checkAirportValidity(char* airport_id)
{
    Airport airport;
    int reccount = 0, i = 0;

    fstream fin("Airports.dat", ios::in | ios::binary);
    while(fin.read((char *)&airport,sizeof(airport)))
        reccount++;
    fin.close(); // seekg(0) will not work because fin.eof( ) is true

    string id[reccount];

    fin.open("Airports.dat", ios::in | ios::binary);
    while(fin.read((char *)&airport,sizeof(airport)))
        {
            id[i] = airport.getAirportID();
            i++;
        }
    fin.close();

    return util.binsearch(id,reccount,airport_id);
}

//For FlightSchedule key is combination of Airline ID + Connection ID
string FlightSchedule::getKey()
{
    stringstream ss_connection_id;
    string s_connection_id;
    ss_connection_id << connection_id; // Converts int to stringstream
    ss_connection_id >> s_connection_id; // Converts stringstream to string
    return airline_id + s_connection_id; //
}


void FlightSchedule::saveSchedule()
{
    FlightSchedule flightSchedule;
    fstream fin("FlightSchedule.dat", ios::in | ios::binary);
    fstream fout("TempFlightSchedule.dat", ios::out | ios::binary |ios::app);

    char lastRecord='y',duplicateRecord = 'n';;

    string n_id = this->getKey();

    while(fin.read((char *)&flightSchedule, sizeof(flightSchedule)))
        {
            string f_id = flightSchedule.getKey();
            if ( n_id == f_id)
                {
                    duplicateRecord = 'y';
                    break;
                }
            else if(n_id < f_id)
                {
                    fout.write((char *)this, sizeof(FlightSchedule));
                    lastRecord = 'n';
                    break;
                }
            else
                {
                    fout.write((char *)&flightSchedule, sizeof(flightSchedule));
                }

        }
    if (duplicateRecord == 'y')
        cout << "\nDuplicate record found. Entry not made!!!";
    else if(lastRecord == 'y'&& duplicateRecord != 'y')
        fout.write((char *)this, sizeof(FlightSchedule));
    else
        {
            fout.write((char *)&flightSchedule, sizeof(flightSchedule));

            while(fin.read((char *)&flightSchedule, sizeof(flightSchedule)))
                fout.write((char *)&flightSchedule, sizeof(flightSchedule));

        }

    fin.close();
    fout.close();

    if (duplicateRecord == 'y')
        {
            remove("TempFlightSchedule.dat");
        }
    else
        {
            remove("FlightSchedule.dat");
            rename("TempFlightSchedule.dat", "FlightSchedule.dat");
        }
}

void FlightSchedule::getAllSchedules()
{

    fstream fin("FlightSchedule.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(FlightSchedule)))
        this->displayschedule();

    fin.close();

}
vector<FlightSchedule> FlightSchedule::getAllSchedules(string fromairport, string toairport)
{
    vector<FlightSchedule> schedules;
    fstream fin("FlightSchedule.dat", ios::in | ios::binary);
    cout << "\nAvailable schedules between " << fromairport << " & " << toairport << " are :"<<endl;
    while(fin.read((char *)this, sizeof(FlightSchedule)))
        {
            if ( (this->fromairport_id == fromairport) && (this->toairport_id == toairport))
                schedules.push_back( *this );
        }
    fin.close();
    return schedules;
}

bool FlightSchedule::getAllSchedules(char* airlineid, int connectionid,char* fromairport, char* toairport)
{
    bool scheduleExistFlag = false;
    fstream fin("FlightSchedule.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(FlightSchedule)))
        {
            if ( strcmp(this->airline_id, airlineid) == 0 && this->connection_id == connectionid)
                if ( strcmp(this->fromairport_id,fromairport) == 0 && strcmp(this->toairport_id, toairport) == 0)
                    {
                        scheduleExistFlag = true;
                        break;
                    }
        }
    fin.close();
    if (scheduleExistFlag)
        return true;
    else
        return false;
}
void FlightSchedule::getAllSchedules(char* fromairport, char* toairport)
{
    bool scheduleExistFlag = false;
    fstream fin("FlightSchedule.dat", ios::in | ios::binary);
    formatDisplaySchedule();
    while(fin.read((char *)this, sizeof(FlightSchedule)))
        {
                if ( strcmp(this->fromairport_id,fromairport) == 0 && strcmp(this->toairport_id, toairport) == 0)
                    {
                        scheduleExistFlag = true;
                        displayschedule();
                    }
        }
    fin.close();

    if(!scheduleExistFlag)
        cout << "No schedule exists between " << fromairport << " and " << toairport << " !!!";
}


char* FlightSchedule::getFromAirport()
{
    return fromairport_id;
}

char* FlightSchedule::getToAirport()
{
    return toairport_id;
}

char* FlightSchedule::getDeptTime()
{
    return depttime;
}

char* FlightSchedule::getArrTime()
{
    return arrtime;
}

char* FlightSchedule::getAirlineID()
{
    return airline_id;
}

int FlightSchedule::getConnectionID()
{
    return connection_id;
}

FlightSchedule* FlightSchedule::getAirportDetail(char* airlineid, int connectionid)
{
    bool scheduleExistFlag = false;
    fstream fin("FlightSchedule.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(FlightSchedule)))
        {
            if ( strcmp(this->airline_id, airlineid) == 0 && this->connection_id == connectionid)
                {
                    scheduleExistFlag = true;
                    break;
                }
        }
    fin.close();
    if (scheduleExistFlag)
        return this;
    else
        return NULL;
}




