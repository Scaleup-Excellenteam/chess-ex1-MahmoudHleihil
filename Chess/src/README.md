# C++ Chess Engine – Mahmoud Hleihil

**Final Project – Part 4**
Tel-Hai College | Advanced C++ | 2025

---

## Overview

This project is a console-based chess engine implemented in modern C++.
It supports:

* All standard chess rules (including castling, check, checkmate, stalemate)
* Interactive mode (Player vs Player)
* AI mode (Player vs AI with multithreaded Minimax algorithm)

---

## Features

| Feature               | Status | Notes                                    |
| --------------------- | ------ | ---------------------------------------- |
| Legal movement        | ✅      | Full validation for all pieces           |
| Castling              | ✅      | King-side and Queen-side                 |
| Check / Checkmate     | ✅      | Implemented with king safety validation  |
| Stalemate / Draw      | ✅      | Recognized when no legal moves exist     |
| AI opponent           | ✅      | Minimax + alpha-beta pruning             |
| Multithreading for AI | ✅      | Threads evaluate legal moves in parallel |

---

## Build Instructions

```bash
# Clone the repository and enter the directory
git clone https://github.com/Scaleup-Excellenteam/chess-ex1-MahmoudHleihil
cd chess-ex1-MahmoudHleihil

# Create build folder and compile
mkdir build
cd build
cmake ..
make

# Run the game
./Chess
```
