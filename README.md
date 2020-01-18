# FlightReservationForClassXII
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

**Binary search is used to validate airport id or airline id entries made by user during various inputs.**

