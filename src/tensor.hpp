#ifndef TENSOR_HPP_
#define TENSOR_HPP_

#include <iostream>
#include <vector>

#include "array.hpp"

enum class dtype {
    float32
};

class Tensor {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;


    private:
    Array value_;
    Array* gradient_;
};

#endif // TENSOR_HPP_