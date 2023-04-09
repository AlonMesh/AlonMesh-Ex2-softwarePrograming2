#include "game.hpp"
#include "card.hpp"
#include "player.hpp"
#include <string>
#include <vector>

namespace ariel {

    Player::Player(string name) {
        this->name = name;
        this->handSize = 0;
        this->cardsTaken = 0;
    }

    Player::Player() {
        this->name = "No Name";
        this->handSize = 0;
        this->cardsTaken = 0;
    }

    Player::Player(const Player& other) {
        this->name = other.name;
        this->handSize = other.handSize;
        this->cardsTaken = other.cardsTaken;
        this->hand = other.hand;
    }

    Player& Player::operator=(const Player& other) {
        if (this != &other) {
            this->name = other.name;
            this->handSize = other.handSize;
            this->cardsTaken = other.cardsTaken;
            this->hand = other.hand;
        }
        return *this;
    }

    Player::Player(Player&& other) noexcept {
        this->name = std::move(other.name);
        this->handSize = std::move(other.handSize);
        this->cardsTaken = std::move(other.cardsTaken);
        this->hand = std::move(other.hand);
    }

    Player& Player::operator=(Player&& other) noexcept {
        if (this != &other) {
            this->name = std::move(other.name);
            this->handSize = std::move(other.handSize);
            this->cardsTaken = std::move(other.cardsTaken);
            this->hand = std::move(other.hand);
        }
        return *this;
    }

    Player::~Player() {}

    int Player::stacksize() {
        return handSize;
    }

    int Player::cardesTaken() {
        return cardsTaken;
    }

    string Player::getName() {
        return name;
    }

    void Player::setHandSize(int size) {
        this->handSize = size;
    }

    void Player::addCardsTaken(int cards) {
        this->cardsTaken += cards;
    }

    vector<Card>& Player::getHand()  {
        return hand;
    }

    void Player::dropCard() {
        this->handSize--;
    }

}
