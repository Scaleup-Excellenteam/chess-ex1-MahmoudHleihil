#include "Rook.h"
#include "Board.h"

bool Rook::isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board& board) const {
    if (src.first != dst.first && src.second != dst.second)
        return false;
    return board.isPathClear(src, dst);
}