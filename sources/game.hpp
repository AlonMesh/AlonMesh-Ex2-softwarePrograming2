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

            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();
            void printDeck(); // Mine

            Player getPlayer1();
            Player getPlayer2();

        private:
            void startGame();
            void splitCards();
            void shuffle();

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
