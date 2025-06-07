#include "GameManager.h"
#include <cctype>

GameManager::GameManager(const std::string& board) : m_board(board), m_turnWhite(true) {}

bool GameManager::isWhiteTurn() const {
    return m_turnWhite;
}

int GameManager::evaluateMove(const std::string& input) {
    int srcCol = input[0] - 'a';
    int srcRow = input[1] - '1';
    int dstCol = input[2] - 'a';
    int dstRow = input[3] - '1';
    auto* srcPiece = m_board.getPieceAt(srcRow, srcCol);
    auto* dstPiece = m_board.getPieceAt(dstRow, dstCol);

    if (!srcPiece) return 11;
    if (srcPiece->isWhite() != m_turnWhite) return 12;
    if (dstPiece && dstPiece->isWhite() == m_turnWhite) return 13;
    if (!srcPiece->isLegalMove({srcRow, srcCol}, {dstRow, dstCol}, m_board)) return 21;

    Board tempBoard = m_board;
    tempBoard.movePiece({srcRow, srcCol}, {dstRow, dstCol});
    if (tempBoard.isCheck(m_turnWhite)) return 31;

    m_board.movePiece({srcRow, srcCol}, {dstRow, dstCol});
    m_turnWhite = !m_turnWhite;
    return (m_board.isCheck(m_turnWhite)) ? 41 : 42;
}

std::vector<std::string> GameManager::getAllLegalMoves() const {
    std::vector<std::string> moves;
    const std::string letters = "abcdefgh";
    const std::string digits = "12345678";
    for (int srcRow = 0; srcRow < 8; ++srcRow) {
        for (int srcCol = 0; srcCol < 8; ++srcCol) {
            const auto* piece = m_board.getPieceAt(srcRow, srcCol);
            if (!piece || piece->isWhite() != m_turnWhite) continue;
            for (int dstRow = 0; dstRow < 8; ++dstRow) {
                for (int dstCol = 0; dstCol < 8; ++dstCol) {
                    if (srcRow == dstRow && srcCol == dstCol) continue;
                    if (!piece->isLegalMove({srcRow, srcCol}, {dstRow, dstCol}, m_board)) continue;

                    Board temp = m_board;
                    temp.movePiece({srcRow, srcCol}, {dstRow, dstCol});
                    if (!temp.isCheck(m_turnWhite)) {
                        std::string move;
                        move += ('a' + srcCol);
                        move += ('1' + srcRow);
                        move += ('a' + dstCol);
                        move += ('1' + dstRow);
                        moves.push_back(move);
                    }
                }
            }
        }
    }
    return moves;
}

const Piece* GameManager::getPiece(int row, int col) const {
    return m_board.getPieceAt(row, col);
}

bool GameManager::isCheck(bool white) const {
    return m_board.isCheck(white);
}
