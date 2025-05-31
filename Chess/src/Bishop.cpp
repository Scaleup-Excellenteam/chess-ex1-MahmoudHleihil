#include "Bishop.h"
#include "Board.h"

bool Bishop::isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board& board) const {
    if (std::abs(src.first - dst.first) != std::abs(src.second - dst.second))
        return false;
    return board.isPathClear(src, dst);
}
