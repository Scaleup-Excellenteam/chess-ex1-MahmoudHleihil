#include "ChessAI.h"
#include <vector>
#include <string>
#include <limits>
#include <cctype>

namespace ChessAI {

int getPieceValue(char piece) {
    switch (tolower(piece)) {
        case 'p': return 1;
        case 'n': case 'b': return 3;
        case 'r': return 5;
        case 'q': return 9;
        default: return 0;
    }
}

int evaluateBoard(const GameManager& gm) {
    int score = 0;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            const auto* p = gm.getPiece(row, col);
            if (!p) continue;
            int val = getPieceValue(p->getType());
            score += p->isWhite() ? val : -val;
        }
    }
    return score;
}

int minimax(GameManager gm, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 0) return evaluateBoard(gm);

    auto moves = gm.getAllLegalMoves();
    if (moves.empty()) return gm.isCheck(maximizingPlayer) ? -10000 : 0;

    int best = maximizingPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (const auto& move : moves) {
        GameManager temp = gm;
        temp.evaluateMove(move);
        int score = minimax(temp, depth - 1, !maximizingPlayer, alpha, beta);

        if (maximizingPlayer) {
            best = std::max(best, score);
            alpha = std::max(alpha, score);
        } else {
            best = std::min(best, score);
            beta = std::min(beta, score);
        }

        if (beta <= alpha) break;
    }
    return best;
}

std::string getBestMove(GameManager& gm, bool isWhite, int threadCount, int depth) {
    auto moves = gm.getAllLegalMoves();
    std::string bestMove;
    int bestScore = std::numeric_limits<int>::min();

    for (const auto& move : moves) {
        GameManager temp = gm;
        temp.evaluateMove(move);
        int score = minimax(temp, depth - 1, false, -10000, 10000);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

} // namespace ChessAI
