#include <iostream>
#include <vector>

template <typename T = void>
class Tensor {
    public:
    Tensor() {
        std::cout << "default constructor of Tensor called" << std::endl;
    }
};

template<>
class Tensor<void> {
    public:
    Tensor() {
        std::cout << "default constructor of Tensor<void> called" << std::endl;
    }
};

int main() {
    Tensor<int> tensor1;
    Tensor tensor2;
}