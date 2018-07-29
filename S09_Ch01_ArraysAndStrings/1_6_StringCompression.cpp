//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.15
// Modified: 2018.07.29
//

/*
1.6 - StringCompression() - P.91
Implement a method to perform basic string compression using the counts of
repeated characters. For example, the string 'aabcccccaaa' would become
'a2b1c5a3'. If the "compressed" string would not become smaller than the
original string, your method should return the original string. You can assume
the string has only uppercase and lowercase letters (a-z)

Problem Setup and Assumptions:
  A string may be represented as an array or linked list of chars.
    Many languages also support the string as a class
  Capital letters are not equivalent to lowercase letters ('A' != 'a')

Naive Approach:

Optimizations:
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
