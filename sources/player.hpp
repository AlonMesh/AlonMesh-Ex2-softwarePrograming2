#ifndef PLAYER_H
#define PLAYER_H
#include "game.hpp"
#include "card.hpp"
#include <string>
#include <vector>

namespace ariel {
    class Player {
        public:
            Player(std::string name);
            ~Player();
            
            int stacksize();
            int cardesTaken();
            std::string getName();
            void setHandSize(int size);

            int handSize;
            int cardsTaken;
            std::vector<ariel::Card> hand;

        private:
            std::string name;
    };
}

#endif
