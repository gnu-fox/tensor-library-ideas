#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace internal {
    
    class MemoryBlock {
        public:

        MemoryBlock(std::size_t memory_size) {
            memory_size_ = memory_size;
            data_ = operator new(memory_size_);
            offset_ = data_;
        }

        ~MemoryBlock() {
            operator delete(data_);
        }

        void* allocate(std::size_t memory_size) {
            void* offset = offset_;
            offset_ = static_cast<char*>(offset_) + memory_size;
            return offset;
        }

        private:
        void* data_ = nullptr;
        void* offset_ = nullptr;
        std::size_t memory_size_;
    };

}

struct Memory {
    static std::unordered_map<std::string, internal::MemoryBlock> buffer;

    static void reserve(std::size_t memory_size, std::string location ) {
        buffer[location] = internal::MemoryBlock(memory_size);
    }

    static void* allocate(std::size_t memory_size, std::string location) {
        return buffer[location].allocate(memory_size);
    }

};

enum class dtype {
    float32
};

class Tensor {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;

    Tensor(shape_type shape, dtype dtype, std::string location = "default") {
        shape_ = shape;
        size_= 1; for (auto size : shape) size_ *= size;
        offset_ = Memory::allocate(size_ * sizeof(float), location);
    }

    private:
    void* offset_;
    size_type size_;
    shape_type shape_;
    shape_type strides_;
};


int main() {
    
}