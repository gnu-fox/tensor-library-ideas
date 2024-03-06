#ifndef ARRAY_HPP_
#define ARRAY_HPP_

#include <iostream>
#include <vector>

#include "memory.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

/*

class Shape

class Range

*/

class Array {
    public:
    using size_type = std::size_t;

    Array operator[](size_type index) {
        if(index >= strides_in_bytes_.back()) throw std::out_of_range("index out of range");
        std::vector<std::size_t> strides(strides_in_bytes_.begin(), strides_in_bytes_.end() - 1);
        void* offset = static_cast<char*>(offset_) + index * strides.back();
        return Array(offset, strides, data_type_);   
    }

    void* offset() {
        return offset_;
    }

    Array(void* offset, std::vector<std::size_t> strides_in_bytes, dtype type) {
        offset_ = offset;
        strides_in_bytes_ = strides_in_bytes;
        data_type_ = type;
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

#endif // ARRAY_HPP_