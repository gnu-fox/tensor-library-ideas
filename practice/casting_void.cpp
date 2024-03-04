#include <stdexcept>
#include <iostream>

enum class DataType {
    float32,
    integer32
};

class DataProcessor {
public:
    DataProcessor(DataType type, void* ptr) : type_(type), ptr_(ptr) {}

    auto process() {
        switch (type_) {
            case DataType::float32:
                return *static_cast<float*>(ptr_);
            default:
                throw std::runtime_error("unsupported data type");
        }
    }

private:
    DataType type_;
    void* ptr_;
};

int main() {
    float floatValue = 3.14f;
    int intValue = 42;

    // Example usage
    DataProcessor processorFloat(DataType::float32, &floatValue);
    auto resultFloat = processorFloat.process();
    std::cout << "Result for float: " << resultFloat << std::endl;

    DataProcessor processorInt(DataType::integer32, &intValue);
    auto resultInt = processorInt.process();
    std::cout << "Result for integer: " << resultInt << std::endl;

    return 0;
}