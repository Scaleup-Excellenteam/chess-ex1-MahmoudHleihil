#pragma once
#include <string>
#include <vector>
#include "Board.h"
#include "Piece.h"

class GameManager {
public:
    GameManager(const std::string& board);
    int evaluateMove(const std::string& input);
    bool isWhiteTurn() const;

    std::vector<std::string> getAllLegalMoves() const;
    const Piece* getPiece(int row, int col) const;
    bool isCheck(bool white) const;
    
private:
    Board m_board;
    bool m_turnWhite;
};
