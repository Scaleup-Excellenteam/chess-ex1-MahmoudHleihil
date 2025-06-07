#pragma once
#include <string>
#include "GameManager.h"

namespace ChessAI {
    std::string getBestMove(GameManager& gm, bool isWhite, int threadCount = 8, int depth = 2);
    int evaluateBoard(const GameManager& gm);
    int minimax(GameManager gm, int depth, bool maximizingPlayer, int alpha, int beta);
}