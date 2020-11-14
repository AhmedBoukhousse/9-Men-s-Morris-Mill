#ifndef TST_TESTPIECEPLACEMENT_H
#define TST_TESTPIECEPLACEMENT_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../src/board.h"

using namespace testing;

TEST(boardTest, testPiecePlacementSlot1)
{
    Board testBoard;
    testBoard.addPiece(1,1);
    ASSERT_THAT(testBoard.boardArea[1], Eq(1));
}

TEST(boardTest, testPiecePlacementPlayer2)
{
    Board testBoard;
    testBoard.addPiece(2,4);
    ASSERT_THAT(testBoard.boardArea[4], Eq(2));
}

TEST(boardTest, testPiecePlacementNoneLeft)
{
    Board testBoard;
    testBoard.playerPiecesAmt[1] = 9;
    testBoard.addPiece(1,4);
    ASSERT_THAT(testBoard.boardArea[4], Eq(0));
}

TEST(boardTest, testNoLegalMoves)
{
    Board testBoard;
    testBoard.addPiece(1,0);
    testBoard.addPiece(2,1);
    testBoard.addPiece(1,2);
    testBoard.addPiece(1,3);
    testBoard.addPiece(2,4);
    testBoard.addPiece(1,5);
    testBoard.addPiece(2,9);
    testBoard.addPiece(2,10);
    testBoard.addPiece(2,12);
    testBoard.addPiece(2,13);
    testBoard.addPiece(2,14);
    testBoard.addPiece(1,18);
    testBoard.addPiece(2,19);
    testBoard.addPiece(1,20);
    testBoard.addPiece(1,21);
    testBoard.addPiece(2,22);
    testBoard.addPiece(1,23);
    ASSERT_FALSE(testBoard.hasLegalMoves(1));
}

TEST(boardTest, testLegalMoves)
{
    Board testBoard;
    testBoard.addPiece(1,0);
    testBoard.addPiece(2,1);
    testBoard.addPiece(1,2);
    ASSERT_TRUE(testBoard.hasLegalMoves(1));
}

TEST(boardTest, testAddingTooMany)
{
    Board testBoard;
    testBoard.addPiece(1,0);
    testBoard.addPiece(1,1);
    testBoard.addPiece(1,2);
    testBoard.addPiece(1,3);
    testBoard.addPiece(1,4);
    testBoard.addPiece(1,5);
    testBoard.addPiece(1,6);
    testBoard.addPiece(1,7);
    testBoard.addPiece(1,8);
    testBoard.addPiece(1,9);
    ASSERT_THAT(testBoard.boardArea[9], Eq(0));
}

TEST(boardTest, countPieces)
{
   Board testBoard;
   testBoard.addPiece(1,0);
   testBoard.addPiece(1,1);
   ASSERT_THAT(testBoard.playerPiecesAmt[1], Eq(2));
}

#endif // TST_TESTPIECEPLACEMENT_H
