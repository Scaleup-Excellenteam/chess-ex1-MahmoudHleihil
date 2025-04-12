#include "GameManager.h"
#include <cctype>

GameManager::GameManager(const std::string& board) : m_board(board), m_turnWhite(true) {}

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
