#include "Customer.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

void Customer::addCustomer()
{
    Utility util;
    string dummy;
    char isEntryValid = 'N';
    cout << "Enter Customer details : "<<endl;
    customer_id = calculateCustomerID();
    cout << "Name : ";
    cin.getline(name,35);
    for (int i =0; i<34; i++)
        name[i] = toupper(name[i]);
    cin.clear(); // Flush the buffer
    cin.sync();

    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Date of Birth (in dd-mm-yyyy format) : ";
            cin.getline(dob,11);
            cin.clear(); // Flush the buffer
            cin.sync();
            if (util.isDateValid(dob))
                isEntryValid = 'Y';
            else
                cout << dob <<" is not a valid date\n";
        }

    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Postal Code : ";
            cin >> postal_code;
            if (util.isPostalCodeValid(postal_code))
                isEntryValid = 'Y';
            else
                cout << postal_code <<" is not a valid Postal Code\n";
        }

    cin.ignore();
    isEntryValid = 'N';
    while(isEntryValid == 'N')
        {
            cout << "Mobile no : ";
            cin.getline(phone,11);
            cin.clear(); // Flush the buffer
            cin.sync();
            if (util.isMobilenoValid(phone))
                isEntryValid = 'Y';
            else
                cout << phone <<" is not a valid Mobile no\n";
        }

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
                cout << email <<" is not a valid Email address\n";
            Customer c;
            bool customerexistbyEmailID = getCustomerbyEmail(email,c);
            if (customerexistbyEmailID)
                {
                    isEntryValid = 'N';
                    cout << email <<" is not unique!!!\n";
                }
        }

    //Write to File
    saveCustomer();

}

void Customer::deleteCustomer()
{
    int customerid;
    char recFound = 'n', reconfirm = 'n';
    fstream fin("Customers.dat", ios::in | ios::binary);
    fstream fout("TempCustomers.dat", ios::out | ios::binary |ios::app);
    cout << "\nEnter the ID Customer to be Deleted : ";
    cin >> customerid;

    while(fin.read((char *)this, sizeof(Customer)))
        {

            if ( this->customer_id == customerid )
                {
                    recFound = 'y';
                    cout << "Are your sure you want to delete this record? (Y/N) : ";
                    cin >> reconfirm;
                    if (reconfirm == 'n')
                        fout.write((char *)this, sizeof(Customer));
                }
            else
                fout.write((char *)this, sizeof(Customer));
        }
    if (recFound == 'n')
        cout << "\nCustomer ID " << customerid << " not Found. ";

    fin.close();
    fout.close();

    remove("Customers.dat");
    rename("TempCustomers.dat", "Customers.dat");

    fin.open("Customers.dat", ios::in | ios::binary);
    cout<<"\nUpdated list of Customers are:\n";
    formatDisplayCustomer();
    while(fin.read((char *)this,sizeof(Customer)))
        {
            this->displayCustomer();
        }

    fin.close();

}

void Customer::modifyCustomer()
{
    int customerid;
    char recFound = 'n';
    fstream fio("Customers.dat", ios::in |ios::out | ios::binary); //input output mode
    cout << "\nEnter the ID Customer to be Modified : ";
    cin >> customerid;

    while(fio.read((char *)this, sizeof(Customer)))
        {
            int pos = fio.tellg();
            if ( this->customer_id == customerid )
                {
                    this->modifyData();
                    fio.seekg(pos - sizeof(Customer)); // File pointer is moved to record to be modified, in this case backward
                    fio.write((char *)this, sizeof(Customer));
                    recFound = 'y';
                    break;
                }
        }
    if (recFound == 'n')
        cout << "\nCustomer ID " << customerid << " not Found. ";
    else
        {
            fio.seekg(0); // Move to the start of the file
            cout<<"\nUpdated list of Customers are:\n";
            formatDisplayCustomer();
            while(fio.read((char *)this,sizeof(Customer)))
                this->displayCustomer();
        }
    fio.close();
}
void Customer::modifyData()
{
    Utility util;
    string dummy;
    char isEntryValid = 'N', option = 'n';
    cout << "Modify Postal Code (y/n): ";
    cin >> option;
    cin.ignore();
    if (option == 'y' || option == 'Y')
        {
            while(isEntryValid == 'N')
                {
                    cout << "Postal Code : ";
                    cin >> postal_code;
                    if (util.isPostalCodeValid(postal_code))
                        isEntryValid = 'Y';
                    else
                        cout << postal_code <<" is not a valid Postal Code\n";
                }
        }

    isEntryValid = 'N';
    cout << "Modify Mobile no (y/n): ";
    cin >> option;
    cin.ignore();
    if (option == 'y' || option == 'Y')
        {
            while(isEntryValid == 'N')
                {
                    cout << "Mobile no : ";
                    cin.getline(phone,11);
                    cin.clear(); // Flush the buffer
                    cin.sync();
                    if (util.isMobilenoValid(phone))
                        isEntryValid = 'Y';
                    else
                        cout << phone <<" is not a valid Mobile no\n";
                }
        }
    isEntryValid = 'N';
    cout << "Modify Email id (y/n): ";
    cin >> option;
    cin.ignore();
    if (option == 'y' || option == 'Y')
        {
            while(isEntryValid == 'N')
                {
                    cout << "Email id : ";
                    cin.getline(email,50);
                    for (int i =0; i<49; i++)
                        email[i] = tolower(email[i]);
                    if (Utility::IsEmailAddressValid(email))
                        isEntryValid = 'Y';
                    else
                        cout << email <<" is not a valid Email address\n";
                    Customer c1;
                    bool customerexistbyEmailID = getCustomerbyEmail(email,c1);
                    if (customerexistbyEmailID)
                        {
                            isEntryValid = 'N';
                            cout << email <<" is not unique!!!\n";
                        }
                }
        }

}



void Customer::displayCustomer()
{
    cout << setw(13) << customer_id << setw(36) << name << setw(15) << dob <<
         setw(8) << postal_code<<setw(12) <<phone<<setw(50) <<email <<endl;
}

void Customer::formatDisplayCustomer()
{
    cout.setf(ios::left);
    cout << "Customer Information : " << endl;
    cout << setw(13) << "Customer ID" << setw(36) << "Customer Name" << setw(15) << "Date Of Birth" <<
         setw(8) << "PO Box" << setw(12) << "Mobile No" << setw(50) << "Customer Email ID" << endl;
}
int Customer::getCustomerID()
{
    return customer_id;
}


void Customer::displayAllCustomers()
{

    fstream fin("Customers.dat", ios::in | ios::binary);
    while(fin.read((char *)this,sizeof(Customer)))
        this->displayCustomer();
    fin.close();
}


void Customer::saveCustomer()
{
    fstream fout("Customers.dat", ios::out | ios::binary | ios::app);
    fout.write((char *)this, sizeof(Customer));
    fout.close();
}
int Customer::calculateCustomerID()
{
    fstream fin("Customers.dat", ios::in | ios::binary);
    int customerid = 101;
    if (fin.is_open())
        {
            int sizeofcust = sizeof(Customer);
            fin.seekg(-sizeofcust,ios_base::end); //Goto the last record
            fin.read((char *)this,sizeof(Customer));
            customerid = this->customer_id + 1;
            fin.close();
        }
    return customerid;
}

Customer* Customer::getCustomerbyID(int custID)
{
    bool customerExist = false;
    fstream fin("Customers.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(Customer)))
        {
            if (this->customer_id == custID)
                {
                    customerExist = true;
                    break;
                }
        }
    fin.close();
    if (customerExist)
        return this;
    else
        return NULL;
}

void Customer::getCustomerbyPhone(char* phoneno, Customer &cust)
{
    fstream fin("Customers.dat", ios::in | ios::binary);
    while(fin.read((char *)this, sizeof(Customer)))
        {
            if (strcmp(this->phone,phoneno) == 0)
                this->displayCustomer();
        }
    fin.close();
}

bool Customer::getCustomerbyEmail(char* emailID,Customer &cust)
{
    bool emailExist = false;
    fstream fin("Customers.dat", ios::in | ios::binary);
    while(fin.read((char *)&cust, sizeof(Customer)))
        {
            if (strcmp(cust.email, emailID)==0)
                {
                    emailExist = true;
                    break;
                }
        }
    fin.close();
    if (emailExist)
        return true;
    else
        return false;

}


