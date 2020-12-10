#ifndef TST_TESTGAMEOVER_H
#define TST_TESTGAMEOVER_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../src/board.h"

using namespace testing;

TEST(gameOverTest, testEndPlayer1Blocked)
{
    Board testBoard;
    testBoard.addPiece(1,0);
    testBoard.addPiece(1,1);
    testBoard.addPiece(1,2);
    testBoard.addPiece(1,3);
    testBoard.addPiece(2,4);
    testBoard.addPiece(2,9);
    testBoard.addPiece(2,10);
    testBoard.addPiece(2,7);
    testBoard.addPiece(2,14);
    int scenario = testBoard.GameOver();
    ASSERT_THAT(scenario, Eq(1));
}

TEST(gameOverTest, testEndPlayer2Blocked)
{
    Board testBoard;
    testBoard.addPiece(2,0);
    testBoard.addPiece(2,1);
    testBoard.addPiece(2,2);
    testBoard.addPiece(2,3);
    testBoard.addPiece(1,4);
    testBoard.addPiece(1,9);
    testBoard.addPiece(1,10);
    testBoard.addPiece(1,7);
    testBoard.addPiece(1,14);
    int scenario = testBoard.GameOver();
    ASSERT_THAT(scenario, Eq(2));
}

TEST(gameOverTest, testEndPlayer1TooLittlePieces)
{
    Board testBoard;
    testBoard.addPiece(1,0);
    testBoard.addPiece(1,2);
    int scenario = testBoard.GameOver();
    ASSERT_THAT(scenario, Eq(3));

}

TEST(gameOverTest, testEndPlayer2TooLittlePieces)
{
    Board testBoard;
    testBoard.addPiece(1,14);
    testBoard.addPiece(1,12);
    testBoard.addPiece(1,17);
    testBoard.addPiece(1,2);
    testBoard.addPiece(2,0);
    testBoard.addPiece(2,2);
    int scenario = testBoard.GameOver();
    ASSERT_THAT(scenario, Eq(4));
}

TEST(gameOverTest, testNotOver)
{
    Board testBoard;
    testBoard.addPiece(2,0);
    testBoard.addPiece(2,2);
    testBoard.addPiece(2,4);
    testBoard.addPiece(1,22);
    testBoard.addPiece(1,15);
    testBoard.addPiece(1,13);
    int scenario = testBoard.GameOver();
    ASSERT_THAT(scenario, Eq(5));
}

#endif // TST_TESTGAMEOVER_H
