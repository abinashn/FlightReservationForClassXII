#include <iostream>
#include <fstream>
#include <cstring>

#include "Airport.h"

using namespace std;

void Airport::setData()
{
    cout << "Enter Airport ID (3 character Short Identifier): ";
    gets(airport_id);
    int len = strlen(airport_id);
    while (len != 3)
        {
            cout << "Airport ID must be of 3 characters." <<endl;
            cout << "Enter Airport ID (3 character Short Identifier): ";
            gets(airport_id);
            len = strlen(airport_id);
        }
    for (int i =0; i<3; i++)
        airport_id[i] = toupper(airport_id[i]);

    cout << "Enter Airport Name: ";
    gets(airport_name);

}

void Airport::displayData()
{
    cout << "ID. : " << airport_id;
    cout << "\tName : " << airport_name << "\n";
}

char* Airport::getAirportID()
{
    return airport_id;
}

void Airport::modifyData()
{
    cout << "Enter Airport Name: ";
    cin.getline(airport_name,30);
}

void Airport::displayall()
{
    fstream fin("Airports.dat", ios::in | ios::binary);
    cout<<"\nList of Airports are: "<<"\n";

    while(fin.read((char *)this,sizeof(Airport)))
        this->displayData();

    fin.close();
}

void Airport::addAirport()
{
    string dummy;
    Airport airport, airport_n;
    char nextEntry = 'Y';
    while(nextEntry == 'y' || nextEntry == 'Y')
        {
            fstream fin("Airports.dat", ios::in | ios::binary);
            fstream fout("TempAirports.dat", ios::out | ios::binary |ios::app);

            char lastAirportRecord='y', duplicateRecord = 'n';
            airport_n.setData();
            string n_id = airport_n.getAirportID();

            while(fin.read((char *)&airport, sizeof(airport)))
                {
                    string f_id = airport.getAirportID();
                    if ( n_id == f_id)
                        {
                            duplicateRecord = 'y';
                            break;
                        }
                    else if(n_id < f_id)
                        {
                            fout.write((char *)&airport_n, sizeof(airport_n));
                            lastAirportRecord = 'n';
                            break;
                        }
                    else
                        {
                            fout.write((char *)&airport, sizeof(airport));
                        }
                }

            if (duplicateRecord == 'y')
                cout << "\nDuplicate record found. Entry not made!!!";

            if(lastAirportRecord == 'y' && duplicateRecord != 'y')
                fout.write((char *)&airport_n, sizeof(airport_n));
            else
                {
                    fout.write((char *)&airport, sizeof(airport));

                    while(fin.read((char *)&airport, sizeof(airport)))
                        fout.write((char *)&airport, sizeof(airport));

                }

            fin.close();
            fout.close();

            remove("Airports.dat");
            rename("TempAirports.dat", "Airports.dat");

            fin.open("Airports.dat", ios::in);
            cout<<"\nUpdated list of airports are:\n";
            while(fin.read((char *)&airport,sizeof(airport)))
                {
                    airport.displayData();
                }

            fin.close();

            cout << "\nEnter another airport? (Y/N) : ";
            cin >> nextEntry;
            getline(cin,dummy);
        }
}

void Airport::modifyAirport()
{
    Airport airport;
    string airport_id;
    char recFound = 'n';
    fstream fio("Airports.dat", ios::in |ios::out | ios::binary); //input output mode
    cout << "\nEnter the ID of Airport to be modified : ";
    getline(cin,airport_id);
    while(fio.read((char *)&airport, sizeof(airport)))
        {
            int pos = fio.tellg();
            string f_id = airport.getAirportID();
            if ( airport_id ==f_id )
                {
                    airport.modifyData();
                    fio.seekg(pos - sizeof(airport)); // File pointer is moved to record to be modified, in this case backward
                    fio.write((char *)&airport, sizeof(airport));
                    recFound = 'y';
                    break;
                }
        }
    if (recFound == 'n')
        cout << "\nAirport " << airport_id << " not Found. ";
    else
        {
            fio.seekg(0); // Move to the start of the file
            cout<<"\nUpdated list of airports are:\n";
            while(fio.read((char *)&airport,sizeof(airport)))
                airport.displayData();
        }
    fio.close();
}

void Airport::deleteAirport()
{
    Airport airport;
    string airport_id;
    char recFound = 'n', reconfirm = 'n';
    fstream fin("Airports.dat", ios::in | ios::binary);
    fstream fout("TempAirports.dat", ios::out | ios::binary |ios::app);
    cout << "\nEnter the ID of Airport to be deleted : ";
    getline(cin,airport_id);

    while(fin.read((char *)&airport, sizeof(airport)))
        {
            string f_id = airport.getAirportID();
            if ( airport_id ==f_id )
                {
                    recFound = 'y';
                    cout << "Are your sure you want to delete this record? (Y/N) : ";
                    cin >> reconfirm;
                    if ( reconfirm == 'n' || reconfirm == 'y' || reconfirm == 'N' || reconfirm == 'Y')
                        {
                            if (reconfirm == 'n' || reconfirm == 'N')
                                fout.write((char *)&airport, sizeof(airport));
                        }
                    else
                        {
                            cout << "Invalid input!!!"<<endl;
                            fout.write((char *)&airport, sizeof(airport));
                        }

                }
            else
                fout.write((char *)&airport, sizeof(airport));
        }
    if (recFound == 'n')
        cout << "\nAirport " << airport_id << " not Found. ";

    fin.close();
    fout.close();

    remove("Airports.dat");
    rename("TempAirports.dat", "Airports.dat");

    fin.open("Airports.dat", ios::in);
    cout<<"\nUpdated list of airports are:\n";
    while(fin.read((char *)&airport,sizeof(airport)))
        {
            airport.displayData();
        }

    fin.close();
}
