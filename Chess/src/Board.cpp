#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"

Board::Board(const std::string& boardStr) {
    m_board.resize(8);
    for (auto& row : m_board)
        row.resize(8);

    for (int i = 0; i < 64; ++i) {
        char c = boardStr[i];
        if (c == '#') continue;
        bool isWhite = std::isupper(c);
        c = std::tolower(c);
        int row = i / 8, col = i % 8;
        if (c == 'r') m_board[row][col] = std::make_unique<Rook>(isWhite);
        else if (c == 'k') m_board[row][col] = std::make_unique<King>(isWhite);
        else if (c == 'b') m_board[row][col] = std::make_unique<Bishop>(isWhite);
        else if (c == 'n') m_board[row][col] = std::make_unique<Knight>(isWhite);
        else if (c == 'q') m_board[row][col] = std::make_unique<Queen>(isWhite);
        else if (c == 'p') m_board[row][col] = std::make_unique<Pawn>(isWhite);
    }

    whiteKingMoved = blackKingMoved = false;
    whiteLeftRookMoved = whiteRightRookMoved = false;
    blackLeftRookMoved = blackRightRookMoved = false;
}

Board::Board(const Board& other) : m_board(8) {
    for (int i = 0; i < 8; ++i) {
        m_board[i].resize(8);
        for (int j = 0; j < 8; ++j) {
            if (other.m_board[i][j])
                m_board[i][j] = other.m_board[i][j]->clone();
        }
    }
    whiteKingMoved = other.whiteKingMoved;
    blackKingMoved = other.blackKingMoved;
    whiteLeftRookMoved = other.whiteLeftRookMoved;
    whiteRightRookMoved = other.whiteRightRookMoved;
    blackLeftRookMoved = other.blackLeftRookMoved;
    blackRightRookMoved = other.blackRightRookMoved;
}

const Piece* Board::getPieceAt(int row, int col) const {
    return m_board[row][col].get();
}

Piece* Board::getPieceAt(int row, int col) {
    return m_board[row][col].get();
}

bool Board::isPathClear(const std::pair<int, int>& src, const std::pair<int, int>& dst) const {
    int dr = (dst.first > src.first) - (dst.first < src.first);
    int dc = (dst.second > src.second) - (dst.second < src.second);
    int r = src.first + dr, c = src.second + dc;
    while (r != dst.first || c != dst.second) {
        if (getPieceAt(r, c)) return false;
        r += dr; c += dc;
    }
    return true;
}

void Board::movePiece(const std::pair<int, int>& src, const std::pair<int, int>& dst) {
    auto* piece = getPieceAt(src.first, src.second);
    if (!piece) return;

    // עדכון דגלי תזוזת כלים
    if (auto king = dynamic_cast<King*>(piece)) {
        if (piece->isWhite()) whiteKingMoved = true;
        else blackKingMoved = true;

        int dx = dst.first - src.first;
        if (std::abs(dx) == 2) {
            // ביצוע צרחה בפועל
            if (dx > 0) {
                // kingside
                movePiece({src.first, 7}, {src.first, 5});
            } else {
                // queenside
                movePiece({src.first, 0}, {src.first, 3});
            }
        }
    }
    else if (auto rook = dynamic_cast<Rook*>(piece)) {
        if (piece->isWhite()) {
            if (src.first == 7 && src.second == 0) whiteLeftRookMoved = true;
            if (src.first == 7 && src.second == 7) whiteRightRookMoved = true;
        } else {
            if (src.first == 0 && src.second == 0) blackLeftRookMoved = true;
            if (src.first == 0 && src.second == 7) blackRightRookMoved = true;
        }
    }

    m_board[dst.first][dst.second] = std::move(m_board[src.first][src.second]);
    m_board[src.first][src.second] = nullptr;
}

std::pair<int, int> Board::findKing(bool white) const {
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            if (auto p = getPieceAt(r, c); p && dynamic_cast<const King*>(p) && p->isWhite() == white)
                return {r, c};
    return {-1, -1};
}

bool Board::isCheck(bool forWhite) const {
    auto kingPos = findKing(forWhite);
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            auto* attacker = getPieceAt(r, c);
            if (attacker && attacker->isWhite() != forWhite) {
                if (attacker->isLegalMove({r, c}, kingPos, *this)) return true;
            }
        }
    }
    return false;
}

bool Board::canCastle(bool white, bool kingSide) const {
    if (white) {
        if (whiteKingMoved) return false;
        if (kingSide && whiteRightRookMoved) return false;
        if (!kingSide && whiteLeftRookMoved) return false;

        if (kingSide) {
            if (getPieceAt(7, 5) || getPieceAt(7, 6)) return false;
            if (!isPathClear({7, 4}, {7, 7})) return false;
            if (isCheck(true)) return false;
            Board temp = *this;
            temp.movePiece({7, 4}, {7, 5});
            if (temp.isCheck(true)) return false;
            temp.movePiece({7, 5}, {7, 6});
            if (temp.isCheck(true)) return false;
            return true;
        } else {
            if (getPieceAt(7, 1) || getPieceAt(7, 2) || getPieceAt(7, 3)) return false;
            if (!isPathClear({7, 4}, {7, 0})) return false;
            if (isCheck(true)) return false;
            Board temp = *this;
            temp.movePiece({7, 4}, {7, 3});
            if (temp.isCheck(true)) return false;
            temp.movePiece({7, 3}, {7, 2});
            if (temp.isCheck(true)) return false;
            return true;
        }
    } else {
        if (blackKingMoved) return false;
        if (kingSide && blackRightRookMoved) return false;
        if (!kingSide && blackLeftRookMoved) return false;

        if (kingSide) {
            if (getPieceAt(0, 5) || getPieceAt(0, 6)) return false;
            if (!isPathClear({0, 4}, {0, 7})) return false;
            if (isCheck(false)) return false;
            Board temp = *this;
            temp.movePiece({0, 4}, {0, 5});
            if (temp.isCheck(false)) return false;
            temp.movePiece({0, 5}, {0, 6});
            if (temp.isCheck(false)) return false;
            return true;
        } else {
            if (getPieceAt(0, 1) || getPieceAt(0, 2) || getPieceAt(0, 3)) return false;
            if (!isPathClear({0, 4}, {0, 0})) return false;
            if (isCheck(false)) return false;
            Board temp = *this;
            temp.movePiece({0, 4}, {0, 3});
            if (temp.isCheck(false)) return false;
            temp.movePiece({0, 3}, {0, 2});
            if (temp.isCheck(false)) return false;
            return true;
        }
    }
}
