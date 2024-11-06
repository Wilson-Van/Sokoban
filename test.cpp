// Copyright 2024 Wilson Van

#include <iostream>
#include <string>

#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

BOOST_AUTO_TEST_CASE(moveOffScreen) {
    SB::Sokoban s;
    std::ifstream lvl("sokoban/pushdown.lvl");
    lvl >> s;
    s.movePlayer(SB::Up);
    s.movePlayer(SB::Up);
    s.movePlayer(SB::Up);
    BOOST_REQUIRE_EQUAL(s.playerLoc().x, 2);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 0);
}

BOOST_AUTO_TEST_CASE(moveIntoWall) {
    SB::Sokoban s;
    std::ifstream lvl("sokoban/level5.lvl");
    lvl >> s;
    s.movePlayer(SB::Left);
    BOOST_REQUIRE_EQUAL(s.playerLoc().x, 1);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 6);

    s.movePlayer(SB::Down);
    BOOST_REQUIRE_EQUAL(s.playerLoc().x, 1);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 6);

    for (int i = 0; i < 7; i++) {
        s.movePlayer(SB::Right);
    }
    BOOST_REQUIRE_EQUAL(s.playerLoc().x, 6);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 6);

    for (int i = 0; i < 7; i++) {
        s.movePlayer(SB::Up);
    }
    BOOST_REQUIRE_EQUAL(s.playerLoc().x, 6);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 1);
}

BOOST_AUTO_TEST_CASE(moveBoxIntoWall) {
    SB::Sokoban s;
    std::ifstream lvl("sokoban/level2.lvl");
    lvl >> s;
    std::string moves = "rrulluuuldd";
    for (int i = 0; i < 11; i++) {
        if (moves[i] == 'r') s.movePlayer(SB::Right);
        if (moves[i] == 'l') s.movePlayer(SB::Left);
        if (moves[i] == 'u') s.movePlayer(SB::Up);
        if (moves[i] == 'd') s.movePlayer(SB::Down);
    }
    BOOST_REQUIRE_EQUAL(s.playerLoc().x, 7);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 3);
}

BOOST_AUTO_TEST_CASE(moveBoxOffMap) {
    SB::Sokoban s;
    std::ifstream lvl("sokoban/pushup.lvl");
    lvl >> s;
    s.movePlayer(SB::Up);
    s.movePlayer(SB::Up);
    BOOST_REQUIRE_EQUAL(s.playerLoc().x, 2);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 1);
}


BOOST_AUTO_TEST_CASE(winCondtion) {
    SB::Sokoban s1;
    std::ifstream lvl1("sokoban/pushup.lvl");
    lvl1 >> s1;
    s1.movePlayer(SB::Up);
    BOOST_REQUIRE_EQUAL(s1.isWon(), true);
    SB::Sokoban s2;
    std::ifstream lvl2("sokoban/autowin.lvl");
    lvl2 >> s2;
    BOOST_REQUIRE_EQUAL(s2.isWon(), true);
    SB::Sokoban s3;
    std::ifstream lvl3("sokoban/level6.lvl");
    lvl3 >> s3;
    std::string firstMoves = "urrrrurdlllluuurul";
    for (int i = 0; i < 19; i++) {
        if (firstMoves[i] == 'r') s3.movePlayer(SB::Right);
        if (firstMoves[i] == 'l') s3.movePlayer(SB::Left);
        if (firstMoves[i] == 'u') s3.movePlayer(SB::Up);
        if (firstMoves[i] == 'd') s3.movePlayer(SB::Down);
    }
    BOOST_REQUIRE_EQUAL(s3.isWon(), true);
    SB::Sokoban s4;
    std::ifstream lvl4("sokoban/level5.lvl");
    lvl4 >> s4;
    std::string secondMoves = "urrrrdruuuu";
    for (int i = 0; i < 12; i++) {
        if (secondMoves[i] == 'r') s4.movePlayer(SB::Right);
        if (secondMoves[i] == 'l') s4.movePlayer(SB::Left);
        if (secondMoves[i] == 'u') s4.movePlayer(SB::Up);
        if (secondMoves[i] == 'd') s4.movePlayer(SB::Down);
    }
    BOOST_REQUIRE_EQUAL(s4.isWon(), true);
}
