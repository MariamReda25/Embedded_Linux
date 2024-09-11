/*                                  * Sign-Up Application *                                           
Description : 
    we're going to be writing a user registration application. 
    This will allow users to register with the system, providing both their name and age, 
    and we'll store this information in our own custom type. 
    We'll also provide the ability for a user to be looked up by an ID, retrieving their information.

Author : Mariam Reda
*/

/***************************************** Dependency *********************************************/
#include <iostream>
#include <string> 
#include <vector>
/***************************************** Declerations *********************************************/
/* Class that will represent a record in the system*/
class Person {

 public:
 unsigned int ID = 0;
 std::string  Name;
 unsigned Age = 0;

};

/* Enum that will represent options of system*/
typedef enum {

ADD_RECORD=1,
FETCH_RECORD,
QUIT

}option;

/*** Function decleration : ***/

/* Description :
     Function Print Application Main Messages.
*/
void MainMessage (void);

/* Description:
     Overloading stream extraction (>>) operator in C++ .
*/
std::istream& operator>>(std::istream& in , option& user_option);

/* Description: 
      Function Used to add new user's record 
      Input : User Name - User Age
      Output: Create New record and assign ID for new User
*/
void AddRecord (std::string Name , unsigned int Age);

/* Description:
      Function Used to get user data
      Input : User ID
      Output: Return the record for that user
*/
void Fetch_Record (unsigned int ID);

/* declare global vector of "Person" type to store input records.*/
std::vector<Person> Records;

/* Entry Point ( main Function )*/
int main () {

/* Local Variables : */

/*used to get input user name (Add record case)*/
std::string InputName;  
/*used to get input user age (Add record case)*/
unsigned int InputAge=0;
/*used to get input user ID (Fetch Case)*/
unsigned int InputID=0;

/* variable of type enum to get user's required option*/
option User_Option;

bool IsRunning = true;

 std::cout << " User SignUp Application \n";

while (IsRunning)
{   
    /* Display Main Options Message*/
     MainMessage ();
     
    /* get User's required option*/
     std::cin >>User_Option;

    /* Based on User's input Option application will react*/
    switch (User_Option)
    {
    /* Case 1: Add new record */
    case ADD_RECORD:
        std::cout << "\nAdd User , Please Enter User name and Age. \n";

        std::cout << "Name : ";
        std::getline( std::cin >> std::ws, InputName);
        
        std::cout << "Age : ";
        std::cin >> InputAge;

        AddRecord (InputName,InputAge);
        std::cout << "\n";
    break;

    /* Case 2: Fetch record */
    case FETCH_RECORD:
        std::cout << "\nPlease Enter User ID:\n";
        
        std::cout << "User ID : ";
        std::cin >> InputID;

        Fetch_Record(InputID);
        std::cout << "\n \n";
    break;

    /* Case 3: Quit from system */
    case QUIT: 
     IsRunning = false;
     std::cout << "Exit \n";
    break;

    /* default Case: invalid input */
    default:
      std::cout << "Invalid Option \n \n";
    break;

    }
}
  return 0;
}

/*** Functions defenation : ***/

/* Description :
     Function Print Application Main Messages.
*/
void MainMessage (void) {

    std::cout << "Please Select an Option \n";
    std::cout << "1: Add Record\n";
    std::cout << "2: Fetch Record\n";
    std::cout << "3: Quit\n\n";
    std::cout << "Enter Option : ";

}
/* Description:
     Overloading stream extraction (>>) operator in C++ .
*/
std::istream& operator>>(std::istream& in , option& user_option){

     int int_UserOption = 0;
     in >>int_UserOption;
     user_option = static_cast <option> (int_UserOption);
     return in;
}
/* Description: 
      Function Used to add new user's record 
      Input : User Name - User Age
      Output: Create New record and assign ID for new User
*/
void AddRecord (std::string Name , unsigned int Age){
  
  static unsigned int UserID = 0;
  Person User;

   User.Age = Age;
   User.Name = Name;
   User.ID = UserID++;

   Records.push_back(User);
  
  std::cout << "\nUser record Added Successfully\n";
  return;

}
/* Description:
      Function Used to get user data
      Input : User ID
      Output: Return the record for that user
*/
void Fetch_Record (unsigned int ID) {

   for (Person i : Records){
       
       if (i.ID == ID) {
          std::cout << "User Name: " << i.Name;
          std::cout << "\nUser Age: "  <<i.Age;
          return;
       }
   }
  
  std::cout << "User is not exist \n";
  return; 
   
}

