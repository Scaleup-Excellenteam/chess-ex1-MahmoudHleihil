#include "King.h"
#include "Board.h"
#include <cmath>

bool King::isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board& board) const {
    int dx = std::abs(src.first - dst.first);
    int dy = std::abs(src.second - dst.second);

    if (dx <= 1 && dy <= 1) return true;

    if (src.second == dst.second && dx == 2) {
        bool kingSide = dst.first > src.first;
        return board.canCastle(isWhite(), kingSide);
    }

    return false;
}
