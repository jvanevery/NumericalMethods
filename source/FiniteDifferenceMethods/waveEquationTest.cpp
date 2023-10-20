/** Testing using central difference approximations for second order differentials to compute a numerical solution to the 1D wave equation:
 * d2f/dx2 = c*d2f/dt2
 * 
 * We will be letting c = 1
 * 
 * Central difference approximiations will have a truncation error of O(h^2) where h is the step-size. Stability of the method
 * is only gauranteed if k^2/h^2 < 1, where k is the time step size and h is the spatial step size.
 * 
 * Initial conditions and boundary conditions must be provided to solve
 * **/

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <matplot/matplot.h>
#include <vector2d.h>

//Solution was stored in a 1d vector, this method will parse it into a 2d one of specificed dimensions
std::vector<std::vector<double>> solution_to_vector_2d(std::vector<double>::iterator ptr, int rows, int columns){

    std::vector<std::vector<double>> solution_as_vector_2d;

    for(int i=0; i<rows; i++){
        std::vector<double> next_row;
        for(int j=0; j<columns; j++){
            next_row.push_back(*ptr);
            std::advance(ptr, 1);
        }
        solution_as_vector_2d.push_back(next_row);
    }

    return solution_as_vector_2d;
}

//Finite difference formula for calculating the solution at the next timestep
double finite_difference(double f_xplush, double f_xminh, double f, double f_tmink, double rho){
    return rho*f_xplush + 2*(1-rho)*f + rho*f_xminh - f_tmink;
}

//Finite difference for calculating solution of the 1st (after 0th) time step of solution. 
double finite_difference_first_row(double f_xplush, double f_xminh, double f, double rho){
    return 0.5*rho*(f_xplush+f_xminh) + (1-rho)*f;
}

int main(){

    //Set bounds and stepsizes
    const double ti = 0;
    const double tf = 5;
    const double xleft = 0;
    const double xright = 1;
    const double tstep = 0.05;
    const double xstep = 0.1;
    const double rho = std::pow(tstep,2)/std::pow(xstep,2);

    //initialize solution space. It's stored as a vector but will be parsed as a matrix
    std::vector<double> solution;

    /**Initial coniditons and boundary conditions
     * IC: f(x,0) = sin(pi*x)
     *     f'(x,0) = 0
     * BC: f(xleft,t) = 0, f(xright,t) = 1
     * */
    const double left_bound = 0;
    const double right_bound = 0;
    std::vector<double> timemesh = matplot::iota(ti, tstep, tf);
    std::vector<double> spacemesh = matplot::iota(xleft, xstep, xright);


    //IC: f(x,0) (start 0th row)
    solution.push_back(left_bound);

    //IC: f(x,0) (0th row)
    //Basic sin wave that satisfies BCs
    for(int i=1; i<spacemesh.size()-1; ++i){
        solution.push_back(std::sin(M_PI*spacemesh.at(i)));
    }

    //IC: f(x,0) (end 0th row)
    solution.push_back(right_bound);

    //BC: (start 1st row)
    solution.push_back(0);

    //IC: f'(x,0)
    for(int i=0; i<spacemesh.size()-2; ++i){
        solution.push_back(finite_difference_first_row(
            solution.at(i+2),
            solution.at(i),
            solution.at(i+1),
            rho
        ));
    }

    //BC (end 1st row)
    solution.push_back(0);

    //Fill in remaining rows with 5 point finite difference forumla. Index starts at 2 because first 2 rows of solution are filled
    
    for(int i=2; i<timemesh.size(); ++i){
        //Start each row with BC
        solution.push_back(left_bound);
        for(int j=1; j<spacemesh.size()-1; ++j){
            solution.push_back(finite_difference(
                solution.at((i-1)*(spacemesh.size()) + j + 1),
                solution.at((i-1)*(spacemesh.size()) + j - 1),
                solution.at((i-1)*(spacemesh.size()) + j),
                solution.at((i-2)*(spacemesh.size()) + j),
                rho
            ));
        }
        //End each row with BC
        solution.push_back(right_bound);
    }
    

    //Convert to vector2d
    std::vector<double>::iterator ptr = solution.begin();
    std::vector<std::vector<double>> solutionAsVec2d = numerical_utils::vector_to_vector2d(ptr, timemesh.size(), spacemesh.size());

    //Print solution before plotting
    std::vector<std::vector<double>>::iterator ptr2d = solutionAsVec2d.begin();
    numerical_utils::print_vector2d(ptr2d, spacemesh.size(), timemesh.size());

    auto [X, Y] = matplot::meshgrid(spacemesh,timemesh);

    matplot::surf(X, Y, solutionAsVec2d);

    matplot::title("Explicit Finite Difference Solution to 1D Wave Equation");
    matplot::xlabel("x");
    matplot::ylabel("t");
    matplot::zlabel("f (Amplitude)");

    matplot::show();

    return 0;
}