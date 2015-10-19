
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
