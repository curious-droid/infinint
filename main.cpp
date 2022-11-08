#include "infinint.h"
#include <iostream>

int main()
{
    infinint m=13; //automatic type conversion supported

    m++; //unary operators supported
    std::cout << m << "\n";
    m-= 20; //binary operators supported
    std::cout << m << "\n";
    std::cout << (m < infinint(-30)) << "\n"; //comparators supported
    std::cout << (m == infinint(-6)) << "\n"; 
    
    std::cin >> m; // instream supported for values up to long long
    std::cout << m << "\n"; //printing supported for values up to long long
    
}