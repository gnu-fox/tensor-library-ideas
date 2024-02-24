#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <iostream>

class Buffer {
    public:
    using size_type = std::size_t;

    Buffer(size_type memory_size) {
        memory_size_ = memory_size;
        data_ = operator new(memory_size_);
    }

    ~Buffer() {
        operator delete(data_);
    }

    private:
    void* data_;
    void* offset_;
    size_type memory_size_;
    
};

#endif // BUFFER_HPP_