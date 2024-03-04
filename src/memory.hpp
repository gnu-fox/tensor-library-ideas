#ifndef MEMORY_HPP_
#define MEMORY_HPP_

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>

namespace internal {

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
        void* data_;
        void* offset_;
        std::size_t memory_size_;
    };
}

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

struct Memory {
    static std::unordered_map<std::string, internal::Block> pool;
    static void reserve(std::size_t memory_size, std::string location = "default") {
        pool[location] = internal::Block(memory_size);
    }

    using size_type = std::size_t;
    static void* allocate(size_type size, dtype type, std::string location = "default") {
        switch(type) {
            case dtype::float32:
                return pool[location].allocate(size * sizeof(float));
            default:
                return nullptr;
        }
    }
};

std::unordered_map<std::string, internal::Block> Memory::pool;

#endif // MEMORY_HPP_