#include "pch.h"



Board testBoard;

TEST(TestCastling, Castling) {
    EXPECT_EQ(false, testBoard.castling(0, c));
    EXPECT_EQ(false, testBoard.castling(0, g));
    EXPECT_EQ(false, testBoard.castling(7, c));
    EXPECT_EQ(false, testBoard.castling(7, g));
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            delete testBoard.pieces_[i][j];
            testBoard.pieces_[i][j] = 0;
        }
    testBoard.pieces_[0][4] = new King(0, 4, white);
    testBoard.whiteKing_ = testBoard.pieces_[0][4];
    testBoard.pieces_[7][4] = new King(7, 4, black);
    testBoard.blackKing_ = testBoard.pieces_[7][4];
    testBoard.pieces_[0][0] = new Rook(0, 0, white);
    testBoard.pieces_[0][7] = new Rook(0, 7, white);
    testBoard.pieces_[7][0] = new Rook(7, 0, black);
    testBoard.pieces_[7][7] = new Rook(7, 7, black);
    EXPECT_EQ(true, testBoard.castling(0, c));
    EXPECT_EQ(true, testBoard.castling(7, g));
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            delete testBoard.pieces_[i][j];
            testBoard.pieces_[i][j] = 0;
        }
    testBoard.pieces_[0][4] = new King(0, 4, white);
    testBoard.whiteKing_ = testBoard.pieces_[0][4];
    testBoard.pieces_[7][4] = new King(7, 4, black);
    testBoard.blackKing_ = testBoard.pieces_[7][4];
    testBoard.pieces_[0][7] = new Rook(0, 7, white);
    testBoard.pieces_[7][7] = new Rook(7, 7, black);
    EXPECT_EQ(true, testBoard.castling(0, g));
    EXPECT_EQ(false, testBoard.castling(7, g));
}
