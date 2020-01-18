#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
public:
    void addCustomer();
    void deleteCustomer();
    void modifyCustomer();
    void displayAllCustomers();
    Customer* getCustomerbyID(int custID);
    void getCustomerbyPhone(char* phoneno,Customer &cust);
    bool getCustomerbyEmail(char* emailID,Customer &cust);
    void displayCustomer();
    void formatDisplayCustomer();
    int getCustomerID();

private:
    int customer_id;
    char name[35];
    char dob[11];
    int postal_code;
    char phone[11];
    char email[50];
    void saveCustomer();
    int calculateCustomerID();
    void modifyData();


};

#endif // CUSTOMER_H
