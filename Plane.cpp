#include "Plane.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

Plane* Plane::getaircraftdata(char* PLANETYPE)
{
    fstream fin("Planes.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(Plane)))
        {
            char* aircrafttype = this->getKey();
            if (strcmp(PLANETYPE, aircrafttype) == 0 )
                {
                    return this;
                    break;
                }
        }
    fin.close();
    return NULL;
}

void Plane::setdata()
{
    cout << "Aircraft Type : ";
    gets(PLANETYPE);
    for (int i =0; i<4; i++)
        PLANETYPE[i] = toupper(PLANETYPE[i]);
    cout << "Maximum capacity in economy class : ";
    cin >> SEATSMAX;
    cout << "Maximum capacity in business class : ";
    cin >> SEATSMAX_B;
    savePlane();

}

char* Plane::getKey()
{
    return PLANETYPE;
}
void Plane::savePlane()
{
    Plane plane;
    fstream fin("Planes.dat", ios::in | ios::binary);
    fstream fout("TempPlanes.dat", ios::out | ios::binary |ios::app);

    char lastRecord='y';

    string n_id = this->getKey();

    while(fin.read((char *)&plane, sizeof(plane)))
        {
            string f_id = plane.getKey();
            if(n_id <= f_id)
                {
                    fout.write((char *)this, sizeof(Plane));
                    lastRecord = 'n';
                    break;
                }
            else
                {
                    fout.write((char *)&plane, sizeof(plane));
                }

        }
    if(lastRecord == 'y')
        fout.write((char *)this, sizeof(Plane));
    else
        {
            fout.write((char *)&plane, sizeof(plane));

            while(fin.read((char *)&plane, sizeof(plane)))
                fout.write((char *)&plane, sizeof(plane));

        }

    fin.close();
    fout.close();

    remove("Planes.dat");
    rename("TempPlanes.dat", "Planes.dat");
}

void Plane::getdata()
{
    cout.setf(ios::left);
    cout << setw(16) << PLANETYPE << setw(20) << SEATSMAX << setw(20) << SEATSMAX_B << endl;
}

void Plane::formatdisplayall()
{
    cout.setf(ios::left);
    cout << setw(16) << "Aircraft Type" << setw(20) << "Max Economy Seat" << setw(20) << "Max Business Seat"
    <<endl;
}


void Plane::displayall()
{
    fstream fin("Planes.dat", ios::in | ios::binary |ios::app);
    while(fin.read((char *)this,sizeof(Plane)))
        {
            this->getdata();
        }

    fin.close();
}


