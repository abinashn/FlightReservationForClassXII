#ifndef UTILITY_H
#define UTILITY_H

#include <string>


class Utility
{
public:

    bool isDateValid(std::string);
    bool isTimeValid(std::string);
    int binsearch (std::string [], int, char*);
    int checkAirlineValidity(char* );
    bool checkConnectionValidity(std::string);
    bool isPostalCodeValid(int postcode);
    bool isMobilenoValid(std::string mobileno);
    //static bool IsEmailAddress(const std::string& str);
    static bool IsEmailAddressValid(const std::string& str);
    std::string getCurrentDate();
    std::string str2ID(int connection_id);

private:
    const int MAX_VALID_YR = 9999;
    const int MIN_VALID_YR = 1800;
    bool checkDateFormatValidity(std::string);
    bool isLeap(int);
    bool checkDateValidity(int, int, int);
    bool checkTimeFormat(std::string);
    bool checkTimeValidity(int,int);

};

#endif // UTILITY_H
