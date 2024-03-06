#include <iostream>

template<typename T = void>
class Something {
    public:
    Something() {
        std::cout << "Something" << std::endl;
    }
};

template<>
class Something<> {
    public:
    Something() {
        std::cout << "Something<void>" << std::endl;
    }
};

float f(Something s) {
    return 0.0f;
}

int main() {
    Something<int> s1;
    Something s2;

    return 0;
}