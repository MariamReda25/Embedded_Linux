#include <iostream>
#include  "math.hpp"
using namespace std;
#include <string>

int main(){


    std::string s {"Hello"};
    std::string s2 {"mar"};

    cout << lib::sum(s,s2) << endl;
}
