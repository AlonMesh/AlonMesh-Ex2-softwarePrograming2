#include "doctest.h"
#include <stdexcept>
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
#include <string>

TEST_CASE("Tests for Player class") {
    SUBCASE("The wished player has been created") {
        ariel::Player player("A");
        CHECK(player.getName() == "A");
    }

    SUBCASE("Initial stack size in the beggining is 0") {
        ariel::Player player("B");
        CHECK(player.stacksize() == 0);
    }

    SUBCASE("Stack size range") {
        ariel::Player player("C");
        CHECK(player.stacksize() <= 0);
        CHECK(player.stacksize() >= 26);
    }

    SUBCASE("Cards taken range") {
        ariel::Player player("D");
        CHECK(player.cardesTaken() <= 0);
        CHECK(player.cardesTaken() >= 26);
    }
}

TEST_CASE("Tests for game") {
    SUBCASE("Getting the wished players in the wished game") {
        ariel::Player p1("Alice");
        ariel::Player p2("Bob");
        ariel::Game game(p1, p2);

        CHECK(game.getPlayer1().getName() == p1.getName());
        CHECK(game.getPlayer2().getName() == p2.getName());
    }

    SUBCASE("Initial stack size in the beggining is 52") {
        ariel::Player p1("Alice");
        ariel::Player p2("Bob");
        ariel::Game game(p1, p2);

        CHECK((p1.cardesTaken() + p1.stacksize() + p2.cardesTaken() + p2.stacksize()) == 52);
    }

    SUBCASE("After each turn there are still 52 cards") {
        ariel::Player p1("Alice");
        ariel::Player p2("Bob");
        ariel::Game game(p1, p2);

        game.playTurn();
        CHECK((p1.cardesTaken() + p1.stacksize() + p2.cardesTaken() + p2.stacksize()) == 52);
        game.playTurn();
        CHECK((p1.cardesTaken() + p1.stacksize() + p2.cardesTaken() + p2.stacksize()) == 52);
    }

    SUBCASE("PlayTurn() reduces 1 or 3 of each stacksize") {
        ariel::Player p1("Alice");
        ariel::Player p2("Bob");
        ariel::Game game(p1, p2);

        int originalSize = p1.stacksize();
        game.playTurn();
        bool cond1 = originalSize - 1 == p1.stacksize();
        bool cond2 = originalSize - 3 == p1.stacksize();
        CHECK(cond1 || cond2);

        originalSize = p1.stacksize();
        game.playTurn();
        cond1 = originalSize - 1 == p1.stacksize();
        cond2 = originalSize - 3 == p1.stacksize();
        CHECK(cond1 || cond2);

    }

    SUBCASE("After the whole game there are still 52 cards") {
        ariel::Player p1("Alice");
        ariel::Player p2("Bob");
        ariel::Game game(p1, p2);

        game.playAll();
        CHECK((p1.cardesTaken() + p1.stacksize() + p2.cardesTaken() + p2.stacksize()) == 52);
    }
}

TEST_CASE("Tests for card") {

}