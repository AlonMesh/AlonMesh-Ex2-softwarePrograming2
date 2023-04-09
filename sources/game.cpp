#include <iostream>
#include <stdexcept>

#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
using namespace std;
#include <vector>
#include <random>
namespace ariel {
    Player p1_("");
    Player p2_("");

    Game::Game() : p1(p1_), p2(p2_), isOn(false) {}

    Game::Game(Player& p1, Player& p2) : p1(p1), p2(p2), isOn(false) {
        this->p1.setHandSize(26);
        this->p2.setHandSize(26);
        this->isOn = false;
    }

    Game::Game(const Game& other) : p1(other.p1), p2(other.p2), isOn(other.isOn) {}

    Game& Game::operator=(const Game& other) {
        if (this == &other) {
            return *this;
        }
        p1 = other.p1;
        p2 = other.p2;
        isOn = other.isOn;
        return *this;
    }

    Game::Game(Game&& other) noexcept : p1(p1_), p2(p2_), isOn(other.isOn) {}


    Game& Game::operator=(Game&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        isOn = other.isOn;
        return *this;
    }
    
    Game::~Game() {}

    void Game::startGame() {
        // Creating new deck
        for(int i=0; i <= 3; i++) {
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
        uniform_int_distribution<> distr(1, 5);
//
        for (int i = 0; i < 2000; i++) {

            int random_num = distr(gen);

            vector<Card> deck1, deck2;

            while (this->deck.size() >= random_num*2) {

                for (int j = 0; j < random_num; j++)
                {
                    deck1.push_back(this->deck.back());
                    deck.pop_back();
                }
                
                for (int j = 0; j < random_num; j++)
                {
                    deck2.push_back(this->deck.back());
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
            this->p1.getHand().push_back(deck.back());
            deck.pop_back();
            this->p2.getHand().push_back(deck.back());
            deck.pop_back();
        }
    }

    void Game::printDeck() {
        for (Card& card : this->deck) {
        std::cout << card.getRank() << std::endl;
        }
    }

    void Game::playTurn() {
        // A game can't start if both players are the same player
        if (&(this->p1) == &(this->p2)) {
            throw runtime_error("Both players are the same");
        }

        if (this->isOn == true && this->p1.stacksize() == 0) {
            // the game is alreay ON but the cards are over: the game is over
            throw runtime_error("The game is already over");
        }

        // The game is ON only when calling the first turn
        if (this->isOn == false) {
            this->isOn = true;
            startGame();
        }

        if (this->p1.getHand().size() == 0) {
            return;
        }

        string turnLog = ""; // This variable documents everything happend during a turn

        Card card1 = this->p1.getHand().back();
        p1.getHand().pop_back();
        this->p1.dropCard();


        Card card2 = this->p2.getHand().back();
        p2.getHand().pop_back();
        this->p2.dropCard();

        turnLog += this->p1.getName() + " played " + to_string(card1.getRank()) + " of " + card1.getShapeName() + " ";
        turnLog += this->p2.getName() + " played " + to_string(card2.getRank()) + " of " + card2.getShapeName() + ". ";

        if (card1.getRank() > card2.getRank()) {
            this->p1.addCardsTaken(2);
            this->roundWins1++;
            turnLog += this->p1.getName() + " wins.";
        }

        else if (card1.getRank() < card2.getRank()) {
            this->p2.addCardsTaken(2);
            this->roundWins2++;
            turnLog += this->p2.getName() + " wins.";
        }

        else { // A draw!
            int totalWin = 2;
            bool vik = false;

            while (p1.getHand().size() > 0 && !vik) {
                turnLog += "draw.";

                // Both players put a "KLAF HAFUH"
                p1.getHand().pop_back();
                this->p1.dropCard();
                p2.getHand().pop_back();
                this->p2.dropCard();

                // Option1: out of cards after putting "KLAF HAFUH" - no winner.
                if (p1.getHand().size() == 0) {
                    break;
                }
                
                card1 = this->p1.getHand().back();
                p1.getHand().pop_back();
                this->p1.dropCard();
                card2 = this->p2.getHand().back();
                p2.getHand().pop_back();
                this->p2.dropCard();

                turnLog += " " + this->p1.getName() + " played " + to_string(card1.getRank()) + " of " + card1.getShapeName();
                turnLog += " " + this->p2.getName() + " played " + to_string(card2.getRank()) + " of " + card2.getShapeName() + ". ";

                totalWin += 4;

                if (card1.getRank() > card2.getRank()) {
                    this->p1.addCardsTaken(totalWin);
                    turnLog += this->p1.getName() + " wins.";
                    this->roundWins1++;
                    vik = true;
                }

                else if (card1.getRank() < card2.getRank()) {
                    this->p2.addCardsTaken(totalWin);
                    turnLog += this->p2.getName() + " wins.";
                    this->roundWins2++;
                    vik = true;
                }

                // Option2: out of cards after another draw - no winner.
                if (p1.getHand().size() == 0) {
                    break;
                }
            }

            // When no one wins - split the potential win for both players.
            // *Including option3, when the while the code didn't get into the while loop.
            if (vik == false) {
                this->p1.addCardsTaken(totalWin / 2);
                this->p2.addCardsTaken(totalWin / 2);            
            }
        }

        this->gameHistory.push_back(turnLog);
    } 
    
    void Game::printLastTurn() {
        cout << this->gameHistory.back() << endl;
    }

    void Game::playAll() {
        while (this->p1.stacksize() > 0) {
            playTurn();
        }

    }
    void Game::printWiner() {

        if (this->p1.cardesTaken() > this->p2.cardesTaken()) {
            cout << this->p1.getName() << endl;
        }

        else if (this->p1.cardesTaken() < this->p2.cardesTaken()) {
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
        double totalRounds = static_cast<double>((this->roundWins1 + this->roundWins2));

        // Estimate each player's current number of cards in hand
        int p1Cards = 26 - this->p1.stacksize() - this->roundWins1 + this->p1.cardesTaken();
        int p2Cards = 26 - this->p2.stacksize() - this->roundWins2 + this->p2.cardesTaken();

        // Estimate the probability of each player winning
        double p1WinProb = static_cast<double>(p1Cards) / 52;
        double p2WinProb = static_cast<double>(p2Cards) / 52;

        cout << this->p1.getName() << "'s stats:" << endl;
        cout << "\tWin rate: " << to_string(static_cast<double>(this->roundWins1) / totalRounds) << "%" << endl;
        cout << "\tCards won: " << to_string(this->p1.cardesTaken()) << endl;
        cout << "\tRounds won: " << to_string(this->roundWins1) << endl;
        cout << "\tChance to win: " << to_string(p1WinProb * 100) << "%" << endl;

        cout << this->p2.getName() << "'s stats:" << endl;
        cout << "\tWin rate: " << to_string(static_cast<double>(this->roundWins2) / totalRounds) << "%" << endl;
        cout << "\tCards won: " << to_string(this->p2.cardesTaken()) << endl;
        cout << "\tRounds won: " << to_string(this->roundWins2) << endl;
        cout << "\tChance to win: " << to_string(p2WinProb * 100) << "%" << endl;

        int drawAmount = (26 - this->p1.stacksize() - this->roundWins1 - this->roundWins2) / 2;
        double drawRate = static_cast<double>(drawAmount) / (this->roundWins1 + this->roundWins2 + drawAmount);

        cout << "Game stats:" << endl;
        cout << "\tDraw rate: " << to_string(drawRate) << "%, draws amount: " << to_string(drawAmount) << endl;
        cout << "\tRounds played: " << this->roundWins1 + this->roundWins2 << endl;
        cout << "\tEach player has " << this->p1.stacksize() << " more cards in his hand" << endl;
    }

    Player Game::getPlayer1() {return this->p1;}
    Player Game::getPlayer2() {return this->p2;}
}