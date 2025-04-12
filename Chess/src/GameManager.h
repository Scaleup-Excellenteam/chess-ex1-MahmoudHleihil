#pragma once
#include "Board.h"
#include <string>

class GameManager {
public:
    GameManager(const std::string& board);
    int evaluateMove(const std::string& input);
private:
    Board m_board;
    bool m_turnWhite;
};