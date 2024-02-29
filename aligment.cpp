#include <iostream>

class Block {
    public:
    Block(std::size_t memory_size) {
        avaliable_size_ = memory_size;
        data_ = operator new(memory_size);
        offset_ = data_;
    }

    ~Block() {
        operator delete(data_);
    }

    void* allocate(std::size_t chunk_size) {
        void* offset = offset_;
        offset_ = static_cast<char*>(offset_) + chunk_size;
        return offset;
    }

    private:
    void* data_;
    void* offset_;
    std::size_t avaliable_size_;
};