#ifndef ARRAY_HPP_
#define ARRAY_HPP_

#include <iostream>
#include <vector>

class Array {
    public:
    Array(void* offset, std::size_t size, std::vector<std::size_t> strides) {
        offset_ = offset;
        size_ = size;
        strides_ = strides;
    }
    
    private:
    void* offset_;
    std::size_t size_;
    std::vector<std::size_t> strides_;
};


#endif // ARRAY_HPP_