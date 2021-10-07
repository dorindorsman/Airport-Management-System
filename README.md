# Airport-Menegment-System
A system for managing flight data around the world, for a particular airline.

Airport, for which we will keep: 

1.Airport Name

2.Name of the country in which it is located

3.Its code in ITA is exactly a 3-character (unique) string

Functions:  

1. A function that receives 2 pointers to airports and returns 1 If they are the same otherwise 0, the test will be performed according to the code in ITA. 

2.Function that receives an airport pointer and code and returns 1 if the resulting airport code is the same as the accepted airport code otherwise the function returns 0.

3.Additional functions require detail below.

Airport Manager, for which we will keep:

The airport authority structure will be so that airports are kept on a linked list as an airport pointer.  
The list of airports should always be sorted according to the airport code i.e. charging as well as adding another airport. 

1.The array of all airports in the program (not a pointer but an airport)
2.Number of airports in the program

Functions:

1.Add an airport

2.Finding an airport by code. The function will receive a code and return a pointer to an airport located in the authority's airport system. 

3.Additional functions require detail below

Airport name reception:
The user must receive a string indicating the name of the airport. This name can consist of a few words.
After you receive the name from the user, the name must be changed to meet the following rules:

1.The first letter of each word will be the letter of size except in the last word where the first letter will be small. If there's only one word in the name, it'll start with a big letter.

2.Between each pair of words there will be 2 spaces accurately. 

3.There must be no space at the beginning and end of the name.

4.If a word named Chariot from an even number of letters of the first letter is large, the second letter is smaller, and thus alternatively until the word is finished even if it is the last word.


Flight, for which we will save:

1.The airport code from which she takes off.

2.Destination airport code (destination cannot be the airport from which it took off)

3.An integer representing the departure time (in this system, for simplicity, flights are only on the round hours, make sure the value is between 0 and 23). 

4.Date structure: day, month, year. Date integrity must be verified

Functions: 

1.A function that accepts a flight and a source airport code and a destination airport code and checks whether it is a flight to the received destinations. 

2.A function that receives an array of voters for flights and the size of a source airport code and a destination airport code and returns how many flights exist on this line.

3.Additional functions require detail below

Date reception:

The departure date will be received from the user in the following format dd/mm/yyyy (verify the integrity of the format). The string must be converted to a date structure. Make sure the date is valid. It should also be checked that the number of the day is valid in the number of months received. It is safe to assume there are always 28 days in February. Let's say April 31 is an illegal date.
Airline, for which we will keep:
At the airline - a linked list that keeps all dates on which flights exist without duplicates as a char*string. (There is no obligation to sort).) When printing the airline's information, print the date list must be added 

1.The name of the company.

2.The amount of her flights.

3.Its flight system - we'll keep as voters for flights - can be assumed that when you create an airline it doesn't have flights.

The airline allows its flight system to be sorted according to the following fields:
hour
Date
Departure Airport Code (Bonus)
Airport code of landing (bonus)

In order for us to know by which field the flights are sorted, we will add an appropriate feature to the airline (enum that will also contain the option that the array is not sorted). At first, the flight system was not sorted at all.

Functions:

1.Add a flight.

2.A function that receives from the user (asks the user) a source airport code and a destination airport code and prints how many flights the company has on this line. 

3.Additional functions require detail below.


Main program:

At the beginning of the program, we will reboot the system by loading the AIRPORTS authority data from a text file and the airline from a binary file. It is important if the order of reading is important.  If one or both files do not exist, the Airports Authority and the airline must be initialized from the user
Please note: There are two dynamically assigned arrays: an airport system at the Airports Authority, and an array of voters for airline flights. 

There is a menu that allows the following displayed:
Add a flight to the airline. To find the src and dest airports of the flight in the database of existing airports in the Airports Authority the user will enter the IATA code of the in-flight airports.
Add an airport to the airport authority. Make sure there is no airport in the system anymore.
Sort flights by a given attribute in ascending order (internal menu according to the entries of the enum-).
Airline flight search by feature in which array is sorted 
Prints the airline's data. that includes printing all flights 
Printing the Data of the Israel Airports Authority – which includes printing all airports
Prints several existing flights to the airline between 2 airports.
Exit the program. Be sure to release any memory that is dynamically allocated.
When exiting the program, the airline's data must be saved to a binary and airport authority file to a text file.

General notes:

The length of all strings is unknown unless a specific length (airport code) is specified. But you can temporarily set a string of 255 characters.
Input integrity checks must be strictly observed.
Const pointers must be taken care of when the function does not change values in the pointer.
make sure that each airport's IATA code is unique when receiving, otherwise print an error message, plus make sure it's exactly 3 years long and contains only capital letters.

Text files:

We will save the airport authority data to a text file 
The file will be saved under the name "airport_authority.txt".

Format writing the Airports Authority as a text file:
[Airport quantity]
[Airport 1]
[Airport 2]
.
..
[Airport n]

When each airport is saved in the following format:
[Airport Name]
[Country]
[IATA Code] 

binary files:

We will save the airline's data to a binary file called company.bin".

Binary file airline write format:
[Number that represents the length of the airline's name including '\0'] ]
[Airline Name]
[Flight quantity]
[Sort method – (Enum numeric value)]    
[Flight 1]
[Flight 2]
...
[Flight n]

When each flight is saved in the following format:
[Source IATA]
[Destination IATA]
[Flight Hour]
 [Date: 3 int]

Generic function that handles the array, "generalArrayFunction". The function will receive an array, number of organs in an array, the size of each organ in bytes, and a pointer to the function
 ; void f(void* element)
: This function should be activated in the following cases
Prints the flight array. 
Release of airline flight system.

qsort:
You must add ascending order sorting capability to the airline's flight system. You can sort by:
hour
Date
Departure Airport Code 
Airport code of landing 

bsearch:
It is necessary to add search capability in the flight system at the airline according to the parameter by which they are sorted, binary search should be used in the library function: bsearch, if the array is not sorted, the user cannot be notified that a search cannot be performed.


 

