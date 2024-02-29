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

struct Memory {
    static std::unordered_map<std::string, ::Block> pool;
    static void reserve(std::size_t memory_size, std::string location = "default") {
        pool[location] = ::Block(memory_size);
    }

    using size_type = std::size_t;
    static void* allocate(size_type size, type dtype, std::string location = "default") {
        switch(dtype) {
            case type::float32:
                return pool[location].allocate(size * sizeof(float));
            default:
                return nullptr;
        }
    }
};

std::unordered_map<std::string, ::Block> Memory::pool;

class Array {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;

    Array(size_type size, type dtype, std::string location = "default") {
        offset_ = Memory::allocate(size, dtype, location);
        size_ = size;
        dtype_ = dtype;
    }
    
    size_type size() const {
        return size_;
    }

    Array& operator[](size_type index) {
        
    }

    private:
    void* offset_;
    type dtype_;
    size_type size_;
    std::vector<std::size_t> strides_;
};


int main() {
    Memory::pool["default"] = ::Block(1024);
    Memory::pool["default"] = ::Block(2048);
    Memory::pool["default"] = ::Block(4096);

    Memory::reserve(1024);

    float* data = (float*) Memory::allocate(10, type::float32);

    for (int i = 0; i < 10; i++) {
        data[i] = i + 5.0;
    }

    for (int i = 0; i < 10; i++) {
        std::cout << data[i] << std::endl;
    }

    Array a(10, type::float32);
    std::cout << "Printing a size" << a.size() << std::endl;
    return 0;

}
