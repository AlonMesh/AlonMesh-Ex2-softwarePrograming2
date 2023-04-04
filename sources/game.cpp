#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
using namespace std;
using namespace ariel;
#include <vector>
#include <random>


    Game::Game(Player& p1, Player& p2) : p1(p1), p2(p2) {
        this->p1 = p1;
        this->p2 = p2;
        this->p1.setHandSize(26);
        this->p2.setHandSize(26);
        startGame();
    }
    Game::~Game() {}

    void Game::startGame() {
        // Creating new deck
        for(int i=1; i <= 4; i++) {
            for(int j=1; j <= 13; j++) {
                deck.push_back(Card(static_cast<CardRank>(j), static_cast<CardShape>(i)));
            }
        }

        shuffle();
        splitCards();
    }

    // Given an ordered deck, shuffle the deck
    void Game::shuffle() {

        // Generage a random number x in [1,5].
        // Then, split x cards for each player till there are less than x cards in the deck.
        // Combine to the deck each player's hand by its new order. repeat x200.
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(1, 6);

        for (int i = 0; i < 200; i++) {

            int random_num = distr(gen);

            vector<Card> deck1, deck2;

            while (this->deck.size() >= random_num*2) {

                for (int j = 0; j < 200; j++) {
                    deck1.push_back(this->deck.back());
                    deck.pop_back();
                }

                for (int j = 0; j < 200; j++) {
                    deck1.push_back(this->deck.back());
                    deck.pop_back();
                }
            }

            // Joining all the decks (by their new order) into a one deck

            while (!deck1.empty()) {
                this->deck.push_back(deck1.back());
                deck1.pop_back();
            }

            while (!deck2.empty()) {
                this->deck.push_back(deck2.back());
                deck2.pop_back();
            }
        }
    }

    void Game::splitCards() {
        for (int i = 0; i < 26; i++)
        {
            this->p1.hand.push_back(deck.back());
            deck.pop_back();
            this->p2.hand.push_back(deck.back());
            deck.pop_back();
        }
    }

    void Game::printDeck() {
        for (Card& card : this->deck) {
        std::cout << card.getRank() << std::endl;
        }
    }

    void Game::playTurn() {

        if (this->p1.hand.size() == 0) {
            return;
        }

        string turnLog = ""; // This variable documents everything happend during a turn

        Card card1 = this->p1.hand.back();
        p1.hand.pop_back();
        this->p1.handSize--;


        Card card2 = this->p2.hand.back();
        p2.hand.pop_back();
        this->p2.handSize--;

        turnLog += this->p1.getName() + " played " + to_string(card1.getRank()) + " of " + card1.getShapeName() + " ";
        turnLog += this->p2.getName() + " played " + to_string(card2.getRank()) + " of " + card2.getShapeName() + ". ";

        if (card1.getRank() > card2.getRank()) {
            this->p1.cardsTaken += 2;
            turnLog += this->p1.getName() + " wins.";
        }

        else if (card1.getRank() < card2.getRank()) {
            this->p2.cardsTaken += 2;
            turnLog += this->p2.getName() + " wins.";
        }

        else { // A draw!
            int totalWin = 2;
            bool vik = false;

            while (p1.hand.size() > 0 && !vik) {
                turnLog += " draw.";

                // Both players put a "KLAF HAFUH"
                p1.hand.pop_back();
                this->p1.handSize--;
                p2.hand.pop_back();
                this->p2.handSize--;

                // Option1: out of cards after putting "KLAF HAFUH" - no winner.
                if (p1.hand.size() == 0) {
                    break;
                }
                
                card1 = this->p1.hand.back();
                p1.hand.pop_back();
                this->p1.handSize--;
                card2 = this->p2.hand.back();
                p2.hand.pop_back();
                this->p2.handSize--;

                turnLog += " " + this->p1.getName() + " played " + to_string(card1.getRank()) + " of " + card1.getShapeName() + " ";
                turnLog += " " + this->p2.getName() + " played " + to_string(card2.getRank()) + " of " + card2.getShapeName() + ". ";

                totalWin += 4;

                if (card1.getRank() > card2.getRank()) {
                    this->p1.cardsTaken += totalWin;
                    turnLog += this->p1.getName() + " wins.";
                    vik = true;
                }

                else if (card1.getRank() < card2.getRank()) {
                    this->p2.cardsTaken += totalWin;
                    turnLog += this->p2.getName() + " wins.";
                    vik = true;
                }

                // Option2: out of cards after another draw - no winner.
                if (p1.hand.size() == 0) {
                    break;
                }
            }

            // When no one wins - split the potential win for both players.
            // *Including option3, when the while the code didn't get into the while loop.
            if (vik = false) {
                this->p1.cardsTaken += (totalWin / 2);
                this->p2.cardsTaken += (totalWin / 2);            
            }
        }

        this->gameHistory.push_back(turnLog);
    } 
    
    void Game::printLastTurn() {
        cout << this->gameHistory.back() << endl;
    }

    void Game::playAll() {
        while (this->p1.cardsTaken > 0) {
            playTurn();
        }

    }
    void Game::printWiner() {
        //eror if no winner yet

        if (this->p1.cardsTaken == this->p2.cardsTaken) {
            cout << this->p1.getName() << endl;
        }

        else if (this->p1.cardsTaken == this->p2.cardsTaken) {
            cout << this->p2.getName() << endl;
        }

        else {
            cout << "draw" << endl;
        }
    }
    void Game::printLog() {
        for (string turnLog : this->gameHistory) {
            cout << turnLog << endl;
        }
    }

    void Game::printStats() {
        
    }

    ariel::Player Game::getPlayer1() {return this->p1;}
    ariel::Player Game::getPlayer2() {return this->p2;}


