#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "card.hpp"
#include "game.hpp"
#include <string>
#include <vector>
using namespace std;

namespace ariel {
    class Player {
        public:
            Player(string name);
            Player();
            Player(const Player& other);
            Player& operator=(const Player& other);
            Player(Player&& other) noexcept;
            Player& operator=(Player&& other) noexcept;
            ~Player();
            
            int stacksize();
            int cardesTaken();
            string getName();
            void setHandSize(int size);
            void addCardsTaken(int cards);
            vector<Card>& getHand();
            void dropCard();


        private:
            string name;
            int handSize;
            int cardsTaken;
            vector<Card> hand;

    };
}

#endif
