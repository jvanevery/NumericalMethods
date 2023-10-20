#include <vector>

namespace numerical_utils{

    void print_vector2d(std::vector<std::vector<double>>::iterator ptr, size_t rows, size_t columns);

    std::vector<std::vector<double>> vector_to_vector2d(std::vector<double>::iterator ptr, size_t rows, size_t columns);

}