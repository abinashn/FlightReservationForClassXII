#ifndef PLANE_H
#define PLANE_H

struct Plane
{
    char PLANETYPE[5];
    int SEATSMAX;
    int SEATSMAX_B;

    void getdata();
    Plane* getaircraftdata(char*);
    void setdata();
    char* getKey();
    void savePlane();
    void displayall();
    void formatdisplayall();
};

#endif // PLANE_H
