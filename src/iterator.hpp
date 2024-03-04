#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include <vector>

#include "memory.hpp"

class Iterator {
    public: 

    Iterator(std::vector<std::size_t> strides, void* offset, dtype type) {
        offset_ = offset;
        type_ = type;
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

    void* operator->() {
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
    dtype type_;
    std::vector<std::size_t> strides_;
};

#endif // ITERATOR_HPP_