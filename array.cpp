#include <iostream>
#include <vector>
#include <algorithm>


enum class dtype {
    float32,
    int32
};

std::size_t size_of(dtype type) {
    switch (type) {
        case dtype::float32:
            return sizeof(float);
        case dtype::int32:
            return sizeof(int);
        default:
            return 0;
    }
}

class Array {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;

    Array(void* offset, std::vector<std::size_t> strides, dtype type) {
        offset_ = offset;
        strides_in_bytes_ = strides;
        data_type_ = type;
        
    }

    Array operator[](size_type index) {
        if(index >= strides_in_bytes_.back()) throw std::out_of_range("index out of range");
        std::vector<std::size_t> strides(strides_in_bytes_.begin(), strides_in_bytes_.end() - 1);
        void* offset = static_cast<char*>(offset_) + index * strides.back();
        return Array(offset, strides, data_type_);   
    }

    void* offset() {
        return offset_;
    }

    private:
    void* offset_;
    std::vector<std::size_t> strides_in_bytes_;
    dtype data_type_;

    friend std::ostream& operator << (std::ostream& os, const Array&);
};

namespace internal{

    template <typename T>
    inline std::ostream& print(std::ostream& os, void* offset, std::vector<std::size_t> strides_in_bytes) {
        T* data = static_cast<T*>(offset);
        for (std::size_t index = 0; index < strides_in_bytes.back() / sizeof(T); ++index) {
            os << '[' << data[index] << ']';

            
            for (std::size_t stride = 1; stride < strides_in_bytes.size(); ++stride) {
                if ((index + 1) % (strides_in_bytes[stride] / sizeof(T)) == 0) {
                    os << std::endl;
                    break;
                }
            }
        }

        return os;
    }

}

std::ostream& operator << (std::ostream& os, const Array& array) {
    switch (array.data_type_) {
        case dtype::float32:
            return internal::print<float>(os, array.offset_, array.strides_in_bytes_);
        case dtype::int32:
            return internal::print<int>(os, array.offset_, array.strides_in_bytes_);
        default:
            return os;
    }
}


class Tensor {
    public:
    Tensor(void* offset) {
        offset_ = offset;
    }

    void* offset() {
        return offset_;
    }

    private:
    void* offset_;
};

int main() {
    void* data = operator new(100 * sizeof(float));
    std::vector<std::size_t> strides_in_bytes = {1* sizeof(float), 10* sizeof(float), 100* sizeof(float)};

    for (std::size_t index = 0; index < 100; ++index) {
        static_cast<float*>(data)[index] = index;
    }

    Array array(data, strides_in_bytes, dtype::float32);
    std::cout << array << std::endl;

    operator delete(data);
    return 0;
}
