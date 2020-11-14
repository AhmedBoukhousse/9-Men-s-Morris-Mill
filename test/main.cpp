#include "tst_testpieceplacement.h"
#include "tst_testPieceMovement.h"
#include "tst_testPieceRemoval.h"
#include "tst_testGameOver.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
