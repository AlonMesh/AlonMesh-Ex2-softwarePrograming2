#ifndef CARD_H
#define CARD_H
#include <string>
#include "game.hpp"
#include "player.hpp"

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
    // I got helped by the internet - I read that I need those function (till ~Card()) to avoid error via tidy
        Card();
        Card(CardRank rank, CardShape shape);
        Card(const Card& other);
        Card& operator=(const Card& other);
        Card(Card&& other) noexcept;
        Card& operator=(Card&& other) noexcept;
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