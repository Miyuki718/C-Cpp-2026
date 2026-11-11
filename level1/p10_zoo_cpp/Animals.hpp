#pragma once
#include <iostream>

class Animal {
public:
    virtual void speak() const = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Dog: Woof!\n";
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Cat: Meow!\n";
    }
};

class Bird : public Animal {
public:
    void speak() const override {
        std::cout << "Bird: Tweet!\n";
    }
};

class WolfDog : public Dog {
public:
    void speak() const override {
        std::cout << "WolfDog: Awooo!\n";
    }
};
