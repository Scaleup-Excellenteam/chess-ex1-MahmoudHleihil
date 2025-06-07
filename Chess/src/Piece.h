#pragma once
#include <string>
#include <utility>
#include <memory>

class Board;

class Piece {
public:
    Piece(bool isWhite) : m_isWhite(isWhite) {}
    virtual ~Piece() = default;

    virtual bool isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board& board) const = 0;
    virtual std::unique_ptr<Piece> clone() const = 0;
    bool isWhite() const { return m_isWhite; }

    virtual char getType() const = 0;
    
protected:
    bool m_isWhite;
};