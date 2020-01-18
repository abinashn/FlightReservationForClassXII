#include "Utility.h"
#include "Airline.h"
#include "FlightSchedule.h"

#include <cstring>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

bool Utility::isDateValid(string lv_date)
{
    string date, month, year;
    int dd, mm, yyyy;

    if (!checkDateFormatValidity(lv_date))
        return false;
    else
        {
            date = lv_date.substr(0,2);
            stringstream inDate(date);
            inDate>>dd;

            month = lv_date.substr(3,2);
            stringstream inMonth(month);
            inMonth>>mm;

            year = lv_date.substr(6,4);
            stringstream inYear(year);
            inYear>>yyyy;

            if (checkDateValidity(dd, mm, yyyy))
                return true;
            else
                return false;

        }
}

bool Utility::isTimeValid(string inTime)
{
    string hour, minute;
    int hh, mm;
    if (!checkTimeFormat(inTime))
        return false;
    else
        {
            hour = inTime.substr(0,2);
            stringstream inHour(hour);
            inHour>>hh;

            minute = inTime.substr(3,2);
            stringstream inMinute(minute);
            inMinute>>mm;
            if (checkTimeValidity(hh,mm))
                return true;
            else
                return false;

        }
}

//Checks for the format hh:mm
bool Utility::checkTimeFormat(std::string inTime)
{
    int len = inTime.size();
    if (len!=5)
        return false;
    char * val;
    val = const_cast<char *>((inTime.substr(2,1)).c_str());
    if(strcmp(val,":")!=0)
        return false;

    string hour;
    hour = inTime.substr(0,2);

    char c;
    for(int i=0; i< 2; i++)
        {
            c = hour[i];
            if(!isdigit(c))
                return false;
        }

    string minute;
    minute = inTime.substr(3,2);

    for(int i=0; i< 2; i++)
        {
            c = minute[i];
            if(!isdigit(c))
                return false;
        }

    return true;
}

bool Utility::checkTimeValidity(int h, int m)
{
    if (h > 23 )
        return false;
    if (m > 59)
        return false;

    return true;
}
bool Utility::checkDateFormatValidity(string inDate)
{

//check the length of the string
    int len=inDate.size();
    if(len!=10)
        return false;

    char * val;
    val = const_cast<char *>((inDate.substr(2,1)).c_str());

//check for the dashes in dob

    if(strcmp(val,"-")!=0 && strcmp(val,"/")!=0)
        return false;

    val = const_cast<char *>((inDate.substr(5,1)).c_str());

    if(strcmp(val,"-")!=0 && strcmp(val,"/")!=0)
        return false;


//check for digits

//extract inDate from string

    string date;
    date = inDate.substr(0,2);

//check char by char for numeric

    char c;

    for(int i=0; i< 2; i++)
        {
            c = date[i];
            if(!isdigit(c))
                return false;
        }

//extract month from string

    char * month;
    month = const_cast<char *>((inDate.substr(3,2)).c_str());

//check char by char for numeric

    for(int i=0; i<2; i++)
        {
            c = month[i];
            if(!isdigit(c))
                return false;
        }

//extract year from string

    char * year;
    year = const_cast<char *>((inDate.substr(6,4)).c_str());

//check char by char for numeric

    for(int i=0; i<4; i++)
        {
            c = year[i];
            if(!isdigit(c))
                return false;
        }
    return true;
}

bool Utility::isLeap(int year)
{
// Return true if year is a multiple pf 4 and not multiple of 100 OR year is multiple of 400.
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

bool Utility::checkDateValidity(int d, int m, int y)
{
// If year, month and day are not in given range
    if (y > MAX_VALID_YR ||
            y < MIN_VALID_YR)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;

    // Handle February month with leap year
    if (m == 2)
        {
            if (isLeap(y))
                return (d <= 29);
            else
                return (d <= 28);
        }

    // Months of April, June, Sept and Nov must have number of days less than or equal to 30.
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return (d <= 30);

    return true;
}
/*
Using Binary Search - returns the item position (value > 0) if found else -1
Used by local method checkAirportValidity of class FlightSchedule
Used by Utility::checkAirlineValidity
*/
int Utility::binsearch(string id[], int size, char* item)
{
    int beg, last, mid;
    beg = 0;
    last = size - 1;
    while (beg <= last)
        {
            mid = (beg+last)/2;
            if ( item == id[mid])
                return mid;
            else if ( item > id[mid])
                beg = mid + 1;
            else
                last = mid - 1;
        }

    return -1;
}
/*
checkAirlineValidity checks if an airline id exists in Airlines data file.
Uses Utility::binsearch
*/
int Utility::checkAirlineValidity(char* airline_id)
{
    Airline airline;
    int reccount = 0, i = 0;

    fstream fin("Airlines.dat", ios::in | ios::binary);
    while(fin.read((char *)&airline,sizeof(airline)))
        reccount++;
    fin.close(); // seekg(0) will not work because fin.eof( ) is true

    string id[reccount];

    fin.open("Airlines.dat", ios::in | ios::binary);
    while(fin.read((char *)&airline,sizeof(airline)))
        {
            id[i] = airline.getAirlineID();
            i++;
        }
    fin.close();

    return binsearch(id,reccount,airline_id);
}
/*
Checks if a flight schedule exists for a given airline ID + connection ID
Used in BookFlight::addBooking to check validity for an airline booking
*/
bool Utility::checkConnectionValidity(string id)
{
    FlightSchedule flightSchedule;
    fstream fin("FlightSchedule.dat", ios::in | ios::binary);
    while(fin.read((char *)&flightSchedule, sizeof(flightSchedule)))
        {
            if (id == flightSchedule.getKey())
                {
                    fin.close();
                    return true;
                    break;
                }
        }
    fin.close();
    return false;
}
/*
Check Postal code validity
Valid postal codes are 100000...999999
*/
bool Utility::isPostalCodeValid(int postcode)
{
    if (postcode <= 99999 || postcode > 999999)
        return false;
    return true;

}
/*
Check Mobile not validity
Length must be 10 character
All characters must be digit
*/
bool Utility::isMobilenoValid(std::string mobileno)
{
    int len=mobileno.size();
    if(len!=10)
        return false;

    //check char by char for numeric

    char c;

    for(int i=0; i< 10; i++)
        {
            c = mobileno[i];
            if(!isdigit(c))
                return false;
        }

    return true;

}

/*bool Utility::IsEmailAddress(const std::string& str)
{
    // Locate '@'
    auto at = std::find(str.begin(), str.end(), '@');
    // Locate '.' after '@'
    auto dot = std::find(at, str.end(), '.');
    // make sure both characters are present
    return (at != str.end()) && (dot != str.end());
}*/
/*
Validate Email address
First Character must be between a-z (ASCII value 97 and 122)
@ can not be first character and there should not be more than 1 @ character in the email address
Dot(.) must occur after @, but must not be the next character.
Also there should not be more than 1 dot(.) character in the email address after @
After the last dot(.) the email id should end with 3 characters. (example .com or .org)
*/
bool Utility::IsEmailAddressValid(const std::string& str)
{
    int i,j,k,c = 0, len=str.size();
    char ch = '@', chdot = '.';
    bool flag = false, flagdot = false;

    // First Character must be between a-z (ASCII value 97 and 122)
    if (str[0] < 97 || str[0] > 122)
        return false;

    //@ can not be first character and there should not be more than 1 @ character in the email address
    for ( i = 1; i< len; i++)
        {
            if (str[i] == ch)
                {
                    flag = true;
                    c++;
                    k = i; // gets the position of @ character
                }

        }
    if (c > 1)
        return false;

    //Dot(.) must occur after @, but must not be the next character.
    //Also there should not be more than 1 dot(.) character in the email address after @

    c = 0;
    for ( j = k + 2; j< len; j++)
        {
            if (str[j] == chdot)
                {
                    flagdot = true;
                    c++;
                    k = j;
                }
        }

    if (c > 1)
        return false;
    // after the last dot(.) the email id should end with 3 characters.
    if (flag && flagdot && k == (len - 4) )
        return true;

    return false;

}
/*
Get current time using time
Extract Year, month and date from current time
Format date to return 2 digit by appending leading 0's (example '5' is returned as '05')
*/
string Utility::getCurrentDate()
{
    time_t t = time(NULL);
    tm* tPtr = localtime(&t);
    string year = str2ID(tPtr->tm_year + 1900);
    string month = str2ID(tPtr->tm_mon + 1);
    string day = str2ID(tPtr->tm_mday);
    if (tPtr->tm_mday < 10)
        day = string(1,'0').append(day);
    string currentdate = day+"-"+month+"-"+year;
    return currentdate;

}

/*
// converts int to string
int -> stringstream
stringstream -> string
*/
string Utility::str2ID(int connection_id)
{
    stringstream ss_connection_id;
    string s_connection_id;
    ss_connection_id << connection_id;
    ss_connection_id >> s_connection_id;
    return s_connection_id;
}

