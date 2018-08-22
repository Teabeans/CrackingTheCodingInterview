//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.15
// Modified: 2018.08.21
//

/*
1.2 - CheckPermutation() - P.90
Given two strings, write a method to decide if one is a permutation of the other.



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

  A string may be represented as an array or linked list of chars.
    Many languages also support the string as a class
  A permutation is a rearrangement of characters in a string.



//-----------------------------------------------------------------------------|
// NAIVE, BRUTE FORCE, TERRIBAD APPROACH
//-----------------------------------------------------------------------------|

  Compare all permutations of one string against the other for equivalence.
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

  1) If the string size is an O(1) accessible field, it may be checked first. Any strings with differing lengths may bypass comparisons; they cannot be permutations of each other.
  2) Sorting the two strings (an O(NlogN) operation) may allow us to traverse the sorted strings char-by-char looking for discrepancies.
    - To be permutations, the quantity of all characters must be the same
    - So if a mismatch is found in the sorted sequence, the quantities differ and the strings cannot be permutations of each other
  3) However, since we only require a count of the characters involved, we can avoid sorting the strings and merely take a tally
    - 2 tables will be required representing the frequency of characters within each string
    - After traversing the string to populate these frequency tables, we can compare the tables for discrepancies
    - The time complexity may be represented as:
      - O(N) to traverse the first string
      - O(N) to traverse the second string
      - O(A) to traverse the frequency table (where A represent the length of the alphabet)
    - This has the additional advantage that the strings need not be modified or copied
  4) A single frequency table may be used by counting up for the first string, then down for the second. This yields a couple advantages:
    - A slight improvement to memory requirements of the frequency table, as only one alphabet need be stored.
    - The algorithm may shortcut its comparisons if the decrement value ever drops below 0 (representing more of that character in the second string than the first)
    - The time complexity may be represented as:
      - O(N) to traverse the first string
      - O(N) to traverse the second string
      - Which simplifies to an O(N) time complexity for this solution



//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|



//-----------------------------------------------------------------------------|
// PSEUDOLOGIC
//-----------------------------------------------------------------------------|

  Compare string lengths for equality
  Declare alphabet table charCounts
  For each character in string1
    Add 1 to the appropriate table in charCounts
  For each character in string2
    Subtract 1 from the appropriate table in charCounts
    If the result is <0
      Return false



//-----------------------------------------------------------------------------|
// CODE (C++)
//-----------------------------------------------------------------------------|
*/

#include <string>
#include <iostream>

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

// (+) --------------------------------|
// #main( int, char* )
// ------------------------------------|
// Desc:    Code driver
// Params:  int arg1 - The number of command line arguments passed in
//          char* arg2 - The content of the command line arguments
// PreCons: None
// PosCons: None
// RetVal:  int - The exit code (0 for normal, -1 for error)
int main( int argc, char* argv[ ] ) {
   std::cout << "Test of checkPermutations( )" << std::endl;
   bool test1 = checkPermutations( "abcdefghijklmnop", "ponmlkjihgfedcba" );
   bool test2 = checkPermutations( "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyy" );
   bool test3 = checkPermutations( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 " );
   std::cout << "Test 1 (expected: 1) : " << test1 << std::endl;
   std::cout << "Test 2 (expected: 0) : " << test2 << std::endl;
   std::cout << "Test 3 (expected: 1) : " << test3 << std::endl;
   return( 0 );
} // Closing main( int, char* )

// End of file 01_02_checkPermutations.cpp
