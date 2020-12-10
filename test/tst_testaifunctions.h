#ifndef TST_TESTAIFUNCTIONS_H
#define TST_TESTAIFUNCTIONS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../src/board.h"
#include "../src/computerPlayer.h"

using namespace testing;

TEST(AI, TestPieceAddition)
{
    Board testBoard;
    computerPlayer testAI;
    testBoard.boardArea[0] = 1;
    testAI.updateHumanVectors(0,-1,testBoard);
    testBoard.boardArea[1] = 1;
    testAI.updateHumanVectors(1,-1,testBoard);
    int pieceToAdd = testAI.AIPlacePiece(testBoard);
    testBoard.addPiece(2,pieceToAdd);
    ASSERT_THAT(testBoard.boardArea[2],Eq(2));
}

TEST(AI, TestPieceMovement)
{
    int overallProgress = 0;
    Board testBoard;
    computerPlayer testAI;

    testBoard.boardArea[0] = 1;
    testAI.updateHumanVectors(0,-1,testBoard);
    testBoard.boardArea[1] = 1;
    testAI.updateHumanVectors(1,-1,testBoard);
    testBoard.boardArea[6] = 1;
    testAI.updateHumanVectors(6,-1,testBoard);

    testBoard.boardArea[21] = 2;
    testAI.updateAIVectors(21,-1,testBoard);
    testBoard.boardArea[16] = 2;
    testAI.updateAIVectors(16,-1,testBoard);
    testBoard.boardArea[13] = 2;
    testAI.updateAIVectors(13,-1,testBoard);

    pair<int,int> piecesToMove = testAI.AIMovePiece(testBoard);
    testBoard.movePiece(2,piecesToMove.first,piecesToMove.second);

    if(testBoard.boardArea[21] == 0 || testBoard.boardArea[16] == 0 || testBoard.boardArea[13] == 0)
        overallProgress++;
    for(int i = 0; i < 24; i++)
    {
        if(testBoard.boardArea[i] == 2)
            overallProgress++;
    }
    ASSERT_THAT(overallProgress,Eq(4));
}

TEST(AI, TestPieceFlight)
{
    int overallProgress = 0;
    Board testBoard;
    computerPlayer testAI;

    testBoard.boardArea[0] = 1;
    testAI.updateHumanVectors(0,-1,testBoard);
    testBoard.boardArea[1] = 1;
    testAI.updateHumanVectors(1,-1,testBoard);
    testBoard.boardArea[6] = 1;
    testAI.updateHumanVectors(6,-1,testBoard);

    testBoard.playerPiecesAmt[2] = 3;
    testBoard.boardArea[21] = 2;
    testAI.updateAIVectors(21,-1,testBoard);
    testBoard.boardArea[22] = 2;
    testAI.updateAIVectors(22,-1,testBoard);
    testBoard.boardArea[13] = 2;
    testAI.updateAIVectors(13,-1,testBoard);

    pair<int,int> piecesToFly = testAI.AIFlyPiece(testBoard);
    testBoard.movePiece(2,piecesToFly.first,piecesToFly.second);

    if(testBoard.boardArea[piecesToFly.first] == 0)
        overallProgress++;

    for(int i = 0; i < 24; i++)
    {
        if(testBoard.boardArea[i] == 2)
            overallProgress++;
    }
    ASSERT_THAT(overallProgress,Eq(4));
}

TEST(AI, TestPieceRemoval)
{
    int overallProgress = 0;
    Board testBoard;
    computerPlayer testAI;
    testBoard.playerPiecesAmt[1] = 3;

    //player
    testBoard.boardArea[0] = 1;
    testAI.updateHumanVectors(0,-1,testBoard);
    testBoard.boardArea[1] = 1;
    testAI.updateHumanVectors(1,-1,testBoard);
    testBoard.boardArea[6] = 1;
    testAI.updateHumanVectors(6,-1,testBoard);

    //AI
    testBoard.boardArea[3] = 2;
    testAI.updateAIVectors(3,-1,testBoard);
    testBoard.boardArea[4] = 2;
    testAI.updateAIVectors(4,-1,testBoard);
    testBoard.boardArea[5] = 2;
    testAI.updateAIVectors(5,-1,testBoard);

    int pieceToRemove = testAI.AIRemovePiece(testBoard);
    testBoard.removePiece(pieceToRemove);

    for(int i = 0; i < 24; i++)
    {
        if(testBoard.boardArea[i] == 1)
            overallProgress++;
    }
    ASSERT_THAT(overallProgress,Eq(2));
}

TEST(AI, TestAdjacencyChecks)
{
    Board testBoard;
    computerPlayer testAI;
    testBoard.boardArea[0] = 2;
    int pos2 = testAI.canBeReached(1,testBoard);
    ASSERT_THAT(pos2,Eq(0));
}

#endif // TST_TESTAIFUNCTIONS_H
