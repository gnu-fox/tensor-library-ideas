#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <iostream>
#include <string>
#include <unordered_map>

namespace internal {
    
    class Block {
        public:
        using size_type = std::size_t;

        Block(size_type memory_size) {
            memory_size_ = memory_size;
            data_ = operator new(memory_size_);
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
        size_type memory_size_;
    };
}

struct Memory {
    using size_type = std::size_t;
    static std::unordered_map<std::string, internal::Block> pool;

    void static reserve(size_type memory_size, const std::string& location = "default") {
        pool[location] = internal::Block(memory_size);
    }

    static void* allocate(size_type chunk_size, const std::string& location = "default") {
        return pool[location].allocate(chunk_size);
    }
};

#endif // BUFFER_HPP_