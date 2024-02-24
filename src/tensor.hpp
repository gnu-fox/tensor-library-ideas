#ifndef TENSOR_HPP_
#define TENSOR_HPP_

#include <iostream>
#include <vector>

class Tensor {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;


    private:
    void* offset_;
    size_type size_;
    shape_type shape_;
    shape_type strides_;
};

#endif // TENSOR_HPP_