#include <iostream>
#include <vector>

class Array {
    public:

    Array(std::vector<std::size_t> shape, float* offset) {
        offset_ = offset;
        size_ = 1; 
        for (auto size : shape) {
            strides_.push_back(size_);
            size_ *= size;
        }
    }

    Array(std::vector<std::size_t> strides, std::size_t size, float* offset) {
        offset_ = offset;
        size_ = size;
        strides_ = strides;
    }

    void print() {
        for(int i = 0; i < size_; i++) {
            std::cout << '[' << offset_[i] << ']';
            for(int j = 1; j < strides_.size(); j++) {
                if ((i+1) % strides_[j] == 0) {
                    std::cout << std::endl;
                }
            }
        }
    }

    Array operator[](std::size_t index) {
        std::vector<std::size_t> new_strides(strides_.begin(), strides_.end() - 1);
        std::size_t new_size = size_ / strides_[1];
        float* new_offset = offset_ + index * strides_.back();
        return Array(new_strides, new_size, new_offset);
    }


    private:
    float* offset_;
    std::size_t size_;
    std::vector<std::size_t> strides_;
};

int main() {
    float* offset = new float[36];
    for(int i = 0; i < 36; i++) { offset[i] = i; }

    Array a({3, 4, 3}, offset);
    a.print();

    delete [] offset;
}