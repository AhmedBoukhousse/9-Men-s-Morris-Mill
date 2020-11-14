#ifndef TST_TESTPIECEREMOVAL_H
#define TST_TESTPIECEREMOVAL_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../src/board.h"

using namespace testing;

TEST(Board, TestPieceRemoval)
{
    Board testBoard;
    testBoard.addPiece(1,1);
    testBoard.addPiece(1,2);
    testBoard.addPiece(1,4);
    testBoard.removePiece(2);
    ASSERT_THAT(testBoard.boardArea[2], Eq(0));
}

TEST(Board, TestPieceRemovalFromMill)
{
    Board testBoard;
    testBoard.addPiece(1,1);
    testBoard.addPiece(1,2);
    testBoard.addPiece(1,0);
    testBoard.addPiece(1,4);
    testBoard.removePiece(2);
    ASSERT_THAT(testBoard.boardArea[2], Eq(1));
}

TEST(Board, TestPieceRemovalFromOnlyMill)
{
    Board testBoard;
    testBoard.addPiece(1,0);
    testBoard.addPiece(1,1);
    testBoard.addPiece(1,2);
    testBoard.addPiece(1,4);
    testBoard.addPiece(1,7);
    testBoard.removePiece(2);
    ASSERT_THAT(testBoard.boardArea[2], Eq(0));
}

TEST(boardTest, countPiecesRemoved)
{
   Board testBoard;
   testBoard.addPiece(1,0);
   testBoard.addPiece(1,1);
   testBoard.removePiece(1);
   ASSERT_THAT(testBoard.playerPiecesAmt[1], Eq(1));
}

#endif // TST_TESTPIECEREMOVAL_H
