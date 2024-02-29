#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <unordered_map>
#include <variant>

template <typename Derived>
struct Operation {

};

struct Addition : public Operation<Addition> {

};

struct Multiplication : public Operation<Multiplication> {

};

struct Graph {
    using Node = std::variant<
        Addition,
        Multiplication
    >;

};

#endif