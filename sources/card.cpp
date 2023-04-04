#include "card.hpp"
using namespace ariel;
using namespace std;

    Card::Card(CardRank rank, CardShape shape) {
        this->rank = rank;
        this->shape = shape;
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