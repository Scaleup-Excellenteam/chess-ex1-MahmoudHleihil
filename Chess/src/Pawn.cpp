#include "Pawn.h"
#include "Board.h"

bool Pawn::isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board& board) const {
    int direction = isWhite() ? 1 : -1; // White moves down the board, black moves up
    int startRow = isWhite() ? 1 : 6;
    int dy = dst.first - src.first;
    int dx = std::abs(dst.second - src.second);

    auto destPiece = board.getPieceAt(dst.first, dst.second);

    // Single step forward
    if (dy == 0 && dx == direction && !destPiece)
        return true;

    // Double step from starting position
    if (dy == 0 && dx == 2 * direction && src.first == startRow &&
        !destPiece && !board.getPieceAt(src.first + direction, src.second))
        return true;

    // Diagonal capture
    if (dy == 1 && dx == direction && destPiece && destPiece->isWhite() != isWhite())
        return true;

    return false;
}
