#ifndef TST_TESTPIECEMOVEMENT_H
#define TST_TESTPIECEMOVEMENT_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../src/board.h"

using namespace testing;


TEST(boardTest, testPieceMovementToBlankIsFirstSpotClear)
{
    Board testBoard;
    testBoard.addPiece(1,4);
    testBoard.swapPiece(1,4,5);
    ASSERT_THAT(testBoard.boardArea[4], Eq(0));
}

TEST(boardTest, testPieceMovementToBlankIsSecondSpotFilled)
{
    Board testBoard;
    testBoard.addPiece(1,4);
    testBoard.swapPiece(1,4,5);
    ASSERT_THAT(testBoard.boardArea[5], Eq(1));
}

TEST(boardTest, testPieceMovementToOccupied)
{
    Board testBoard;
    testBoard.addPiece(2,4);
    testBoard.addPiece(1,5);
    testBoard.swapPiece(1,5,4);
    ASSERT_THAT(testBoard.boardArea[4], Eq(2));
}

TEST(boardTest, testMill)
{
    Board testBoard;
    testBoard.addPiece(1,1);
    testBoard.addPiece(1,2);
    testBoard.addPiece(1,0);
    ASSERT_THAT(testBoard.checkMill(2), Eq(1));
}

TEST(boardTest, testNoMill)
{
    Board testBoard;
    testBoard.addPiece(1,1);
    testBoard.addPiece(2,2);
    testBoard.addPiece(1,0);
    ASSERT_THAT(testBoard.checkMill(2), Eq(0));
}

TEST(boardTest, testFlight)
{
    Board testBoard;
    testBoard.addPiece(1,1);
    testBoard.addPiece(1,2);
    testBoard.addPiece(1,0);
    testBoard.swapPiece(1,2,22);
    ASSERT_THAT(testBoard.boardArea[22], Eq(1));
}

TEST(boardTest, testNoFlight)
{
    Board testBoard;
    testBoard.addPiece(1,1);
    testBoard.addPiece(1,2);
    testBoard.addPiece(1,0);
    testBoard.addPiece(1,5);
    testBoard.swapPiece(1,2,22);
    ASSERT_THAT(testBoard.boardArea[22], Eq(0));
}


#endif // TST_TESTPIECEMOVEMENT_H


