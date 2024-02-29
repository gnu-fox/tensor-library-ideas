#include <iostream>
#include <vector>
#include <variant>
#include <unordered_map> 

class Variable {
    public:
    float value;

    Variable* forward() {
        return this;
    }

    void backward(Variable* gradient) {
        /**/
    }
};


struct Memory {
    static std::unordered_map<std::string, std::vector<Variable*>> pool;

    static void reserve(std::size_t memory_size, std::string location = "default") {
        pool[location].reserve(memory_size);
    }

    static Variable* allocate(std::string location = "default") {
        Variable* variable = new Variable;
        variable->value = 0.0;
        pool[location].push_back(variable);
        return variable;
    }

    static void free(std::string location = "default") {
        for (auto variable : pool[location]) {
            std::cout << "deleting variable " << variable->value << std::endl;
            delete variable;
        }
        pool[location].clear();
    }
};

std::unordered_map<std::string, std::vector<Variable*>> Memory::pool;


template <typename Derived>
class Operation {

};

class Addition : public Operation<Addition> {
    public:
    Addition(Variable* a, Variable* b) {
        a_ = a;
        b_ = b;
    }

    Variable* perform() {
        Variable* result = Memory::allocate();
        result->value = a_->value + b_->value;
        return result;
    }

    void backward(Variable* gradient) {
        a_->backward(gradient);
        b_->backward(gradient);
    }

    private:
    Variable* a_;
    Variable* b_;

};

class Multiplication : public Operation<Multiplication> {
    public:

    private:
    Variable* a_;
    Variable* b_;
};

int main() {

    Memory::reserve(10);

    Variable* a = Memory::allocate();
    Variable* b = Memory::allocate();

    a->value = 1.0;
    b->value = 2.0;

    Addition addition(a, b);

    Variable* result = addition.perform();

    std::cout << "result: " << result->value << std::endl;


    Memory::free();

    return 0;
}