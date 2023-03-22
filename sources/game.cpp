#include "game.hpp"
#include "player.hpp"

namespace ariel {
        Game::Game(Player p1, Player p2) {
            this->p1 = p1;
            this->p2 = p2;
        }
        Game::~Game() {}

        void Game::playTurn() {int i=1;} // All those {1+1;} blocks are meaningless rows which were writen only for compelation
        void Game::printLastTurn() {int i=1;}
        void Game::playAll() {int i=1;}
        void Game::printWiner() {int i=1;}
        void Game::printLog() {int i=1;}
        void Game::printStats() {int i=1;}

        ariel::Player Game::getPlayer1() {return this->p1;}
        ariel::Player Game::getPlayer2() {return this->p2;}

};
