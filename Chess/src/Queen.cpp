#include "Queen.h"
#include "Board.h"

bool Queen::isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board& board) const {
    if (src == dst)
        return false;

    if (src.first == dst.first || src.second == dst.second ||
        std::abs(src.first - dst.first) == std::abs(src.second - dst.second)) {
        return board.isPathClear(src, dst);
    }
    return false;
}
