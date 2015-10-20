
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



// ------------
// cutribbon_eval
// ------------

class Node
{
public:
  Node (int idx_) :
    idx (idx_)
  {}

  int idx = 0;
};

using Stack = std::vector<Node>;

void dump_stack (const Stack& stack, const std::vector<int>& cut_lengths, int total_length)
{
  for (const Node& node : stack) {
    std::cout << node.idx  << " " << cut_lengths[node.idx] << std::endl;
  }
  std::cout << total_length << std::endl;
  std::cout << std::endl;
}

int cutribbon_eval (int target_length, std::vector<int> cut_lengths)
{
  // Sort the cut lengths from smallest to largest.  Remove any duplicate values.
  std::sort (cut_lengths.begin(), cut_lengths.end());
  const int max_idx = cut_lengths.size() - 1;

  // The depth first search stack seeded with the shortest cut idx
  Stack stack {{0}};
  
  // The total length of cuts we have accumulated so far
  int total_length = cut_lengths[0];

  while (true)
  {
    dump_stack (stack, cut_lengths, total_length);

    Node& top_node = stack.back();
    
    // If we are equal to the target length then we have found the solution
    if (total_length == target_length) {
      return stack.size();
    }

    else {
      // The index of the next node to push
      int next_idx = -1;
      
      // If we are shorter than the target length then explore one node further
      if (total_length < target_length) {
        next_idx = top_node.idx;
      }

      // Since we have exceeded the target length backtrack and restart exploration
      else {
        do {
          next_idx = top_node.idx;
          total_length -= cut_lengths[next_idx];
          stack.pop_back();
          top_node = stack.back();
        } 
        while (next_idx == max_idx);
        next_idx += 1;
      }

      // Append the next idx
      total_length += cut_lengths[next_idx];
      stack.emplace_back (next_idx);
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
