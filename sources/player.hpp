#ifndef PLAYER_H
#define PLAYER_H

#include <string>

namespace ariel {
    class Player {
    public:
        Player(std::string name);
        Player();
        ~Player();

        int stacksize();
        int cardesTaken();
        std::string getName();

    private:
        std::string name;
        int handSize;
        //std::vector<Card> hand;
    };
}

#endif
