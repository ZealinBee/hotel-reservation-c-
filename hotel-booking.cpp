// Hi, my name is zhiyuan and this is my hotel reservation system. I'm aiming for a grade 5 because this program has all the instructed functions, and it has an extra function (change reservation). I have commented a lot in the program to ensure the readability and structured the program in a way that is understandable. I am satisfied with how the program turned out.

#include <iostream>
// For string
#include <string>
// For random
#include <cstdlib>
#include <ctime>
// For limits like INT_MAX
#include <limits>
#include <climits>
// Vector because I want to learn how it works
#include <vector>
// For setw
#include <iomanip>

// I use this for the endl, not the cout and cin, because doing merely cout and cin sometimes causes errors because of the conflict with other libraries
using namespace std;

// discount percentage constants
const float NO_DISCOUNT = 0;  // 0 percent
const float DISCOUNT_10 = .1; // 10 percent
const float DISCOUNT_20 = .2; // 20 percent

// room rate in euros
const int SINGLE_ROOM = 100;
const int DOUBLE_ROOM = 150;

// room struct, stores everything, i made sure to initialize everything with 0 or string()
struct Room
{
    int numberOfDays = 0;           // number of days
    double totalCost = 0;           // total cost
    int reservedNumber = 0;         // reserved number
    string roomType = string();     // single room or double room
    string reserverName = string(); // reservers name
};

// Number of Total Rooms, used vectors because I want to learn how vector works properly, put there as the maximum, I could put more but I don't have to.
vector<Room> rooms(300);

// I declared all the functions first, all the detailed comments about these functions will be inside the functions, so I won't comment this in details here.
float discount();                                                                                                                   // generates a random discount
int reservationNumber();                                                                                                            // generates a random reservation number
int introduction(int option);                                                                                                       // the intro of the program
void reserveRoom(int roomOption, int &totalNumberOfSingleRooms, int &totalNumberOfDoubleRooms, float discountPercent, int runTime); // the function that allows the user to reserve a room
int randomAmountOfRoomsGenerator();                                                                                                 // generates 40 - 80 even number of rooms
void optionInputValidation(int &enteredOption, int acceptableLength);                                                               // checks the input

int main()
{
    // Used in matching the reservation, you will see the details later
    Room matchedReservation;

    // Variables, I made sure to initalize everything here not in global
    int option = 0;                                                    // The option the user enters
    int roomOption = 0;                                                // either single room or double room
    int enteredReservationNumber = 0;                                  // used for matching reservation number
    string enteredReservationName = string();                          // used for matching reservation number
    float discountPercent = 0;                                         // the discount percentage, either 0 or 0.1 0r 0.2
    int totalNumberOfSingleRooms = randomAmountOfRoomsGenerator() / 2; // 40 - 80 rooms divide 2, always even number
    int totalNumberOfDoubleRooms = randomAmountOfRoomsGenerator() / 2; // 40 - 80 rooms divide 2, always even number
    bool isTheReservationMatched = false;                              // The reservation is not matched by default

    // This is declared because I want this number to increase this every time I the do while loop runs, and this number is inside the struct rooms[runTime] so that every single reservation will be made into a new struct and the previous struct will not be deleted, this allows the user to book several rooms and still be able to check reservation.
    int runTime = 0;
    // do while statement because it is nice for looping
    do
    {
        // The runtime increases by one everytime the program runs
        runTime++;
        // The intro of the program, located after line 200
        introduction(option);
        // The input validation gets the option and validates the input to make sure the input is valid, I put this function every time we accept an input. The function is located in the end of the program
        optionInputValidation(option, 5);
        // switch for the options entered
        switch (option)
        {
            // If the user wants to book something, then we ask for the room number first then the room type
        case 1:
            // Go to this function (after line 210) to see what this really do, I commented it there
            reserveRoom(roomOption, totalNumberOfSingleRooms, totalNumberOfDoubleRooms, discountPercent, runTime);
            break;
        case 2:
            // Reservation will not be matched by default
            isTheReservationMatched = false;
            // Asks for the reservation number and name from the user
            std::cout << "Enter your reservation number: ";
            optionInputValidation(enteredReservationNumber, 99999);
            cout << "Enter your reservation name: ";
            getline(std::cin, enteredReservationName);
            // Do a match, it will run through all the reservations in the app and see if both the reservation number and reservation name entered match with anything in the database
            for (int i = 0; i < runTime; i++)
            {
                if (enteredReservationNumber == rooms[i].reservedNumber && enteredReservationName == rooms[i].reserverName)
                {
                    // If it matches, it will break out of the for loop, and assign matchedReservation with the reserver name and number
                    isTheReservationMatched = true;
                    matchedReservation = rooms[i];
                    break;
                }
            }
            if (isTheReservationMatched == true)
            {
                std::cout << "Hi " << matchedReservation.reserverName << "! Your room type is " << matchedReservation.roomType << " and your total cost is " << matchedReservation.totalCost << ". " << endl;
                break;
            }
            else if (isTheReservationMatched == false)
            {
                std::cout << "Sorry, but the reservation is not found.";
                break;
            }
            break;
        case 3:
            // This is for matching the reservation again, because the user has to already have a room in order to change his reservation. The logic is the same with booking a reservation, but it deletes the original reservation and release the room type
            isTheReservationMatched = false;
            std::cout << "Enter your reservation number: ";
            optionInputValidation(enteredReservationNumber, 99999);
            cout << "Enter your reservation name: ";
            getline(std::cin, enteredReservationName);
            for (int i = 0; i < runTime; i++)
            {
                if (enteredReservationNumber == rooms[i].reservedNumber && enteredReservationName == rooms[i].reserverName)
                {
                    // If the reservation matches, I will delete the matched reservation because the user will be making a new reservation
                    rooms[i].reservedNumber = 0;
                    rooms[i].reserverName = string();
                    // If the old reservation was a single room, then we will add one more single room, and if it is a double room, we will add one more double room
                    if (rooms[i].roomType == "single room")
                    {
                        totalNumberOfSingleRooms++;
                    }
                    else if (rooms[i].roomType == "double room")
                    {
                        totalNumberOfDoubleRooms++;
                    }
                    isTheReservationMatched = true;
                    break;
                }
            }
            if (isTheReservationMatched)
            {
                // Let the user reserve the room again
                reserveRoom(roomOption, totalNumberOfSingleRooms, totalNumberOfDoubleRooms, discountPercent, runTime);
            }
            else if (!isTheReservationMatched)
            {
                std::cout << "The Reservation is not found, try again";
            }

            break;
        case 4:
            isTheReservationMatched = false;
            std::cout << "Enter your reservation number: ";
            optionInputValidation(enteredReservationNumber, 99999);
            cout << "Enter your reservation name: ";
            getline(std::cin, enteredReservationName);
            for (int i = 0; i < runTime; i++)
            {
                if (enteredReservationNumber == rooms[i].reservedNumber && enteredReservationName == rooms[i].reserverName)
                {
                    // If the reservation matches, I will delete the matched reservation
                    rooms[i].reservedNumber = 0;
                    rooms[i].reserverName = string();
                    // Add back the room
                    if (rooms[i].roomType == "single room")
                    {
                        totalNumberOfSingleRooms++;
                    }
                    else if (rooms[i].roomType == "double room")
                    {
                        totalNumberOfDoubleRooms++;
                    }
                    isTheReservationMatched = true;
                    break;
                }
            }
            if (isTheReservationMatched)
            {
                std::cout << "You have deleted your reservation successfully.";
            }
            else if (!isTheReservationMatched)
            {
                std::cout << "The Reservation is not found, try again";
            }
            break;
        case 5:
            // This simply just quits the program
            std::cout << "Thanks for using our program!";
            break;
            // If the user enters something invalid, it will tell the user about it, even though I already have input valdiation, this is here just in case something else goes run.
        default:
            std::cout << "You entered an invalid value, try again :)";
        };

    } while (option != 5);

    return 0;
}

int introduction(int option)
{
    std::cout << endl
              << "WELCOME TO ZHIYUAN's HOTEL BOOKING SYSTEM!" << endl;
    std::cout << "1. Make a reservation" << endl;
    std::cout << "2. Check your reservation" << endl;
    std::cout << "3. Change Reservation" << endl;
    std::cout << "4. Delete a Reservation" << endl;
    std::cout << "5. Quit Application" << endl;
    return option;
}

void reserveRoom(int roomOption, int &totalNumberOfSingleRooms, int &totalNumberOfDoubleRooms, float discountPercent, int runTime)
{
    // Takes in the room option, total number of single rooms and double room (referenced because I need them to update), the discount percent and the run time
    // Ask the user how many days they want to reserve
    std::cout << "How many days do you want to reserve? (no more than 20 days)" << endl;
    optionInputValidation(rooms[runTime].numberOfDays, 20);
    // Ask for the room type, single room and double room are available
    std::cout
        << "Would you like a: " << endl
        << "1. Single Room (100 EUR, " << totalNumberOfSingleRooms << " rooms left)" << endl

        << "2. Double Room (150 EUR, " << totalNumberOfDoubleRooms << " rooms left)" << endl;
    optionInputValidation(roomOption, 2);
    std::cout << "Thank you! Now We need your name, input your name " << endl;
    std::getline(std::cin, rooms[runTime].reserverName);
    // This depends on what room option(single or double) the user chose
    switch (roomOption)
    {
    case 1:
        if (totalNumberOfSingleRooms == 0)
        {
            std::cout << "There's no more single rooms";
        }
        else
        {
            // Calculates the discount percent from the function I"ve made
            discountPercent = discount();
            // Calculates the total cost based on a simple formula
            rooms[runTime].totalCost = rooms[runTime].numberOfDays * (SINGLE_ROOM - SINGLE_ROOM * discountPercent);
            // Tells the cost and discount percent
            std::cout << "Thank you " << rooms[runTime].reserverName << "! The total cost is " << rooms[runTime].totalCost << "." << endl
                      << "Your Discount was " << discountPercent * 100 << "%. " << endl;
            // Creates the reservation number based on the reservation number function, the chances of it making the same resevation number is small and we ask for the reservation name when checking the reservaion so it won't conflict
            rooms[runTime].reservedNumber = reservationNumber();
            // Tells the user their reservation number and name so that they can check their reservation
            std::cout << "Your reservation number is " << rooms[runTime].reservedNumber << " "
                      << "(Use this and your name to check your reservation)" << endl;
            rooms[runTime].roomType = "single room";
            totalNumberOfSingleRooms = totalNumberOfSingleRooms - 1;
        }

        break;
    case 2:
        if (totalNumberOfDoubleRooms == 0)
        {
            std::cout << "There's no more double rooms";
        }
        else
        {
            // Same logic with the single room, but instead it's double room
            discountPercent = discount();
            rooms[runTime].totalCost = rooms[runTime].numberOfDays * (DOUBLE_ROOM - DOUBLE_ROOM * discountPercent);
            std::cout << "Thank you " << rooms[runTime].reserverName << "! The total cost is " << rooms[runTime].totalCost << "." << endl
                      << "Your Discount was " << discountPercent * 100 << "%. " << endl;
            rooms[runTime].reservedNumber = reservationNumber();
            std::cout << "Your reservation number is " << rooms[runTime].reservedNumber << " "
                      << "(Use this to check your reservation)" << endl;
            rooms[runTime].roomType = "double room";
            totalNumberOfDoubleRooms = totalNumberOfDoubleRooms - 1;
        }
        break;
    default:
        std::cout << "Invalid input, try again";
    };
}

int randomAmountOfRoomsGenerator()
{
    // Generates a number from 40-80 with the srand and rand()
    srand(time(0));
    int randomAmountOfRooms = rand() % 40 + 40;
    // This function makes sure that the amount of room generated is actually even
    if (randomAmountOfRooms % 2 != 0)
    {
        randomAmountOfRooms += 1;
    }
    return randomAmountOfRooms;
}

// gets the discount rate randomly (0%, 10%, 20%)
float discount()
{
    // returns the discount, either 0 or 0.1 or 0.2
    //  some c++ magic that allows you to get a random Number everytime:
    srand(time(0));
    int randomNumber = rand() % 3;
    float randomDiscount;
    if (randomNumber == 0)
    {
        randomDiscount = NO_DISCOUNT;
    }
    else if (randomNumber == 1)
    {
        randomDiscount = DISCOUNT_10;
    }
    else if (randomNumber == 2)
    {
        randomDiscount = DISCOUNT_20;
    }
    return randomDiscount;
}

int reservationNumber()
{
    // Returns a reservation number 10000 - 99999
    srand(time(0));
    int randomReservationNumber = rand() % 90000 + 9999;
    return randomReservationNumber;
}

void optionInputValidation(int &enteredOption, int acceptableLength)
{
    // Takes in the entered option and acceptable length of the number to check if the entered option is valid
    // Validates input, set the width of the entered option to be the acceptable length, to make sure that the user don't enter more than what I want them to enter
    cin >> std::setw(1) >> enteredOption;
    // While the loop is true, it will keep running until the entered option is good and acceptable length
    while (true)
    {
        if (!cin.good() || enteredOption > acceptableLength || enteredOption == 0)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input, look at the above instruction" << endl;
            cin >> setw(1) >> enteredOption;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            return;
        }
    }
}
