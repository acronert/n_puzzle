# n_puzzle

A n-puzzle (based on the 15 puzzle game) solver using the A* algorithm in C++.
This project is part of the 42 curriculum.

---

## Overview
This project is an n-puzzle solver using the A* algorithm in C++, part of the 42 curriculum. It allows you to experiment with different algorithms and heuristics while demonstrating performance optimizations in C++.

Key features include:

- Supports multiple algorithms: Standard A*, Greedy, and Uniform Cost Search
- Multiple heuristics: Manhattan Distance, Misplaced Tiles, Gaschnig, and Linear Conflict
- Terminal display with colored tiles based on distance to goal
- Automatic solvability check
- Efficient heap-based priority queue for pathfinding
- Memory pool usage to reduce allocation overhead

---

## 📷 Demo

![npuzzle_demo](npuzzle_demo.gif) 
*Testing standard and greedy with Manhattan Distance heuristic on a 4 by 4 puzzle*

---

## 📦 Requirements

- Linux
- C++ 17
- `make`

---

## ⚙️ Building

```bash
make```
