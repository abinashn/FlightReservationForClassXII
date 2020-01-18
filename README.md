# Flight Reservation For Class XII
C++ Project Class 12th - for Flight Reservation system

**OBJECTIVE**

The objective of this project is to create an Online Flight Reservation System for National flights operated by different airlines between major cities in India. This project gives an online platform for the customers to book a flight ticket to their choice of destination and dates for travel. 

The “Flight reservation system” project is an attempt to stimulate the basic concepts of airline reservation system. The system enables the customer search for airline flights for two travel cities on a specified date, choose a flight based on the details, reservation of flight and cancellation of reservation.
 
**ENVIRONMENT**

-	Operating System: Windows OS
-	IDE (Development environment): Code::Blocks 17.12
-	C++ Compiler: MinGW's GNU GCC compiler for C++
-	Command Prompt / Output Window Size: 150*30 pixels

**FEATURES**

The major features implemented as a part of this project are:-
- Maintenance Platform for Airline Operators / Agents
-	Book a flight ticket
-	Search for flights between cities on a given day
-	Modify a booking (Change travel date and/or Travel class for the same airline carrier)
-	Cancel a booking

**C++ Concepts Used**

1.	File handling 
2.	Encapsulation
3.  Inheritance 
    - Flight is a base class; 
    - BookFlight is the derived class 
4.	Binary Search 
    - Modify and Delete functions use binary search
    - Add method uses for Duplicate checks at various places
5.	Records are added at sorted position in all data files using Sequential Sort
6.	Pointers (this, object)
7.	Function Overloading

**DESIGN**

This section elaborates the details of the building blocks and design framework of the various components of the project.

**Basic Design**

-	The Project uses Object oriented programming with binary data files handling to store and manipulate the data records.
-	The definition and declaration of classes are separated into Header (.h) and Source code (.cpp) files respectively.
-	Uses iomanip library for output formatting.

Approach for Adding, Modifying and Deleting records to / from the data files are as below:-

**_1. Add a record_**

-	Binary Data file is opened in input mode along with a temporary binary file in output-append mode. 
-	Records are appended using the insertion sort in ascending order. i.e. record (with existing key) is fetched and is compared against the record to be inserted (new key). 
o	If the keys are equal, then record is identified as duplicate and the insertion is rejected. 
o	If the existing key > new key, then the new key is written to the temporary file, else the existing key is written to the temporary file.
o	Once all records are written to temporary file and no duplicates are found, the main file is deleted, and the temporary file is renamed as main file.


**_2. Modify a record_**

-	The binary data file is opened in input-output mode. 
-	File is read record by record and the key field is compared against the key to be modified. 
-	If a match is found, the file pointer is moved by one record (fio.seekg(pos - sizeof(object))) and the record is overwritten with new values.  

**_3. Delete a record_**

-	The binary data file is opened in input mode and a temporary data file is opened in output-append mode. 
-	File is read record by record and the key field is compared against the key to be deleted. 
-	If a match is found the record is not written to temporary file else the record is written to temporary file.
-	Once all records are written to temporary file, the main file is deleted, and the temporary file is renamed as main file.

**Reusable Functions**

The validation and search functions are implemented in a separate class called “Utility” and reused throughout the project as and when needed. 
Validity of Data & Format are done for following fields defined and used as Functions of the Utility Class
-	Date and Time, Email, Phone, Postal code, Airline id, Connection id 

***Binary search is used to validate airport id or airline id entries made by user during various inputs.***

**Business Logic and Rules**

Flight Booking and its modification is explained using the approach below :- 

1.	Customer searches for a flight, by providing a travel date and source and destination cities/airports.
2.	A flight record must exist for the travel date
3.	The destinations are maintained for an airline with a connection id between two cities (airports) as a flight schedule.
4.	The airports are maintained with an airport code and airport (city) name
5.	Based on customer input, the relevant options are returned. Each record provides details of airline, connection id along with available occupancy.
6.	Airline is maintained in a separate file and airline id along with connection id is maintained in Flight schedule. The available occupancy is calculated based on the plane type maintained in flight class (by subtracting booked seats from max occupancy for a given travel class)
7.	Customer is asked to book a flight using the available options. 
8.	Customer can opt for any airline from the available options along with a travel class.
9.	Depending on an aircraft type customer might not be allowed to book a travel class if no seats are available for that specific class. Example if an aircraft type does not have a business class, customer cannot book a ticket for business class. Similarly, if the available occupancy is 0, customer cannot book a ticket using that option.
10.	A customer record must exist to book a ticket as ticket can only be issued against an existing customer ID. 
11.	Once a ticket is booked customer is issued an autogenerated booking ID
12.	Customer can modify or delete an existing booking by providing the booking ID
13.	Modification is allowed for another date with the same carrier (airline id + connection id) and customer can opt for a different travel class subject to availability.
14.	Customer should be able to search bookings by providing either customer id, email id or phone no (10-digit mobile no).

**Project Flow basics:**

The main screen offers a menu for various objects with submenu for each object. The submenu offers the option to interact with an object type. 

From submenu using switch ‘0’ it is always possible to navigate back to main menu. Main menu also provides switch for clear screen and exit the program via options ‘C’ and ‘X’ respectively.

The first 5 Menu Options in the project are used for CRUD operations on the Master Files used by the Application Owner and Airline Operators to store the information needed for a Customer prior to booking / modifying a flight. 

The data files created as a part of these Options available in the project are Airlines.dat, Airports.dat, Planes.dat, FlightSchedule.dat, Flights.dat, Customers.dat, Bookings.dat
