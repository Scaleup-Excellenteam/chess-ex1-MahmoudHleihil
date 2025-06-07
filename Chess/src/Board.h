#pragma once
#include <vector>
#include <memory>
#include "Piece.h"

class Board {
public:
    Board(const std::string& boardStr);
    Board(const Board& other);
    const Piece* getPieceAt(int row, int col) const;
    Piece* getPieceAt(int row, int col);
    bool isPathClear(const std::pair<int, int>& src, const std::pair<int, int>& dst) const;
    bool isCheck(bool forWhite) const;
    void movePiece(const std::pair<int, int>& src, const std::pair<int, int>& dst);
    std::pair<int, int> findKing(bool white) const;
    bool canCastle(bool white, bool kingSide) const;

private:
    std::vector<std::vector<std::unique_ptr<Piece>>> m_board;

    bool whiteKingMoved;
    bool blackKingMoved;
    bool whiteLeftRookMoved;
    bool whiteRightRookMoved;
    bool blackLeftRookMoved;
    bool blackRightRookMoved;
};
