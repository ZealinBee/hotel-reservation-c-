#include <iostream>
#include <string>
// For random
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>
#include <climits>
#include <vector>
using namespace std;

// discount percentage constants
const float NO_DISCOUNT = 0;  // 0 percent
const float DISCOUNT_10 = .1; // 10 percent
const float DISCOUNT_20 = .2; // 20 percent

// room rate
const int SINGLE_ROOM = 100;
const int DOUBLE_ROOM = 150;

// room struct

struct Room
{
    double numberOfDays;
    double totalCost;
    double reservedNumber;
    string roomType;
    string reserverName;
};

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
    int randomReservationNumber = rand() % 89999 + 9999;
    return randomReservationNumber;
}

int getChoice()
{
    int choice = 0;

    return choice;
}

int introduction()
{
    int option;
    cout << endl
         << "WELCOME TO ZHIYUAN's HOTEL BOOKING SYSTEM!" << endl;
    cout << "1. Make a reservation" << endl;
    cout << "2. Check your reservation" << endl;
    cout << "3. Change Reservation" << endl;
    cout << "4. Quit Application" << endl;

    return option;
}

int main()
{

    // Number of Total Rooms, used vectors so that I don't have to set an array number.
    vector<Room> rooms(5);
    // Used in matching the reservation
    Room matchedReservation;

    // Useful variables
    int roomOption;
    int option;
    int enteredReservationNumber;
    float discountPercent;
    int totalNumberOfSingleRooms = 40;
    int totalNumberOfDoubleRooms = 40;
    bool isTheReservationMatched = false;

    // This is to aid the struct, this is declared because I want this number to increase everytime I run the do while loop, and this number is inside the object rooms[runTime] so that every single reservation will be made into a new object and the previous objects will not be deleted
    int runTime = 0;

    // do while statement because it is good for input validation
    do
    {
        runTime += 1;
        // The intro basically
        introduction();
        std::cin >> option;
        // If the user enters a letter then the program just complains (not final because I want the program to rerun)
        if (cin.fail())
        {
            cout << "Invalid input, try again.";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        // switch for the options entered
        else
        {
            switch (option)
            {

            // If the user wants to book something, then we ask for the room number first then the room type
            case 1:
                cout << "How many days do you want to reserve?" << endl;
                std::cin >> rooms[runTime].numberOfDays;
                cout << "Would you like a: " << endl
                     << "1. Single Room (100 EUR, " << totalNumberOfSingleRooms << " rooms left)" << endl

                     << "2. Double Room (150 EUR, " << totalNumberOfDoubleRooms << " rooms left)" << endl;
                std::cin >> roomOption;

                cout << "Thank you! Now We need your name, input your name " << endl;
                cin.ignore();
                std::getline(std::cin, rooms[runTime].reserverName);
                switch (roomOption)
                {
                case 1:
                    if (totalNumberOfSingleRooms == 0)
                    {
                        cout << "There's no more single rooms";
                    }
                    else
                    {
                        discountPercent = discount();
                        rooms[runTime].totalCost = rooms[runTime].numberOfDays * (SINGLE_ROOM - SINGLE_ROOM * discountPercent);
                        cout << "Thank you " << rooms[runTime].reserverName << "! The total cost is " << rooms[runTime].totalCost << "." << endl
                             << "Your Discount was " << discountPercent * 100 << "%. " << endl;
                        rooms[runTime].reservedNumber = reservationNumber();
                        cout << "Your reservation number is " << rooms[runTime].reservedNumber << " "
                             << "(Use this to check your reservation)" << endl;
                        rooms[runTime].roomType = "single room";
                        totalNumberOfSingleRooms = totalNumberOfSingleRooms - 1;
                    }

                    break;

                case 2:
                    if (totalNumberOfDoubleRooms == 0)
                    {
                        cout << "There's no more double rooms";
                    }
                    else
                    {
                        discountPercent = discount();
                        rooms[runTime].totalCost = rooms[runTime].numberOfDays * (DOUBLE_ROOM - DOUBLE_ROOM * discountPercent);
                        cout << "Thank you " << rooms[runTime].reserverName << "! The total cost is " << rooms[runTime].totalCost << "." << endl
                             << "Your Discount was " << discountPercent * 100 << "%. " << endl;
                        rooms[runTime].reservedNumber = reservationNumber();
                        cout << "Your reservation number is " << rooms[runTime].reservedNumber << " "
                             << "(Use this to check your reservation)" << endl;
                        rooms[runTime].roomType = "double room";
                        totalNumberOfDoubleRooms = totalNumberOfDoubleRooms - 1;
                    }

                    break;
                default:
                    cout << "Please enter a valid value :)";
                };
                break;

            case 2:
                isTheReservationMatched = false;

                cout << "Enter your reservation number: ";
                std::cin >> enteredReservationNumber;
                // Do a match
                for (int i = 0; i < runTime; i++)
                {
                    if (enteredReservationNumber == rooms[i].reservedNumber)
                    {
                        isTheReservationMatched = true;
                        matchedReservation = rooms[i];
                        break;
                    }
                }

                if (isTheReservationMatched == true)
                {
                    cout << "Hi " << matchedReservation.reserverName << "! Your room type is " << matchedReservation.roomType << " and your total cost is " << matchedReservation.totalCost << ". " << endl;
                    break;
                }
                else if (isTheReservationMatched == false)
                {
                    cout << "The reservation is not found, try again";
                    break;
                }

                break;
            case 3:
                isTheReservationMatched = false;
                cout << "Enter your reservation number: ";
                cin >> enteredReservationNumber;
                for (int i = 0; i < runTime; i++)
                {
                    if (enteredReservationNumber == rooms[i].reservedNumber)
                    {
                        // rooms[i].reservedNumber = NAN;
                        isTheReservationMatched = true;
                        break;
                    }
                }
                if (isTheReservationMatched == true)
                {
                    cout << "How many days do you want to reserve?" << endl;
                    std::cin >> rooms[runTime].numberOfDays;
                    cout << "Would you like a: " << endl
                         << "1. Single Room (100 EUR, " << totalNumberOfSingleRooms << " rooms left)" << endl

                         << "2. Double Room (150 EUR, " << totalNumberOfDoubleRooms << " rooms left)" << endl;
                    std::cin >> roomOption;
                }
                else if (isTheReservationMatched == false)
                {
                    cout << "The Reservation is not found, try again";
                }

                break;
            case 4:
                cout << "Thanks for using our program!";
                break;
            default:
                cout << "You entered an invalid value, try again :)";
            };
        }

    } while (option != 4);
}
