#ifndef TENSOR_HPP_
#define TENSOR_HPP_

#include <iostream>
#include <vector>

#include "buffer.hpp"

enum class dtype {
    float32
};


class Tensor {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;

    Tensor(shape_type shape, dtype dtype, std::string location = "default") {
        shape_ = shape;
        size_= 1; for (auto size : shape) size_ *= size;
    }

    private:
    void* offset_;
    Tensor* gradient_;
    size_type size_;
    shape_type shape_;
    shape_type strides_;
};

#endif // TENSOR_HPP_