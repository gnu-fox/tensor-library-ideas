#include <iostream>
#include <vector>

class Iterator{
    public:

    private:
    float* offset_;
    std::size_t size_;
    std::vector<std::size_t> strides_;
};



int main () {
    

    std::vector<std::size_t> shape = {2, 3};
    std::vector<std::size_t> strides = {3, 1};
    std::size_t size = 6;
}