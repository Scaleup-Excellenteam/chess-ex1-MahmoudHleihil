#include "GameManager.h"
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <chrono>

struct Move {
    std::string from;
    std::string to;
    int score;

    bool operator<(const Move& other) const {
        return score < other.score; // for max-heap
    }
};

std::priority_queue<Move> moveQueue;
std::mutex queueMutex;
std::atomic<bool> stopFlag = false;
const int SCORE_THRESHOLD = 9000; // Bonus threshold

int evaluateMoveSim(const GameManager& gm, const std::string& input) {
    GameManager temp = gm;
    return temp.evaluateMove(input);
}

void worker(const GameManager& gm, const std::vector<std::string>& moves) {
    for (const auto& move : moves) {
        if (stopFlag) return;
        int score = rand() % 10000; // simulate scoring
        if (score >= SCORE_THRESHOLD) stopFlag = true;

        std::lock_guard<std::mutex> lock(queueMutex);
        moveQueue.push({move.substr(0, 2), move.substr(2, 2), score});
    }
}

std::vector<std::string> generateAllLegalMoves(GameManager gm, bool isWhite) {
    std::vector<std::string> legalMoves;
    const std::string letters = "abcdefgh";
    const std::string digits = "12345678";
    for (char sc : letters) {
        for (char sr : digits) {
            for (char dc : letters) {
                for (char dr : digits) {
                    std::string move = {sc, sr, dc, dr};
                    GameManager temp = gm;
                    if (temp.evaluateMove(move) >= 41)
                        legalMoves.push_back(move);
                }
            }
        }
    }
    return legalMoves;
}

Move getBestMoveMultithreaded(GameManager gm, bool isWhite, int threadCount) {
    stopFlag = false;
    moveQueue = std::priority_queue<Move>();

    auto moves = generateAllLegalMoves(gm, isWhite);
    int batchSize = (moves.size() + threadCount - 1) / threadCount;
    std::vector<std::thread> threads;

    for (int i = 0; i < threadCount; ++i) {
        int start = i * batchSize;
        int end = std::min((int)moves.size(), (i + 1) * batchSize);
        if (start >= end) break;
        threads.emplace_back(worker, gm, std::vector<std::string>(moves.begin() + start, moves.begin() + end));
    }

    for (auto& t : threads) t.join();
    return moveQueue.top();
}

void runBenchmark() {
    std::string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    GameManager gm(board);
    std::vector<int> threadCounts = {1, 2, 4, 8};
    for (int count : threadCounts) {
        auto start = std::chrono::high_resolution_clock::now();
        getBestMoveMultithreaded(gm, true, count);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Threads: " << count << ", Time: " << duration.count() << "ms\n";
    }
}
