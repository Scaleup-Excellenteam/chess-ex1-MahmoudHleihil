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
        if (c == 'r') m_board[i % 8][i / 8] = std::make_unique<Rook>(isWhite);
        else if (c == 'k') m_board[i % 8][i / 8] = std::make_unique<King>(isWhite);
        else if (c == 'b') m_board[i % 8][i / 8] = std::make_unique<Bishop>(isWhite);
        else if (c == 'n') m_board[i % 8][i / 8] = std::make_unique<Knight>(isWhite);
        else if (c == 'q') m_board[i % 8][i / 8] = std::make_unique<Queen>(isWhite);
        else if (c == 'p') m_board[i % 8][i / 8] = std::make_unique<Pawn>(isWhite);
    }
}

Board::Board(const Board& other) : m_board(8) {
    for (int i = 0; i < 8; ++i) {
        m_board[i].resize(8);
        for (int j = 0; j < 8; ++j) {
            if (other.m_board[i][j])
                m_board[i][j] = other.m_board[i][j]->clone();
        }
    }
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
