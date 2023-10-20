#include <iostream>
#include <vector>

using namespace std;

namespace numerical_utils{

    //Helper function that prints a vector
    void print_vector2d_row(vector<double> row){
        
        for(int i=0; i<row.size(); ++i){
            cout << row[i] << " ";
        }
        cout << endl;
    }

    //Print a vector of vectors
    void print_vector2d(vector<vector<double>>::iterator ptr, size_t rows, size_t columns){
        for(int j=0; j<rows; j++){
            print_vector2d_row(*ptr);
            advance(ptr, 1);
        }
    }

    //Convert a vector to a vector2d with specified row and column size
    vector<vector<double>> vector_to_vector2d(vector<double>::iterator ptr, size_t rows, size_t columns){

        vector<vector<double>> solution_as_vector_2d;

        for(int i=0; i<rows; i++){
            vector<double> next_row;
            for(int j=0; j<columns; j++){
                next_row.push_back(*ptr);
                advance(ptr, 1);
            }
            solution_as_vector_2d.push_back(next_row);
        }
        return solution_as_vector_2d;
    }

}