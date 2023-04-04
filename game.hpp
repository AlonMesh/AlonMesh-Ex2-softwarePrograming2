    #ifndef GAME_H
    #define GAME_H

    #include "player.hpp"
    #include <vector>

    namespace ariel {
        class Game {
        public:
            Game(ariel::Player &p1, ariel::Player &p2);
            ~Game();

            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();

            void Game::printDeck();

            Player getPlayer1();
            Player getPlayer2();

        private:
            void startGame();
            void splitCards();
            void shuffle();

            std::vector<std::string> gameHistory;

            Player& p1;
            Player& p2;
            std::vector<Card> deck;
        };
    }
    #endif
