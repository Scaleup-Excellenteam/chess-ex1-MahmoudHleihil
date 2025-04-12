#include "Knight.h"

bool Knight::isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board&) const {
    int dx = std::abs(src.first - dst.first);
    int dy = std::abs(src.second - dst.second);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}