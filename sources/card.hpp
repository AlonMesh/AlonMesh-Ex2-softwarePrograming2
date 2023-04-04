#ifndef CARD_H
#define CARD_H
#include <string>

namespace ariel {

enum class CardRank {
    Ace = 1,
    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9,
    Ten = 10,
    Jack = 11,
    Queen = 12,
    King = 13
};


enum class CardShape {
    Spades,
    Hearts,
    Diamonds,
    Clubs
};


    class Card {
    public:
        Card(CardRank rank, CardShape shape);
        ~Card();

        int getRank();
        std::string getRankName();
        CardShape getShape();
        std::string getShapeName();

    private:
        CardRank rank;
        CardShape shape;

    };
}

#endif