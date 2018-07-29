//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.23
// Modified: 2018.07.29
//

// TODO: Investigate use of a boolean isEven/isOdd toggle. Investigate use of
// oddCount to avoid iterating over the count the alphabet

/*
1.4 - Palindrome Permutation() - P.91
Given a string, write a function to check if it is a permutation of a palindrome. A palindrome is a word or phrase that is the same forwards and backwards. A permutation is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.

Example:
Input: Tact Coa
Output: True (permutations: "taco cat", "atco cta", etc.)

Problem Setup and Assumptions:
  A string may be represented as an array or linked list of chars.
    Many languages also support the string as a class
  A permutation is a rearrangement of characters in a string.
  A palindrome reads the same forward as backward
   - Ignoring case
   - Ignoring whitespace
  Assume valid chars from a-z and A-Z

Terribad approach:
  Generate all permutations of the string
  Check each permutation for palindromic qualities by iterating from the front and back of the string
  Return false if all permutations are exhausted without finding a palindrome
  Return true if a palindrome is encountered

Naive Approach:


Better Approach:
  Observe that the palindromic quality is really a description of character counts. Palindromes:
    - Have an even number of every character
    - But +may+ have an odd number of a single character
  Hence, if all the characters are even in count (except possibly one), then the string can be configured as a palindrome.

Optimizations:
  1) Placing the counts in a hash table will be a faster time complexity than rearranging the native string
  2) Counting the number of odd characters as the algorithm iterates over the string may save time on short strings OR large alphabets
    - On longer strings (and shorter alphabets), it will likely be more worthwhile to iterate over the count array after all the counts are tallied.
  The time complexity shall be:
    - O(N) to iterate over the string (where N is the length of the input) plus...
    - O(A) to iterate over the character counts (where A is the length of the valid alphabet)
    - Formally, O(N + A), though in most cases the alphabet may reasonably be expected not to be the dominant factor, particularly where asmyptotic behavior becomes a consideration.

Pseudo Logic:
  Create a hash table of counts, initialize to zero (0)

    A   B   C   ...   X   Y   Z
  -------------------------------
  | 0 | 0 | 0 | ... | 0 | 0 | 0 |
  -------------------------------

  Iterate over the argument string, incrementing the appropriate hash for each character

    A   B   C   ...   X   Y   Z
  -------------------------------
  | # | # | # | ... | # | # | # |
  -------------------------------

  With the count array populated, iterate over it. If more than one odd number is found, the string was not a palindrome permutation.

Code (C++):
*/

#include <string>

// (+) --------------------------------|
// #palindromePermutation(string)
// ------------------------------------|
// Desc:    Determines whether a string is a permutation of a palindrome
// Params:  string arg1 - The string to analyze
// PreCons: None
// PosCons: None
// RetVal:  bool true - The received string is a palindrome permutation
//          bool false - The received string is not a palindrome permutation
bool palindromePermutation(string theString) {
   // Generate a count table and initialize it to 0
   int charCounts[256];
   for (int i = 0 ; i < 256 ; i++) {
      charCounts[i] = 0;
   }

   // Iterate over the string, incrementing the charCounts table
   char currCharIndex;
   for ( int i = 0 ; i < theString.length() ; i++ ) {
      currCharIndex = (int)theString.at(i);
      charCounts[currCharIndex]++;
   }

   // Iterate over the charCounts table and inventory how many odd character counts were found
   int oddsEncountered = 0;
   for ( int i = 0 ; i < 256 ; i++ ) {
      if (charCounts[i] % 2 != 0) {
         oddsEncountered++;
         // Check if this is or is not the first odd value encountered
         if (oddsEncountered > 1) {
            return (false);
         }
      }
   } // Closing for - all counts checked

   // Not more than one odd count was encountered, therefore...
   return (true);
} // Closing palindromePermutation(string)
