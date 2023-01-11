#include <iostream>
#include <memory>
#include <vector>

// struct with template type T
template <typename T>
struct MyStruct {
    T value;
    MyStruct(T v) : value(v) {}
    T getValue() const { return value; }
};

// abstract base class
class Base {
public:
    virtual ~Base() = default;
    virtual void print() const = 0;
};

// class template with template type T
template <typename T>
class Derived : public Base {
public:
    Derived(T v) : value(std::make_unique<MyStruct<T>>(v)) {}
    void print() const override {
        std::cout << "My value is " << value->getValue() << std::endl;
    }
private:
    std::unique_ptr<MyStruct<T>> value;
};

// class template argument deduction for constructors
template <typename T>
Derived(T) -> Derived<T>;

int main() {
    auto x = Derived(5);  // Derived<int>
    auto y = Derived("hello");  // Derived<const char*>

    std::vector<std::unique_ptr<Base>> vec;
    vec.emplace_back(std::make_unique<Derived<int>>(10));
    vec.emplace_back(std::make_unique<Derived<std::string>>("world"));

    for (auto& element : vec) {
        element->print();
    }

    //lambda function with constexpr
    constexpr auto adder = [](auto x, auto y) constexpr { return x + y; };
    std::cout << adder(5, 6) << std::endl; // 11
    std::cout << adder(std::string("hello "), std::string("world")) << std::endl; // "hello world"
    return 0;
}
