#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <iostream>
#include <string>
#include <unordered_map>

namespace internal {
    
    class MemoryBlock {
        public:
        using size_type = std::size_t;

        MemoryBlock(size_type memory_size) {
            memory_size_ = memory_size;
            data_ = operator new(memory_size_);
        }

        ~MemoryBlock() {
            operator delete(data_);
        }

        private:
        void* data_;
        void* offset_;
        size_type memory_size_;
    };

}

struct Memory {
    using size_type = std::size_t;
    static std::unordered_map<std::string, internal::MemoryBlock> buffer;

    static void reserve(size_type memory_size, std::string location ) {
        buffer[location] = internal::MemoryBlock(memory_size);
    }
};

#endif // BUFFER_HPP_