# hotel-reservation-c++
# A hotel reservation system built with c++
TAMK HOTEL RESERVATION SYSTEM C++
The program only uses 600kb of memory in the stack! (probably because of vectors? I didn’t really try to optimize the program) 
This reservation program allows the user to book a room, check their reservation with their reservation number and name (need both the number and name because that’s how real hotel does it, I want it to seem a bit more professional). And the user has the right to change the reservation by inputing their reservation number and name. And of course, the user has the option to delete the reservation. By the way, the user can’t just select the room number they want to book, because it makes no sense to me, I have never been to a hotel where I can choose what room number I want to be in. But obviously, the room type (single or double) is bookable.
This is how it looks like in the beginning:
### WELCOME TO ZHIYUAN's HOTEL BOOKING SYSTEM!  
1. Make a reservation
2. Check your reservation
3. Change Reservation
4. Quit Application  
The user will enter a number, from 1 – 4, if the user enters something invalid like many letters or too much input ,then the program will tell the user that they are putting the wrong input and need to put the correct input. The program will not crash from wrong inputs, because I built a input validation system function and validate every input entered.  
When you make a reservation, the program will ask you for the room type, whether it is single room or double room, there is a random number of rooms generated every time, from 40 – 80 even number of rooms. And the number of rooms will decrease everytime the user successfully book a room.
Here is what happens when you book a room :  
How many days do you want to reserve? (no more than 20 days)  
13  
Would you like a:   
1.Single Room (100 EUR, 30 rooms left)  
2.Double Room (150 EUR, 30 rooms left)  
1  
Thank you! Now We need your name, input your name  
zhiyuan liu  
Thank you zhiyuan liu! The total cost is 1170.  
Your Discount was 10%.   
Your reservation number is 58915 (Use this to check your reservation)  

The discount is also random.  
When you click check reservation, here is what happens:  
Enter your reservation number: 58915  
Enter your reservation name: zhiyuan liu  
Hi zhiyuan liu! Your room type is single room and your total cost is 1170.    
Of course, the user has the right to book multiple rooms, the program will store all of them, and you will be able to check the room with your reservation number and name.  

Note: Every input has an input valiation built in, so it will not be easily broken by wrong input.  
Changing the reservation will enable the user to change the reservation, it will ask the user for the reservation number and ask the user to enter a new set of information.  
When you click change reservation, here is what happens:  
Enter your reservation number: 33927  
Enter your reservation name: zhiyuan liu  
How many days do you want to reserve? (no more than 20 days)  
2  
Would you like a:  
1. Single Room (100 EUR, 28 rooms left)  
2. Double Room (150 EUR, 28 rooms left)  
1  
Thank you! Now We need your name, input your name   
zhiyuan liu  
Thank you zhiyuan liu! The total cost is 200.  
Your Discount was 0%.   
Your reservation number is 97419 (Use this and your name to check your reservation)  
The program basically ask the user to book a room again after asking for the reservation number and name. But the difference is, it deletes the original room the user had, and released the room count for the room type.   

Lastly delete reservation, exactly the same with change reservation, without the reserving again.  
It will look like this:  
Enter your reservation number: 33927  
Enter your reservation name: zhiyuan liu  
Your reservation was deleted successfully.  
