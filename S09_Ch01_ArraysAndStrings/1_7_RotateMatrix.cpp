//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.15
// Modified: 2018.08.22
//

NOTE: PLACEHOLDER DOCUMENT! TODO: Complete problem

/*
1.7 - RotateMatrix() - P.91
Given an image represented by an NxN matrix, where each pixel in the image is 4
bytes, write a method to rotate the image by 90 degrees.

Can you do this in place?

//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

  A left rotation may be performed by calling a right rotation 3 times.
    Only the right (clockwise) rotation shall be handled
  The nature of the pixel is immaterial; we may handle the pixel as a 32-bit int
  Since the problem specifies an N x N matrix, we address a square aspect ratio

  To move a pixel

     0   1    X         0   1    X
   +---+---+          +---+---+     ([0][0] becomes [1][0])
0  | 1 | 2 |       0  | 4 | 1 |     ([1][0] becomes [1][1])
   +---+---+          +---+---+
1  | 4 | 3 |       1  | 3 | 2 |
   +---+---+          +---+---+
Y                  Y



//-----------------------------------------------------------------------------|
// NAIVE APPROACH
//-----------------------------------------------------------------------------|

  Iterate across every pixel within a quadrant and for (4) times
    Identify the 4 sister-pixels

     0   1   2    X    [X][Y]               is sister to
   +---+---+---+       [XMax - X][Y]        which is sister to
0  | 1 | 2 | 3 |       [XMax - X][YMax - Y] which is sister to
   +---+---+---+       [X][YMax-Y]
1  | 8 | 9 | 4 |
   +---+---+---+
2  | 7 | 6 | 5 |
   +---+---+---+
Y

    There are two special cases;
      In an odd-numbered array, the center column and row exhibit:
        [X][Y]      is sister to
        [YMax-Y][X] which is sister to
        [X][YMax-Y] which is sister to
        [Y][X]

      And the center
        [1/2X][1/2Y] has no sibling

  The time complexity may be represented by the number of comparisons required based on N, the length of the strings.
  As a string of length N will in the worst case require a quantity of comparisons matching the number of permutations available, the pattern will be as follows:
    (1) char  == 1 combination  (a)
    (2) chars == 2 combinations (ab, ba)
    (3) chars == 6 combinations (abc, acb, bac, bca, cab, cba)
  More broadly, we may say that the number of combinations is factorial in nature:
  O(N!)
  1 * 2 * 3 ... * n
  However, this only represents the number of string comparisons to perform. As such comparisons are char-by-char comparisons down the string, we may expect a time complexity closer to:
  O(N! * N)
  Note that this ignores issues of repeated characters or discussions of alphabet size.



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

  1) The orientation of the image may be stored as a separate value from 0 to 3.
     This may then be used to interpret the N, E, S, W orientation of the image
     without modifying the image itself.



Pseudo Logic:
  Compare string lengths for equality
  Declare alphabet table charCounts
  For each character in string1
    Add 1 to the appropriate table in charCounts
  For each character in string2
    Subtract 1 from the appropriate table in charCounts
    If the result is <0
      Return false

Code (C++):
*/

#include <string>

// (+) --------------------------------|
// #checkPermutations(string)
// ------------------------------------|
// Desc:    Determines whether two strings are permutations of one another or not
// Params:  string arg1 - The first string to compare
//          string arg2 - The second string to compare
// PreCons: None
// PosCons: None
// RetVal:  bool true - The received strings are permutations of each other
//          bool false - The received strings are not permutations of each other
bool checkPermutations(string string1, string string2) {
   // Compare string lengths for equality
   if ( string1.length( ) != string2.length( ) {
      return( false );
   }

   // Declare and initialize alphabet table charCounts
   int charCounts[256];
   for ( int i = 0 ; i < 256 ; i++ ) {
      charCounts[i] = 0;
   }

   // For each character in string1
   char currChar;
   for ( int i = 0 ; i < string1.length( ) ; i++ ) {
      // Add 1 to the appropriate table in charCounts
      currChar = string1.at( i );
      charCounts[ (int)currChar ] += 1;
   } // Closing for - Frequency table loaded

   // For each character in string2
   for ( int i = 0 ; i < string2.length( ) ; i++ ) {
      // Subtract 1 from the appropriate table in charCounts
      currChar = string2.at( i );
      charCounts[ (int)currChar ] -= 1;

      // If the result is <0
      if ( charCounts[ (int)currChar ] < 0 ) {
         // Return false
         return( false );
      }
   } // Closing for - All comparisons performed

   // No discrepancies found in the two strings, so...
   return( true );
}
