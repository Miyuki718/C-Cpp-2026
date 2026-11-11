#pragma once
#include <memory>
#include <utility>
#include <vector>
#include "Animals.hpp"

class Zoo {
private:
    std::vector<std::unique_ptr<Animal>> animals;

public:
    void add(std::unique_ptr<Animal> animal) {
        if (animal) {
            animals.push_back(std::move(animal));
        }
    }

    void allSpeak() const {
        for (const auto& animal : animals) {
            animal->speak();
        }
    }
};
