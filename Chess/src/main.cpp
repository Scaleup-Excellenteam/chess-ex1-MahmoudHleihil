// Chess 
#include "Chess.h"
#include "GameManager.h"
#include <iostream>
#include <string>

struct Move {
    std::string from;
    std::string to;
    int score;
};

Move getBestMoveMultithreaded(GameManager gm, bool isWhite, int threadCount);

int main() {
    std::string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
    Chess a(board);
    GameManager gm(board);

    int codeResponse = 0;
    std::string res = "start";
    bool autoMode = false;
    int threadCount = 4;

    std::cout << "Enable auto-play mode? (1 = yes, 0 = no): ";
    std::cin >> autoMode;

    if (autoMode) {
        std::cout << "Enter number of threads to use (e.g., 2, 4, 8): ";
        std::cin >> threadCount;
    }

    while (res != "exit") {
        if (!autoMode) {
            res = a.getInput();
            if (res == "exit") break;
            codeResponse = gm.evaluateMove(res);
        } else {
            Move best = getBestMoveMultithreaded(gm, gm.isWhiteTurn(), threadCount);
            res = best.from + best.to;
            std::cout << "Auto move: " << res << " (score = " << best.score << ")\n";
            codeResponse = gm.evaluateMove(res);
            a.setInput(res);
        }

        a.setCodeResponse(codeResponse);
        if (!autoMode)
            res = a.getInput();
    }

    std::cout << "\nExiting.\n";
    return 0;
}
