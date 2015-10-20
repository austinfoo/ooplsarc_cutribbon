
#ifndef CutRibbon_h
#define CutRibbon_h

// --------
// includes
// --------

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// ------------
// cutribbon_eval
// ------------

int cutribbon_eval (int target_length, std::vector<int> cut_lengths);

// -------------
// cutribbon_print
// -------------

void cutribbon_print (std::ostream& w, int num_pieces);

// -------------
// cutribbon_solve
// -------------

void cutribbon_solve (std::istream& r, std::ostream& w);

#endif

// ----------------------------
// projects/twobuttons/Twobuttons.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <list>
#include <limits>



// ------------
// cutribbon_eval
// ------------

class Node
{
public:
  Node (int idx_, int length_, int depth_) :
    idx (idx_),
    length (length_),
    depth (depth_)
  {}

  int idx = 0;
  int length = 0;
  int depth = 0;
};

class Visit
{
public:
  int depth = 0;
};

using Queue = std::list<Node>;

int cutribbon_eval (int target_length, std::vector<int> cut_lengths)
{
  // Sort the cut lengths from smallest to largest.
  std::sort (cut_lengths.begin(), cut_lengths.end());

  // The work queue
  Queue queue {{0, cut_lengths[0], 1}, {1, cut_lengths[1], 1}, {2, cut_lengths[2], 1}};

  // The visited vector
  std::vector<Visit> visited (4001);

  // The current best solution
  int solution_depth = 0;

  while (!queue.empty())
  {
    Node& node = queue.front();

    if (node.length == target_length) {
      solution_depth = node.depth;
    }

    else {
      for (int next_idx = node.idx; next_idx < cut_lengths.size(); ++next_idx) {
	int next_length = node.length + cut_lengths[next_idx];
	int next_depth = node.depth + 1;
	if (next_length <= target_length && visited[next_length].depth < next_depth)
	{
	  queue.emplace_back (next_idx, next_length, next_depth);
	  visited[next_length].depth = next_depth;
	}
      }
    }

    queue.pop_front();
  }

  return solution_depth;
}

// -------------
// cutribbon_print
// -------------

void cutribbon_print (std::ostream& w, int num_pieces) {
  w << num_pieces << std::endl;
}

// -------------
// cutribbon_solve
// -------------

void cutribbon_solve (std::istream& r, std::ostream& w) 
{
  std::string s;

  // Get the target length and cut lengths
  int target_length = 0;
  std::vector<int> cut_lengths (3);
  if (std::getline(r, s)) {
    std::istringstream sin(s);
    sin >> target_length;
    sin >> cut_lengths[0] >> cut_lengths[1] >> cut_lengths[2];
  }

  // Determine the number of pieces
  int num_pieces = cutribbon_eval(target_length, cut_lengths);

  // Print the result
  cutribbon_print(w, num_pieces);
}

#include <iostream>



// ----
// main
// ----

int main () {
    using namespace std;
    cutribbon_solve(cin, cout);
    return 0;
}
