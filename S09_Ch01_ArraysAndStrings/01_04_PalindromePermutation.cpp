//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.23
// Modified: 2018.08.21
//

/*
1.4 - Palindrome Permutation() - P.91
Given a string, write a function to check if it is a permutation of a palindrome. A palindrome is a word or phrase that is the same forwards and backwards. A permutation is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.

Example:
Input: Tact Coa
Output: True (permutations: "taco cat", "atco cta", etc.)



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

A string may be represented as an array or linked list of chars.
  Many languages also support the string as a class
A permutation is a rearrangement of characters in a string.
A palindrome reads the same forward as backward
 - Ignoring case
 - Ignoring whitespace
Assume valid chars from a-z and A-Z



//-----------------------------------------------------------------------------|
// NAIVE, BRUTE FORCE, TERRIBAD APPROACH
//-----------------------------------------------------------------------------|

Terribad approach:
  Generate all permutations of the string
  Check each permutation for palindromic qualities by iterating from both the
    front and back of the string.
  Return false if all permutations are exhausted without finding a palindrome.
  Return true if a palindrome is encountered.

Naive Approach:
  Observing that the provided string is effectively a kit of parts, we may
  attempt to build a palindrome by constructing the two halves separately,
  drawing letters from the provided string one-by-one.
  This process may be eased by first sorting the string, then drawing pairs
  of characters until until a deadlock is reached or a palindrome constructed.



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

Observe that the palindromic quality is really a description of character counts.
Palindromes:
  - Have an even number of every character
  - But +may+ have an odd number of a single character
Hence, if all the characters are even in count (except possibly one),
then the string can be configured as a palindrome.
  
1) As we don't care about the specific number of pairs, the table may merely
  track whether the number of characters encountered thus far is even or odd.
2) A single counter can tally how many odd characters have been encountered
3) At the conclusion of the scan, if the tally is greater than 1, no palindrome
  can be derived from the original string

//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

The time complexity shall be on the order of:

O( n ) to iterate over the string

Where 'n' is the length of the input) plus:



//-----------------------------------------------------------------------------|
// PSEUDOLOGIC
//-----------------------------------------------------------------------------|

Create an odd counter
Create a hash table of even/odd status:

  a   b   c  ...  x   y   z
+---+---+---+---+---+---+---+
| 0 | 0 | 0 |...| 0 | 0 | 0 |
+---+---+---+---+---+---+---+

Iterate over the argument string, toggling the appropriate cell for each character

  a   b   c  ...  x   y   z
+---+---+---+---+---+---+---+
| 0 | 1 | 0 |...| 1 | 0 | 1 |
+---+---+---+---+---+---+---+

Whenever a cell toggles from 0 to 1, increment the odd counter
Whenever a cell toggles from 1 to 0, decrement the odd counter

At the end of the process, if the odd counter is greater than 1, return false.
Otherwise return true.



//-----------------------------------------------------------------------------|
// CODE (C++)
//-----------------------------------------------------------------------------|
*/
// Compile with:
// $ g++ --std=c++11 01_04_PalindromePermutation.cpp -o PalindromePermutation
// Run with:
// $ ./PalindromePermutation

#include <string>
#include <iostream>

// (+) --------------------------------|
// #palindromePermutation(string)
// ------------------------------------|
// Desc:    Determines whether a string is a permutation of a palindrome
// Params:  string arg1 - The string to analyze
// PreCons: Additional whitespaces are omitted from the input string if they
//          do NOT count towards permutative qualities
//          Whitespaces are included in the input string if they DO count
//          towards permutative quality.
//          Capitalization DOES count
// PosCons: None
// RetVal:  bool true - The received string is a palindrome permutation
//          bool false - The received string is not a palindrome permutation
bool palindromePermutation( std::string theString ) {
   // Generate an even/odd table and initialize it to true (counts of 0 are even)
   bool isEven[ 256 ];
   for ( int i = 0 ; i < 256 ; i++ ) {
      isEven[ i ] = true;
   }
   int oddCounter = 0;
   // Iterate over the string, toggling the isEven table
   char currCharIndex;
   for ( int i = 0 ; i < theString.length( ) ; i++ ) {
      currCharIndex = ( int )theString.at( i );
      isEven[ currCharIndex ] = !isEven[ currCharIndex ];
      // If we just switched to an even count...
      if( isEven[ currCharIndex ] == true ) {
         oddCounter--;
      }
      else {
         oddCounter++;
      }
   } // Closing for - String has been parsed
   // If the oddCounter is 0 or 1, this is permutable
   if( oddCounter <= 1 ) {
      return( true );
   }
   else {
      // Otherwise it isn't permutable.
      return ( false );
   }
} // Closing palindromePermutation(string)



//-----------------------------------------------------------------------------|
// DRIVER
//-----------------------------------------------------------------------------|

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
   std::cout << "Test of palindromePermutation( )" << std::endl;
   bool test1 = palindromePermutation( "thisisapermutationthisisapermutationz" );
   bool test2 = palindromePermutation( "thisisnotapermutation" );
   bool test3 = palindromePermutation( "TacocaT" ); // Trailing whitespace
   std::cout << "Test 1 : ( 1 expected )" << std::endl;
   std::cout << "           " << test1 << std::endl << std::endl;
   std::cout << "Test 2 : ( 0 expected )" << std::endl;
   std::cout << "           " << test2 << std::endl << std::endl;
   std::cout << "Test 3 : ( 1 expected )" << std::endl;
   std::cout << "           " << test3 << std::endl << std::endl;
   return( 0 );
} // Closing main( int, char* )

// End of file 01_04_PalindromePermutation.cpp
