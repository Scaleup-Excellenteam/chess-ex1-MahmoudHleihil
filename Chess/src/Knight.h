#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(bool isWhite) : Piece(isWhite) {}
    bool isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board& board) const override;
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Knight>(*this); }
};