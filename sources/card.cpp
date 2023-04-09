#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
using namespace std;
namespace ariel {
    
    Card::Card() {}

    Card::Card(CardRank rank, CardShape shape) {
        this->rank = rank;
        this->shape = shape;
    }

    Card::Card(const Card& other) {
        // copy the values of the other object's members to this object's members
        this->rank = other.rank;
        this->shape = other.shape;
    }

        Card& Card::operator=(const Card& other) {
        if (this != &other) {
            this->rank = other.rank;
            this->shape = other.shape;
        }
        return *this;
    }

    Card::Card(Card&& other) noexcept {
        this->rank = other.rank;
        this->shape = other.shape;
        other.rank = CardRank::Two;
        other.shape = CardShape::Spades;
    }

    Card& Card::operator=(Card&& other) noexcept {
        if (this != &other) {
            this->rank = other.rank;
            this->shape = other.shape;
            other.rank = CardRank::Two;
            other.shape = CardShape::Spades;
        }
        return *this;
    }

    Card::~Card() {};

    int Card::getRank() {
        int rankValue = static_cast<int>(this->rank);
        return rankValue;
    }

    string Card::getShapeName() {
        switch (shape) {
            case CardShape::Spades:
                return "Spades";
            case CardShape::Hearts:
                return "Hearts";
            case CardShape::Diamonds:
                return "Diamonds";
            case CardShape::Clubs:
                return "Clubs";
            default:
                return "";
    }
}
}