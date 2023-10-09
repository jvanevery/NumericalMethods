/** Using the Gauss-Seidel iterative finite-difference approach to numerically solve Laplace's equation in 2D 
 * 
 * Starting from the differential version of gauss' law ..... laplacian (potential) = rho/epsilon
 * 
 * We will be working with zero enclosed charge, so rho = 0. So the equation to solve is:
 * 
 * d2f/dx2 + d2f/dy^2 = 0
 * 
 * Where f is the electric potential
 * 
 * Boundary conditions must be provided to solve over a region
 * **/

#include <iostream>
#include <vector>
#include <cmath>
#include <matplot/matplot.h>

//Five point finite difference formula. p is the potential
//         0        <------ p_i_jplus
//   0     0     0  < ---- p_imin_j, p_i_j, p_iplus_j
//         0        <------ p_i_jmin
double finite_difference(double p_iplus_j, double p_i_jplus , double p_imin_j , double p_i_jmin , double rho){
    return (1/(2*(rho+1)))*(p_i_jplus + rho*(p_iplus_j + p_imin_j) + p_i_jmin);
}

//Initialize solution with zeros
/*
void init_solution(std::vector<std::vector<double>>::iterator ptr, size_t rows, size_t columns){
    for(int i = 0; i<rows; i++){
        std::vector<double> next_row(columns, 0);
        *ptr = next_row;
        std::advance(ptr, 1);
    }
}
*/

/**Set boundary conditions in solution
     * BC: f(0,y) = 10 J/C, f(xright,y) = 10 J/C
     *     f(x,0) = 0, f(x, yright) = 0
     * */
void set_initial_conditions(std::vector<std::vector<double>>::iterator ptr, size_t rows, size_t columns){
    for(int i = 0; i<rows; i++){
        (*ptr)[0] = 10;
        (*ptr)[columns-1] = 10;
        std::advance(ptr, 1);
    }
}

void print_solution_row(std::vector<double> row){
    
    for(int i=0; i<row.size(); ++i){
        std::cout << row[i] << " ";
    }
    std::cout << std::endl;
}

void print_solution(std::vector<std::vector<double>>::iterator ptr, size_t rows, size_t columns){
    for(int j=0; j<rows; j++){
        print_solution_row(*ptr);
        std::advance(ptr, 1);
    }
}

int main(){

    //Set domain, stepsizes, constants, and iteration number
    const double xleft = 0;
    const double xright = 1;
    const double yleft = 0;
    const double yright = 1;
    const double ystep = 0.1;
    const double xstep = 0.1;
    const double rho = std::pow(ystep,2)/std::pow(xstep,2);
    const double iterations = 100;

    //Discretization for x and y
    std::vector<double> x = matplot::iota(xleft, xstep, xright);
    std::vector<double> y = matplot::iota(yleft, ystep, yright);

    //initialize solution space
    std::vector<std::vector<double>> solution;
    std::vector<std::vector<double>>::iterator ptr = solution.begin();
    //init_solution(ptr, y.size(), x.size());

    for(int j = 0; j<y.size(); j++){
        std::vector<double> next_row(x.size(), 0);
        solution.push_back(next_row);
    }

    //Set BCs in solution
    ptr = solution.begin();
    set_initial_conditions(ptr, y.size(), x.size());

    //Iterate using 5 point Gauss_Seidel Method
    for(int it=0; it<iterations; ++it){
        for(int j=1; j<y.size()-1; ++j){
            for(int i=1; i<x.size()-1; ++i){
                solution.at(j).at(i) = finite_difference(
                    solution.at(j).at(i+1),
                    solution.at(j+1).at(i),
                    solution.at(j).at(i-1),
                    solution.at(j-1).at(i),
                    rho);
            }
        }
    }

    ptr = solution.begin();
    print_solution(ptr, y.size(), x.size());
    
    //This is a vector<vector<double>>
    auto [X, Y] = matplot::meshgrid(x,y);

    matplot::surf(X, Y, solution);

    matplot::show();

    return 0;
}