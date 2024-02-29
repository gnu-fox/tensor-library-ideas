#include <iostream>
#include <vector>
#include <cstdint>

enum class type {
    float32 = 4,
};

class Tensor {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;

    Tensor(size_type size, type dtype = type::float32) {
        size_ = size;
        offset_ = operator new(size_*static_cast<int>(dtype));
    }

    ~Tensor() {
        operator delete(offset_);
    }

    auto begin() { return static_cast<float*>(offset_); }
    auto end() { return static_cast<float*>(offset_) + size_; }

    private:
    void* offset_;
    size_type size_;
};


int main() {

    std::cout << static_cast<uint16_t>(type::float32) << std::endl;

    
    Tensor tensor(10, type::float32);
    float i = 0;
    for (auto& value : tensor) {
        value = i++;
    }

    for (auto value : tensor) {
        std::cout << value << std::endl;
    }

    return 0;
}