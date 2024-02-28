#include <iostream>
#include <vector>

enum class layout {
    Row,
    Column
};

class Matrix {
    public:
    using size_type = std::size_t;

    Matrix(size_type rows, size_type cols, layout layout = layout::Row) {
        rows_ = rows;
        cols_ = cols;
        data_.resize(rows*cols);
        layout_ = layout;
    }
    
    private:
    size_type rows_;
    size_type cols_;
    layout layout_;
    std::vector<float> data_;
    std::vector<std::size_t> strides_;
};


int main() {
    Matrix matrix(3, 3);
}