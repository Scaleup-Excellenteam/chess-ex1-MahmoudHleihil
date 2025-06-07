#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(bool isWhite) : Piece(isWhite) {}
    bool isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board& board) const override;
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Bishop>(*this); }
    char getType() const override { return isWhite() ? 'B' : 'b'; }

};