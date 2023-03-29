#include "doctest.h"
#include <stdexcept>
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
#include <string>

TEST_CASE("The wished player has been created") {
    ariel::Player player("Alice");
    CHECK(player.getName() == "Alice");
}

TEST_CASE("Initial STACK SIZE of player before entering a game is 0") { 
    ariel::Player player("Alice");
    CHECK(player.stacksize() == 0);
}

TEST_CASE("Initial CARDS TAKEN of player before entering a game is 0") { 
    ariel::Player player("Alice");
    CHECK(player.cardesTaken() == 0);
}

TEST_CASE("STACK SIZE is always in the range (0,26) included") { 
    ariel::Player p1("Alice");
    CHECK(p1.stacksize() >= 0);
    CHECK(p1.stacksize() <= 26);

    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    for (int i = 0; i < 5; i++)
    {
        game.playTurn();
        CHECK(p1.stacksize() >= 0);
        CHECK(p1.stacksize() <= 26);
    }
}

TEST_CASE("CARDS TAKEN is always in the range (0,26) included") {
    ariel::Player p1("Alice");
    CHECK(p1.cardesTaken() >= 0);
    CHECK(p1.cardesTaken() <= 26);

    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    for (int i = 0; i < 5; i++)
    {
        game.playTurn();
        CHECK(p1.cardesTaken() >= 0);
        CHECK(p1.cardesTaken() <= 26);
    }
}

TEST_CASE("The wished players are fields of a given game") {
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    CHECK(game.getPlayer1().getName() == p1.getName());
    CHECK(game.getPlayer2().getName() == p2.getName());
}

TEST_CASE("Player can play in an unique game") {
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    ariel::Player p3("Charlie");
    ariel::Game game2(p1, p3);
    CHECK_THROWS(game2.playTurn());
    CHECK_THROWS(game2.playAll());
    CHECK_THROWS(game2.getPlayer1());
    CHECK_THROWS(game2.getPlayer2());
}

TEST_CASE("When the game begins the deck is shuffled correctly - each player gets half of the cards") {
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
}

TEST_CASE("When the game ends each player has no cards") {
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    game.playAll();

    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
}

TEST_CASE("After each turn there are still 52 cards") {
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    game.playTurn();
    CHECK((p1.cardesTaken() + p1.stacksize() + p2.cardesTaken() + p2.stacksize()) == 52);
    game.playTurn();
    CHECK((p1.cardesTaken() + p1.stacksize() + p2.cardesTaken() + p2.stacksize()) == 52);
}

TEST_CASE("After the whole game there are still 52 cards") {
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    game.playAll();
    CHECK((p1.cardesTaken() + p1.stacksize() + p2.cardesTaken() + p2.stacksize()) == 52);
}

TEST_CASE("Winner is set only after the game is over") {
  ariel::Player p1("Alice");
  ariel::Player p2("Bob");
  ariel::Game game(p1, p2); 

  CHECK_THROWS(game.printWiner()); // should throw exeption cuz the game isn't done.
}

TEST_CASE("Printing turns and logs is possible only after the first turn") {
  ariel::Player p1("Alice");
  ariel::Player p2("Bob");
  ariel::Game game(p1, p2); 

  CHECK_THROWS(game.printLastTurn()); // should throw exeption cuz there wasn't turns yet.
  CHECK_THROWS(game.printLog());
}