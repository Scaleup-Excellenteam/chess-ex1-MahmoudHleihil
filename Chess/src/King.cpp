#include "King.h"
#include <cmath>

bool King::isLegalMove(const std::pair<int, int>& src, const std::pair<int, int>& dst, const Board&) const {
    int dx = std::abs(src.first - dst.first);
    int dy = std::abs(src.second - dst.second);
    return dx <= 1 && dy <= 1;
}