#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>

namespace {

    class Block {
        public:

        Block() {
            data_ = nullptr;
            offset_ = nullptr;
            memory_size_ = 0;
        }

        Block(std::size_t memory_size) {
            std::cout << "allocating memory of size " << memory_size << " bytes" << std::endl;
            
            data_ = operator new(memory_size);
            offset_ = data_;
            memory_size_ = memory_size;
        }

        Block(const Block& other) {
            std::cout << "copy constructor of Block of memory called" << std::endl;
            
            data_ = operator new(other.memory_size_);
            offset_ = other.offset_;
            memory_size_ = other.memory_size_;
            std::memcpy(data_, other.data_, other.memory_size_);

        }

        Block(Block&& other) {            
            std::cout << "move constructor of Block of memory called" << std::endl;
            data_ = other.data_;
            offset_ = other.offset_;
            memory_size_ = other.memory_size_;
            other.data_ = nullptr;
            other.offset_ = nullptr;
            other.memory_size_ = 0;

        }

        Block& operator=(const Block& other) {          
            std::cout << "copy assignment operator of Block called" << std::endl;
    
            if (this != &other) {
                data_ = operator new(other.memory_size_);
                offset_ = other.offset_;
                memory_size_ = other.memory_size_;
                std::memcpy(data_, other.data_, other.memory_size_);
            }
            return *this;
        }

        Block& operator=(Block&& other) {
            std::cout << "move assignment operator of Block called" << std::endl;

            if (this != &other) {
                data_ = other.data_;
                offset_ = other.offset_;
                memory_size_ = other.memory_size_;
                other.data_ = nullptr;
                other.offset_ = nullptr;
                other.memory_size_ = 0;
            }
            return *this;
        }

        ~Block() {
            std::cout << "destructor of Block called" << std::endl;
            operator delete(data_);
        }

        void* allocate(std::size_t chunk_size) {
            void* offset = offset_;
            offset_ = static_cast<char*>(offset_) + chunk_size;
            return offset;
        }

        private:
        void* data_ = nullptr;
        void* offset_ = nullptr;
        std::size_t memory_size_;
    };

}

enum class type {
    float32
};

inline size_t bytes(type dtype) {
    switch(dtype) {
        case type::float32:
            return sizeof(float);
        default:
            throw std::runtime_error("unsupported data type");
    }
}

struct Memory {
    static std::unordered_map<std::string, ::Block> pool;
    static void reserve(std::size_t memory_size, std::string location = "default") {
        pool[location] = ::Block(memory_size);
    }

    static void* allocate(std::size_t memory_size, std::string location = "default") {
        return pool[location].allocate(memory_size);
    }
};

std::unordered_map<std::string, ::Block> Memory::pool;

template<class T>
class Iterator {
    public:
    Iterator(std::vector<std::size_t> strides, void* offset, type dtype) {
        offset_ = offset;
        strides_ = strides;
        dtype_ = dtype;
    }

    Iterator operator[](std::size_t index) {
        std::vector<std::size_t> strides(strides_.begin(), strides_.end() - 1);
        offset_ = static_cast<char*>(offset_) + index * strides.back();
        return Iterator(strides, offset_, dtype_);
    }

    Iterator& operator ++(){
        offset_ = static_cast<char*>(offset_) + strides_.front();
        return *this;
    }

    Iterator operator ++(int){
        Iterator copy = *this;
        ++(*this);
        return copy;
    }

    Iterator& operator --(){
        offset_ = static_cast<char*>(offset_) - strides_.front();
        return *this;
    }

    Iterator operator --(int){
        Iterator copy = *this;
        --(*this);
        return copy;
    }

    T& operator*() {
        return *static_cast<T*>(offset_);
    }

    T* operator->() {
        return offset_;
    }

    friend bool operator == (const Iterator& lhs, const Iterator& rhs){
        return rhs.offset_ == lhs.offset_;
    }

    friend bool operator != (const Iterator& lhs, const Iterator& rhs){
        return !(rhs.offset_ == lhs.offset_);
    }

    private:
    void* offset_;
    type dtype_;
    std::size_t size_;
    std::vector<std::size_t> strides_;
};


class Array {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;
    using iterator = typename Iterator<Array>;

    Array(size_type size, type dtype, std::string location = "default") {
        size_ = size;
        dtype_ = dtype;
        offset_ = Memory::allocate(size * bytes(dtype), location);
    }

    for(auto element : tensor) {
        std::cout << array << std::endl;
    }

    Array(shape_type shape, type dtype, std::string location = "default") {
        size_ = 1;
        for(auto size : shape) {
            strides_.push_back(size_* bytes(dtype));
            size_ *= size;
        }
        dtype_ = dtype;
        offset_ = Memory::allocate(size_ * bytes(dtype), location);
    }

    size_type size() const { return size_; }

    private:
    void* offset_;
    type dtype_;
    size_type size_;
    std::vector<std::size_t> strides_;
};




int main() {
    float* offset = new float[36];

    for(int i = 0; i < 36; i++) { offset[i] = i; }

    type dtype_ = type::float32;
    size_t size_ = bytes(dtype_);
    std::vector<size_t> strides_;
    for(auto size : {3, 4, 3}) {
        strides_.push_back(size_);
        size_ *= size;
    }


    Array array({3, 4, 3}, type::float32);
}