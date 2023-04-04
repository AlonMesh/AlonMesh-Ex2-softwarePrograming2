#include <string>
#include "player.hpp"
using namespace ariel;

    Player::Player(std::string name) {
        this->name = name;
        this->handSize = 0;
        this->cardsTaken = 0;
    }

    // Player::Player() {
    //     this->name = "No Name";
    //     this->handSize = 0;
    //     this->cardsTaken = 0;
    // }

    Player::~Player() {}

    int Player::stacksize() {return handSize;}
    int Player::cardesTaken() {return cardsTaken;}
    std::string Player::getName() {return name;}
    void Player::setHandSize(int size) {this->handSize = size;}
