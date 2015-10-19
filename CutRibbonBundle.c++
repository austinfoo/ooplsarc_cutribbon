
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
#include <stack>
#include <algorithm>
#include <list>



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

  int idx = 0;
  int length = 0;
  int total_length = 0;
};

void dump_stack (const std::list<Node>& list)
{
  for (auto& node : list) {
    std::cout << node.idx  << " " << node.length << " " << node.total_length << std::endl;
  }
  std::cout << std::endl;
}

int cutribbon_eval (int target_length, std::vector<int> cut_lengths)
{
  // The stack to contain the current state of our depth first search
  std::list<Node> stack;

  // Sort the cut length from smallest to largest.  Remove any dupliate values.
  std::sort (cut_lengths.begin(), cut_lengths.end());
  const int max_idx = cut_lengths.size() - 1;

  // Seed the stack with the smallest cut
  stack.emplace_back(0, cut_lengths[0], cut_lengths[0]);

  while (true)
  {
    //dump_stack (stack);

    Node& top_node = stack.back();
    
    // If we are equal to the target length then we have found the solution
    if (top_node.total_length == target_length) {
      return stack.size();
    }

    // If we are shorter than the target length then explore one node further
    else if (top_node.total_length < target_length) {
      stack.emplace_back (top_node.idx, top_node.length, top_node.total_length + top_node.length);
    }

    // Since we have exceeded the target length backtrack and restart exploration
    else {

      // Back up to the last node with a non-max idx
      int last_idx_explored_from_top_node = 0;
      do {
	last_idx_explored_from_top_node = top_node.idx;
	stack.pop_back();
	top_node = stack.back();
      } 
      while (last_idx_explored_from_top_node == max_idx);

      // The top node has not explored all children.  Append the next child.
      int next_idx = last_idx_explored_from_top_node + 1;
      int next_length = cut_lengths[next_idx];
      int next_total_length = top_node.total_length + next_length;
      stack.emplace_back (next_idx, next_length, next_total_length);
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
