#ifndef ARRAY_HPP_
#define ARRAY_HPP_

#include <iostream>
#include <vector>

#include "memory.hpp"

class Array {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;

    Array(size_type size, type dtype, std::string location = "default") {
        offset_ = Memory::allocate(size, dtype, location);
        size_ = size;
        dtype_ = dtype;
    }
    
    size_type size() const {
        return size_;
    }

    private:
    void* offset_;
    type dtype_;
    size_type size_;
    std::vector<std::size_t> strides_;
};

#endif // ARRAY_HPP_