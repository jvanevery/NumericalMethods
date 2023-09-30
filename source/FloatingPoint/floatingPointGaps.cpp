//Plot that shows the exponential behavior of the gaps between the floating point numbers
//We will use 32 bit floats

// The gaps between floating point numbers grow exponentially, but it is important to note
// that the "relative error" when rounding a number to its nearest floating point neighbor
// is actually contant. That is because even though the gaps get larger with larger exponent
// the floating point numbers get larger with the same scaling.

// The floating point gaps of the same exponent are often referred to as a "unit in the last place"

// The relative error from rounding is actually a factor of 1/2 smaller than machine epsilon
// because when rounding to the nearest fp number we will have to traverse less than half the
// gap distance

//    A-----------x--------------------B
// we can see that if A and B are x's nearest floating point neighbors, that x is at most 
// half the gapsize away from its nearest neighbor

// For 32 bit fp the relative error from rounding is 2^-24
// For 64 bit fp the relative error from rounding is 2^-53

#include <cmath>
#include <iostream>
#include <matplot/matplot.h>


int main(){

    double maxPower64 = 1023;
    double gapExponent64 = 52;

    std::vector<double> q = matplot::iota(-maxPower64 + 1, 1, maxPower64);
    
    std::vector<double> gapsizes;
    double temp = 0;
    for(double i :  q){
        temp = std::pow<double>(2,i - gapExponent64);
        gapsizes.push_back(std::log2(temp));
    }

    // For some reason if I use the matplot::semilogy here instead of taking the log myself,
    // the log of the gapsizes with negative exponent are set to inf or NaN?
    matplot::plot(q, gapsizes);
    matplot::title("Floating point Gap Distance vs. Exponent");
    matplot::xlabel("exponent q where -1022 <= q <= 1023");
    matplot::ylabel("log(Distance(q))");

    matplot::show();

    return 0;
}

