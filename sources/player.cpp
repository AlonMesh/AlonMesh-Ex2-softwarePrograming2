#include <string>
#include "player.hpp"

namespace ariel {

    Player::Player(std::string name) {
        this->name = name;
        this->handSize = 26;
    }

    Player::Player() {
        this->name = "No Name";
        this->handSize = 26;
    }

    Player::~Player() {}

    int Player::stacksize() {return this->handSize;}
    int Player::cardesTaken() {return 0;}
    std::string Player::getName() {return "0";}
}