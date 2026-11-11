#include "Zoo.hpp"

int main() {
    Zoo zoo;
    zoo.add(std::make_unique<Dog>());
    zoo.add(std::make_unique<Cat>());
    zoo.add(std::make_unique<Bird>());
    zoo.add(std::make_unique<WolfDog>());
    zoo.allSpeak();
    return 0;
}
