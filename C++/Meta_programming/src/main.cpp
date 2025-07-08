#include <iostream>
#include <string>
#include  "math.hpp"

using namespace std;


int main(){
    
    /* Test Cases */

    std::string s0 {"Hello"};
    std::string s1 {"ll"};

    
   /* Template instantiation */
    cout << lib::sum(30,20,77,1,3.7) << "\n";
    cout << lib::sum(32.2,53.4) << "\n";
    cout << lib::sum(30) << "\n";
    cout << lib::sum() << "\n";

    cout << lib::sub(30,20,77,1,3.7) << "\n";
    cout << lib::sub(77.5,20) << "\n";
    cout << lib::sub(9) << "\n";
    cout << lib::sub() << "\n";

    cout << lib::max(30,20,77,1,3.7) << "\n";
    cout << lib::max(30,20) << "\n";
    cout << lib::max(30.8,3.7) << "\n";
    cout << lib::max(3) << "\n";
    cout << lib::max() << "\n";

    cout << lib::min(30,20,77,1,3.7) << "\n";
    cout << lib::min(1.7,3) << "\n";
    cout << lib::min(8) << "\n";
    cout << lib::min() << "\n";

    cout << lib::sub(s0,s1) << "\n";
    cout << lib::sum(s0,s1) << "\n";

}
