#ifndef GAME_HPP
#define GAME_HPP

namespace ariel { class Player; class Card; }
#include "card.hpp"
#include <vector>
using namespace std;

namespace ariel {
    using namespace ariel;

    class Game {
        public:
            Game();
            Game(Player& player1, Player& player2);
            Game(const Game& other); // Declaration of the copy constructor
            Game& operator=(const Game& other);
            Game(Game&& other) noexcept;
            Game& operator=(Game&& other) noexcept;
            ~Game();

            // Play a round in the game
            void playTurn();
            
            // Print the turnLog
            void printLastTurn();

            // Play all games till the game is over
            void playAll();

            // Print the name of the winner (or the player in charge)
            void printWiner();

            // Print all turnLog so far
            void printLog();

            // Print statistics about the game, such as winrate for each player and total draws
            void printStats();

            // Print the cards
            void printDeck();

            // Returns a referance for each player
            Player getPlayer1();
            Player getPlayer2();

        private:
            // Creating an ordered and ligel deck
            void startGame();

            // Shuffling an ordered (or not) deck and order it randomly
            void shuffle();

            // Split cards for each player
            void splitCards();

            vector<string> gameHistory;
            Player& p1;
            Player& p2;
            vector<Card> deck;
            bool isOn;
            int roundWins1;
            int roundWins2;
    };
}
#endif
