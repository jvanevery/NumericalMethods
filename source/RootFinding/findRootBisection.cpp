// This will be an example of the bisection method for root finding
// I will use both the standard method, false position method, and modified false position method.

//I will also analyze convergence for each method

#include <cmath>
#include <iostream>
#include <matplot/matplot.h>

//We will look for a root of the function lambda*cosh(50/lambda) - lambda - 10
double func(double arg){
    using namespace std;
    return ((arg*cosh(50/arg)) - arg - 10);
}

int main(){
    //We will search over the interval [50,150]
    //We will do this iteratively instead of recursively

    //Tolerance for difference between iterations
    double tolerance = 0.0001;
    double diff = 1;

    double a = 50;
    double b = 150;

    double fofa = func(a);
    double fofb = func(b);

    
    if(fofa == 0){
        return a;
    }

    if(fofb == 0){
        return b;
    }

    //Check that the function is positive on one side and negative on the other
    if(fofa*fofb > 0){
        throw 0;
    }

    // Will set these in each iteration. Start c = NaN so that the loop must run at least once
    double c = NAN;
    double cPrior;
    double fofc;

    while(tolerance < diff){
        cPrior = c;
        c = a + (b - a)/2;
        fofc = func(c);

        if(fofa > 0){
            if(fofc >0){
                a = c;
            }
            else{
                b = c;
            }
        }
        else{
            if(fofc < 0){
                a = c;
            }
            else{
                b = c;
            }
        }

        diff = std::abs(c - cPrior);
    }

    std::cout << "root = " << c << "     Precision determined to a tolerance of " << tolerance;
    return c;
}