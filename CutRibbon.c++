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
#include <stack>
#include <algorithm>

#include "CutRibbon.h"

// ------------
// cutribbon_eval
// ------------

class Node
{
public:
  Node (int idx_, int length_, int total_length_) :
    idx (idx_),
    length (length_),
    total_length (total_length_)
  {}

  void write (int idx_, int length_, int total_length_) {
    idx = idx_;
    length = length_;
    total_length = total_length_;
  }
  
  int idx;
  int length = 0;
  int total_length = 0;
};

int cutribbon_eval (int target_length, std::vector<int> cut_lengths)
{
  // The stack to contain the current state of our depth first search
  std::stack<Node> stack;

  // Sort the cut length from smallest to largest.  Remove any dupliate values.
  std::sort (cut_lengths.begin(), cut_lengths.end());
  std::unique (cut_lengths.begin(), cut_lengths.end());
  int max_idx = cut_lengths.size() - 1;

  // Seed the stack with the smallest cut
  stack.emplace(0, cut_lengths[0], cut_lengths[0]);

  while (true)
  {
    Node& top_node = stack.top();
    
    // If we are equal to the target length then we have found the solution
    if (top_node.total_length == target_length) {
      return stack.size();
    }

    // If we are shorter than the target length then xplore one node further
    else if (top_node.total_length < target_length) {
      stack.emplace (top_node.length, top_node.idx, top_node.total_length + top_node.length);
    }

    // Since we have exceeded the target length backtrack and restart exploration
    else {

      // Back up to the last node with a non-max idx
      int last_idx_explored_from_top_node = 0;
      do {
	last_idx_explored_from_top_node = top_node.idx;
	stack.pop();
	top_node = stack.top();
      } 
      while (top_node.idx == max_idx);

      // If the last node has explored all children, then morph the last node to the next cut size
      if (last_idx_explored_from_top_node == max_idx) {
	int new_idx = top_node.idx + 1;
	int new_length = cut_lengths[new_idx];
	int new_total_length = top_node.total_length - top_node.length + new_length;
	top_node.write (new_length, new_idx, new_total_length);
      }

      // The last node has not explored all children.  Append the next child.
      else {
	int next_idx = last_idx_explored_from_top_node + 1;
	int next_length = cut_lengths[next_idx];
	int next_total_length = top_node.total_length + next_length;
	stack.emplace (next_length, next_idx, next_total_length);
      }
    }
  }
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

  // Get the length
  int length = 0;
  if (std::getline(r, s)) {
    std::istringstream sin(s);
    sin >> length;
  }

  // Get the cuts length
  std::vector<int> cut_lengths (3);
  if (std::getline(r, s)) {
    std::istringstream sin(s);
    sin >> cut_lengths[0] >> cut_lengths[1] >> cut_lengths[2];
  }

  // Determine the number of pieces
  int num_pieces = cutribbon_eval(length, cut_lengths);

  // Print the result
  cutribbon_print(w, num_pieces);
}
