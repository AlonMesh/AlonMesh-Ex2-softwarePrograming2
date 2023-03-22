    #ifndef GAME_H
    #define GAME_H

    #include "player.hpp"

    namespace ariel {
        class Game {
        public:
            Game(ariel::Player p1, ariel::Player p2);
            ~Game();

            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();

            ariel::Player getPlayer1();
            ariel::Player getPlayer2();

        private:
            ariel::Player p1;
            ariel::Player p2;
        };
    }
    #endif
