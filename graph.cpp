#include <iostream>
#include <vector>
#include <variant>

struct Tensor {
    float value;

    float forward() const {
        return value;
    }
};

template<class Left, class Right>
struct Addition {
    Left left;
    Right right;

    float forward() const {
        return left.forward() + right.forward();
    }

};

template<class Left, class Right>
struct Multiplication {
    Left left;
    Right right;

    float forward() const {
        return left.forward() * right.forward();
    }

};


template<class Left, class Right>
struct Division {
    Left left;
    Right right;

    float forward() const {
        return left.forward() / right.forward();
    }

};


int main() {

    Tensor a{1.0};
    Tensor b{2.0};
    Tensor c{3.0};
    
    auto result = Addition<Multiplication<Tensor, Tensor>, Division<Tensor, Tensor>>{
        Multiplication<Tensor, Tensor>{a, b},
        Division<Tensor, Tensor>{c, b}
    };

    std::cout << result.forward() << std::endl;
}