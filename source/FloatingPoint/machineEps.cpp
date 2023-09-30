// Simple test of machine epsilon for 32 and 64 floating point numbers

#include <cmath>
#include <iostream>

int main(){

    //32 bit floating point number
    std::cout << "\nTesting machine epsilon for a 32 bit floating point number\n";

    //2^-23 = 1.1920929 * 10 ^ -7
    float eps32 = std::pow<float>(2,-23);

    //2^-24 = 5.96046 * 10 ^ -8
    float smallerThanEps32 = std::pow<float>(2,-24);

    float x = static_cast<float>(1);
    float y = static_cast<float>(1) + eps32;

    std::cout << "\n epsilon = " << eps32 << "...\n";
    std::cout << "1 = 1 + e is " << std::boolalpha << (x==y);

    y = static_cast<float>(1) + smallerThanEps32;
    std::cout << "\n";

    std::cout << "\n epsilon = " << smallerThanEps32 << "...\n";
    std::cout << "1 = 1 + e is " << std::boolalpha << (x==y);


    //64 bit floating point number
    std::cout << "\nTesting machine epsilon for a 64 bit floating point(double) number\n";

    //2^-52
    double eps64 = std::pow<double>(2,-52);

    //2^-53
    double smallerThanEps64 = std::pow<double>(2,-53);

    double q = 1;
    double r = 1 + eps64;

    std::cout << "\n epsilon = " << eps64 << "...\n";
    std::cout << "1 = 1 + e is " << std::boolalpha << (q==r);

    r = 1 + smallerThanEps64;
    std::cout << "\n";

    std::cout << "\n epsilon = " << smallerThanEps64 << "...\n";
    std::cout << "1 = 1 + e is " << std::boolalpha << (q==r);

    return 0;
}