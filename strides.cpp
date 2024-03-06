#include <iostream>
#include <vector>

struct Range {
    std::size_t start;
    std::size_t stop;

    Range(std::size_t start, std::size_t stop) : start(start), stop(stop) {
        if (start > stop) {
            throw std::invalid_argument("start must be less than or equal to stop");
        }
    }
};

template<typename T> 
class Array {
    public:
    Array(T* offset, std::size_t size, std::vector<std::size_t> strides) {
        offset_ = offset;
        size_ = size;
        strides_ = strides;
    }

    Array operator[](std::size_t index) {
        std::vector<std::size_t> strides(strides_.begin() + 1, strides_.end());
        std::size_t size = strides_.front();
        T* offset = offset_ + index * size;
        return Array(offset, size, strides);
    }

    Array operator[](Range range) {
        std::vector<std::size_t> strides(strides_.begin(), strides_.end());
        std::size_t size = strides_.front() * (range.stop - range.start + 1);
        T* offset = offset_ + range.start * strides_.front();
        return Array(offset, size, strides);
    }


    std::size_t size() {
        return size_;
    }

    private:
    T* offset_;
    std::size_t size_;
    std::vector<std::size_t> strides_;

    template<typename U>
    friend std::ostream& operator << (std::ostream& os, const Array<U>&);
};

template<typename T>
std::ostream& operator << (std::ostream& os, const Array<T>& array) {
    for (std::size_t index = 0; index < array.size_; ++index) {
        os << '[' << array.offset_[index] << ']';
        for (std::size_t stride = 1; stride < array.strides_.size(); ++stride) {
            if ((index + 1) % array.strides_[stride] == 0) {
                os << std::endl;
                break;
            }
        }
    }
    return os;
}

int main() {
    float* data = new float[27];
    for (std::size_t index = 0; index < 27; ++index) {
        data[index] = index;
    }
    std::size_t size = 27;
    std::vector<std::size_t> strides = {9, 3};

    Array<float> array(data, size, strides);
    std::cout << array[{1,1}] << std::endl;
    delete[] data;
}