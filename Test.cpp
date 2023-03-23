#include "doctest.h"
#include <stdexcept>
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
#include <string>

TEST_CASE("The wished player has been created") { //1
    ariel::Player player("Avner");
    CHECK(player.getName() == "Avner");
}

TEST_CASE("Initial STACK SIZE of player before entering a game is 0") { //2
    ariel::Player player("Avner");
    CHECK(player.stacksize() == 0);
}

TEST_CASE("Initial CARDS TAKEN of player before entering a game is 0") { //3
    ariel::Player player("Avner");
    CHECK(player.cardesTaken() == 0);
}

TEST_CASE("STACK SIZE is always in the range (0,26) included") { //4
    ariel::Player p1("Avner");
    CHECK(p1.stacksize() >= 0);
    CHECK(p1.stacksize() <= 26);

    ariel::Player p2("Benny");
    ariel::Game game(p1, p2);

    for (int i = 0; i < 5; i++)
    {
        game.playTurn();
        CHECK(p1.stacksize() >= 0);
        CHECK(p1.stacksize() <= 26);
    }
}

TEST_CASE("CARDS TAKEN is always in the range (0,26) included") { //5
    ariel::Player p1("Avner");
    CHECK(p1.cardesTaken() >= 0);
    CHECK(p1.cardesTaken() <= 26);

    ariel::Player p2("Benny");
    ariel::Game game(p1, p2);

    for (int i = 0; i < 5; i++)
    {
        game.playTurn();
        CHECK(p1.cardesTaken() >= 0);
        CHECK(p1.cardesTaken() <= 26);
    }
}

TEST_CASE("The wished players are fields of a given game") { //6
    ariel::Player p1("Avner");
    ariel::Player p2("Benny");
    ariel::Game game(p1, p2);

    CHECK(game.getPlayer1().getName() == p1.getName());
    CHECK(game.getPlayer2().getName() == p2.getName());
}

TEST_CASE("When the game begins the deck is shuffled correctly - each player gets half of the cards") { //7
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
}

TEST_CASE("When the game ends each player has no cards") { //8
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    game.playAll();

    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
}

TEST_CASE("After each turn there are still 52 cards") { //9
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    game.playTurn();
    CHECK((p1.cardesTaken() + p1.stacksize() + p2.cardesTaken() + p2.stacksize()) == 52);
    game.playTurn();
    CHECK((p1.cardesTaken() + p1.stacksize() + p2.cardesTaken() + p2.stacksize()) == 52);
}

TEST_CASE("PlayTurn() reduces 1 or 3 cards of each STACK SIZE") { //10
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    for (int i = 0; i < 3; i++)
    {
        int originalSize = p1.stacksize();
        game.playTurn();
        bool cond1 = originalSize - 1 == p1.stacksize();
        bool cond2 = originalSize - 3 == p1.stacksize();
        bool finalBool = cond1 || cond2;
        CHECK(finalBool);
    }
}

TEST_CASE("PlayTurn() grants 2 or 6 cards to specific CARDS TAKEN") { // original 1 or 3 and the other 1 or 3 //11
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Game game(p1, p2);

    for (int i = 0; i < 3; i++)
    {
        int originalSize1 = p1.cardesTaken();
        int originalSize2 = p2.cardesTaken();
        game.playTurn();
        bool cond1 = (originalSize1 + 2 == p1.cardesTaken() && originalSize2 == p2.cardesTaken());
        bool cond2 = (originalSize1 + 6 == p1.cardesTaken() && originalSize2 == p2.cardesTaken());
        bool cond3 = (originalSize2 + 2 == p2.cardesTaken() && originalSize1 == p1.cardesTaken());
        bool cond4 = (originalSize2 + 6 == p2.cardesTaken() && originalSize1 == p1.cardesTaken());
        CHECK((cond1 || cond2 || cond3 || cond4));
    }
}

TEST_CASE("After the whole game there are still 52 cards") { //12
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



//card are done in the middle of the game