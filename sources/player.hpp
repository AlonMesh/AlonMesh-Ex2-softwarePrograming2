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
            
            // Return the amount of cards left in player's hand
            int stacksize();
            
            // Return the amount of cards won by the player during the game
            int cardesTaken();

            // Return the name of the player
            string getName();

            // A setter for the field handSize
            void setHandSize(int size);

            // Increase the field cardsTaken by a given number
            void addCardsTaken(int cards);

            // Returns a referance to a player's hand
            vector<Card>& getHand();

            // Decrease the field handSize by 1
            void dropCard();


        private:
            string name; // A player must have a name
            int handSize; // The amount of cards player holds
            int cardsTaken; // The amount of cards player won during the game
            vector<Card> hand; // Set of cards the player holds

    };
}

#endif
