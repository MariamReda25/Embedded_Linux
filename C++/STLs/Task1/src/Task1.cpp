/************************* Managinga Bakery's Daily Orders ************************
 * Creating a simple program to helpa bakery manage its daily orders using vectors.
 * This Task demonstrate how to use vector and it's Functionalities to :
 *     1- Add new Orders to the end of list
 *     2- Find and Remove sepecifi Order
 *     3- Print information from Order list based on User's Option
 */
/************************** Include dependancies**************************/
#include <iostream>
#include <vector>
#include <array>
#include <string>

using namespace std;
/***************************** Declerations*******************************/
#define INITIAL_SIZE 5

/* global list of orders */
vector<vector<string>> today_orders;

/************************ Function Prototypes*****************************/
/* Description : 
*    Function Display Main menue Options 
*/
void display_main(void);
/* Description: 
*    Function use to add new customer order by ask him/her to add needed items.
*    Take customer_order (vector) to add items on it.
*/
void add_new_order(vector<string> &customer_order);
/* Description : 
*    Function Check if order number is exist or contain items.
*    Take  order_number and check on it then return bool value.
*/
bool is_exist(int order_number);
/* Description : 
*    Function Display Information about Orders based on User's Option. 
*/
void print_order(void);
/* Description : 
*    Function search about smallest order which have min. number of items in order list.
*     return index of Order in list
*/
int minimum_order (void);
/* Description : 
*    Function search about largest order which have max. number of items in order list.
*     return index of Order in list
*/
int maximum_order (void);
/****************************Entry Point**********************************/
int main()
{   
/***********************Variables Declerations****************************/

    vector<string> customer_order;
    bool Is_Running = true;
    int n_orders = 0;     // variable to track number of orders
    int order_number = 0;  
    char choice;

/***************************Application Logic ****************************/
    do
    {
        display_main();
        cin >> choice;
        switch (choice)
        {
        case 'N':
        case 'n':
        {
            add_new_order(customer_order);
            if (! customer_order.empty()){
             today_orders.push_back(customer_order);
             cout << "Order Number " << n_orders+1 << " is added successfully\n";
             customer_order.clear();
             n_orders++;
             if (n_orders % INITIAL_SIZE == 0)
                today_orders.resize(n_orders + INITIAL_SIZE);
            }
        }
        break;
        case 'R':
        case 'r':
        {
            cout << "Enter Order Number to be removed: ";
            cin >> order_number;
            if (is_exist(order_number))
            {
                today_orders.erase(today_orders.begin() + (order_number - 1));
                today_orders.shrink_to_fit();
                cout << "Order number " << order_number << " is removed successfully\n";
            }
            else
            {
                cout << "Invalid Order Number, This order not exist\n";
            }
        }
        break;
        case 'P':
        case 'p':
        {   
            if (today_orders.empty())
            {
                cout << "Empty Order List\n";
            }
            else
            {
                print_order();
            }
        }
        break;
        case 'q':
        case 'Q':
          today_orders.clear();
          if(today_orders.empty()){
              cout<< "**** End of The Day *****";
              Is_Running = false;
          } else {
            cout << "Your List is not empty";
          }

        }

    } while (Is_Running);
}
/***************************** Function definitions**************************/
/* Description : 
*    Function Display Main menue Options 
*/
void display_main(void)
{
    cout << "*** Welcome to Bakery at New Day *** \n";
    cout << "Add New Order (n-N)\n";
    cout << "Remove Specific Order (r-R)\n";
    cout << "Print Order (p-P)\n";
    cout << "End Of the Day (q-Q)\n";
    cout << "Enter Your Choice : \n";
}
/* Description: 
*    Function use to add new customer order by ask him/her to add needed items.
*    Take customer_order (vector) to add items on it.
*/
void add_new_order(vector<string> &customer_order)
{
    char choice = 0;
    string item = "";
    do
    { 
        cout << "Enter (n-N) for new item or (m-M) For menu\n";
        cin >> choice;
        switch (choice)
        {
        case 'N':
        case 'n':
             cout << "Enter Your needed item:";
             cin >> item;
             customer_order.push_back(item);
         break;

        default:
             cout<< "Invalid Option\n";
            break;
        } 
    } while (choice != 'M' && choice != 'm');
}
/* Description : 
*    Function Display Information about Order List based on User's Option. 
*/
void print_order(void)
{

    int n_choice;
    int order_number;
    cout << "1- Specific nth Order\n";
    cout << "2- All orders\n";
    cout << "3- First Order\n";
    cout << "4- Last Order\n";
    cout << "5- Analysis of Order List\n";
    cout << "6- Minimun Order\n";
    cout << "7- Maximum Order\n";
    cout << "8- Menu \n";
    cout << "Enter Your Choice: ";
    cin >> n_choice;
    switch (n_choice)
    {
    case 1:
        cout << "\nEnter Order Number: ";
        cin >> order_number;
        if (is_exist(order_number))
        {
            for (auto it = today_orders[order_number - 1].rbegin(); it != today_orders[order_number - 1].rend(); it++)
            {
                cout << *it << " ";
            }
        }
        else {
            cout << "Invalid Order Number, This order not exist";
        }
         cout << "\n";
        break;

    case 2:
        for (int i = 0; i < today_orders.size(); i++)
        {
            cout << "Order Number " << i + 1 << "\n\t";
            for (auto it = today_orders[i].begin(); it != today_orders[i].end(); it++)
            {

                cout << *it << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        break;
    case 3:
        cout << "First Order : \n\t";
        for (int i = 0; i < today_orders.front().size(); i++)
        {
            cout << today_orders.front()[i] << " ";
        }
        cout << "\n";
        break;
    case 4:
        cout << "Last Order : \n\t";
        for (int i = 0; i < today_orders.back().size(); i++)
        {
            cout << today_orders.back()[i] << " ";
        }
        cout << "\n";
        break;
    case 5:
         cout<< "Number of Orders in Order List " << today_orders.size()<< "\n";
         cout<< " Capacity of Order List " << today_orders.capacity() << "\n";
         cout<< "Reminanig Size to Expand List  " <<today_orders.max_size()<< "\n";
    case 6:{
        int min_order = minimum_order();
         cout << "Minimum Order : \n\t";
         for (auto it = today_orders[min_order].begin(); it != today_orders[min_order].end(); it++){
             cout<< *it << " ";
         }
         cout<<"\n";
        }
     break;
    case 7: {
         int max_order = maximum_order();
         cout << "Maximum Order : \n\t";
         for (auto it = today_orders[max_order].begin(); it != today_orders[max_order].end(); it++){
             cout<< *it << " ";
         }
         cout<<"\n";
        } 
        break;
    case 8:
         return;
    default:
        cout << "Invalid Choice";
    }
}
/* Description : 
*    Function Check if order number is exist or contain items.
*    Take  order_number and check on it then return bool value.
*/
bool is_exist(int order_number)
{

    if (order_number > today_orders.size() || today_orders[order_number - 1].empty())
    {
        return false;
    }
    return true;
}
/* Description : 
*    Function search about largest order which have max. number of items in order list.
*     return index of Order in list
*/
int maximum_order (void){

    int max_order = today_orders[0].size();
    for (auto i = 1; i < today_orders.size(); i++){

        if (today_orders[i].size() > max_order){
             max_order = i;
        }
    }

    return max_order;

}
/* Description : 
*    Function search about smallest order which have min. number of items in order list.
*     return index of Order in list
*/
int minimum_order (void){

    int min_order = today_orders[0].size();
    for (auto i = 1; i < today_orders.size(); i++){

        if (today_orders[i].size() < min_order){
             min_order = i;
        }
    }

    return min_order;

}