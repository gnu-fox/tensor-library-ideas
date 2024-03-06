#include <iostream>
#include <vector>

#include "memory.hpp"

enum class layout {
    row,
    column
};

class Matrix {
    public:
    using size_type = std::size_t;
    Matrix(size_type rows, size_type columns, dtype type, void* data, layout layout = layout::row) {
        
                                
    }


    private:
    void* data_;
    dtype data_type_;
    std::vector<std::size_t> strides_in_bytes_;
};