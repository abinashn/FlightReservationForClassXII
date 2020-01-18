#include "Airline.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
/*
Private Method used to take inputs for Airline and is called from addAirline method.
Airline ID is converted to upper case character
*/
void Airline::setData()
{
    cout << "Enter Airline ID (2 character Short Identifier): ";
    gets(airline_id);
    int len = strlen(airline_id);
    while (len != 2)
        {
            cout << "Airline ID must be of 2 character." << endl;
            cout << "Enter Airline ID (2 character Short Identifier): ";
            gets(airline_id);
            len = strlen(airline_id);
        }
    for (int i =0; i<2; i++)
        airline_id[i] = toupper(airline_id[i]);
    cout << "Enter Airline Name: ";
    gets(airline_name);
}
/*
Private method to Display Air line data, called from Airline:: displayall()
*/
void Airline::displayData()
{
    cout << "ID. : " << airline_id;
    cout << "\tName : " << airline_name << "\n";
}
/*
Private method used by Airline:: modifyAirline() to input airline name.
*/
void Airline:: modifyData()
{
    cout << "Enter Airline Name: ";
    gets(airline_name);
}
/*
Used by Utility::checkAirlineValidity to check if an airline ID exist
*/
char* Airline::getAirlineID()
{
    return airline_id;
}
/*
Displays all airline records by reading the Airlines.dat file and using method void Airline:: displayData();
*/
void Airline:: displayall()
{
    fstream fin("Airlines.dat", ios::in | ios::binary);
    cout<<"\nList of Airlines are: "<<"\n";

    while(fin.read((char *)this,sizeof(Airline)))
        this->displayData();

    fin.close();
}

/*
Modifies airline name.
Uses method Airline::getAirlineID() and  void Airline:: modifyData()
*/

void Airline:: modifyAirline()
{
    Airline airline;
    char airline_id[3];
    char recFound = 'n';

    cout << "\nEnter the ID of Airline to be modified : ";
    gets(airline_id);
    for (int i =0; i<2; i++)
        airline_id[i] = toupper(airline_id[i]);

    fstream fio("Airlines.dat", ios::in |ios::out | ios::binary); //input output mode
    while(fio.read((char *)&airline, sizeof(airline)))
        {
            int pos = fio.tellg();
            char* f_id = airline.getAirlineID();
            if ( strcmp(airline_id,f_id) == 0 )
                {
                    airline.modifyData();
                    fio.seekg(pos - sizeof(airline)); // File pointer is moved to record to be modified, in this case backward
                    fio.write((char *)&airline, sizeof(airline));
                    recFound = 'y';
                    break;
                }
        }
    if (recFound == 'n')
        cout << "\nAirline " << airline_id << " not Found. ";
    else
        {
            fio.seekg(0); // Move to the start of the file
            while(fio.read((char *)&airline,sizeof(airline)))
                airline.displayData();
        }
    fio.close();

}
/*
Adds a new airline record to a binary file.
By default records are added shorted by Airline ID, uses a temporary file to add new records
Checks for duplicate record using function Airline::getAirlineID()
*/
void Airline:: addAirline()
{
    string dummy;
    Airline airline, airline_n;
    char nextEntry = 'Y';
    while(nextEntry == 'y' || nextEntry == 'Y')
        {
            fstream fin("Airlines.dat", ios::in | ios::binary);
            fstream fout("TempAirlines.dat", ios::out | ios::binary |ios::app);

            char lastAirlineRecord='y', duplicateRecord = 'n';
            airline_n.setData();
            char* n_id = airline_n.getAirlineID();

            while(fin.read((char *)&airline, sizeof(airline)))
                {
                    char* f_id = airline.getAirlineID();
                    int i = strcmp(f_id,n_id);
                    if ( i == 0)
                        {
                            duplicateRecord = 'y';
                            break;
                        }
                    else if(i > 0)
                        {
                            fout.write((char *)&airline_n, sizeof(airline_n));
                            lastAirlineRecord = 'n';
                            break;
                        }
                    else
                        {
                            fout.write((char *)&airline, sizeof(airline));
                        }
                }

            if (duplicateRecord == 'y')
                cout << "\nDuplicate record found. Entry not made!!!";

            if(lastAirlineRecord == 'y' && duplicateRecord != 'y')
                fout.write((char *)&airline_n, sizeof(airline_n));
            else
                {
                    fout.write((char *)&airline, sizeof(airline));

                    while(fin.read((char *)&airline, sizeof(airline)))
                        fout.write((char *)&airline, sizeof(airline));

                }

            fin.close();
            fout.close();

            remove("Airlines.dat");
            rename("TempAirlines.dat", "Airlines.dat");

            fin.open("Airlines.dat", ios::in);
            cout<<"\nUpdated list of airlines are:\n";
            while(fin.read((char *)&airline,sizeof(airline)))
                {
                    airline.displayData();
                }

            fin.close();

            cout << "\nEnter another airline? (Y/N) : ";
            cin >> nextEntry;
            getline(cin,dummy);
        }

}

/*
Deletes an airline record by airline ID.
Uses Temporary file for coping all records except the one to be deleted.
Reconfirmation is used before the actual deletion.
*/

void Airline:: deleteAirline()
{
    Airline airline;
    char airline_id[3];
    char recFound = 'n', reconfirm = 'n';

    cout << "\nEnter the ID of Airline to be deleted : ";
    gets(airline_id);
    for (int i =0; i<2; i++)
        airline_id[i] = toupper(airline_id[i]);

    fstream fin("Airlines.dat", ios::in | ios::binary);
    fstream fout("TempAirlines.dat", ios::out | ios::binary |ios::app);

    while(fin.read((char *)&airline, sizeof(airline)))
        {
            char* f_id = airline.getAirlineID();
            if ( strcmp(airline_id,f_id) == 0 )
                {
                    recFound = 'y';
                    cout << "Are your sure you want to delete this record? (Y/N) : ";
                    cin >> reconfirm;
                    if (reconfirm == 'n')
                        fout.write((char *)&airline, sizeof(airline));
                }
            else
                fout.write((char *)&airline, sizeof(airline));
        }
    if (recFound == 'n')
        cout << "\nAirline " << airline_id << " not Found. ";

    fin.close();
    fout.close();

    remove("Airlines.dat");
    rename("TempAirlines.dat", "Airlines.dat");

    fin.open("Airlines.dat", ios::in);
    cout<<"\nUpdated list of airlines are:\n";
    while(fin.read((char *)&airline,sizeof(airline)))
        {
            airline.displayData();
        }

    fin.close();
}
