#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H

#include "board.h"

class PuzzleHeuristic
{
 public:
  virtual ~PuzzleHeuristic() { }
  virtual int compute(const Board& b) = 0;
};

class PuzzleManhattanHeuristic : public PuzzleHeuristic
{
 public:
  // counts Manhattan distance of each tile
  // **EXCLUDING the blank tile** from its
  // correct location in the solved board.
  int compute(const Board& b);
};

class PuzzleOutOfPlaceHeuristic : public PuzzleHeuristic
{
 public:
  // Counts the number of tiles out of place
  // **EXCLUDING the blank tile**.
  int compute(const Board& b);
};

class PuzzleBFSHeuristic : public PuzzleHeuristic
{
 public:
  // Returns 0
  int compute(const Board& b);
};


#endif
