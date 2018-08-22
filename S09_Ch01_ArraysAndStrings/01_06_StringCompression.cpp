//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.15
// Modified: 2018.08.22
//

/*
1.6 - StringCompression() - P.91
Implement a method to perform basic string compression using the counts of
repeated characters. For example, the string 'aabcccccaaa' would become
'a2b1c5a3'. If the "compressed" string would not become smaller than the
original string, your method should return the original string. You can assume
the string has only uppercase and lowercase letters (a-z)



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

A string may be represented as an array or linked list of chars.
  Many languages also support the string as a class
Capital letters are not equivalent to lowercase letters ('A' != 'a')
The number of characters saved by compressing a series may be expressed as:
  From 1 to 9:     savings = Number of sequential chars - 2
  From 10 to 99:   savings = Number of sequential chars - 3
  From 100 to 999: savings = Number of sequential chars - 4
  Most broadly, savings are reduced by 1 for every power of 10 increase in the
    sequence length.



//-----------------------------------------------------------------------------|
// NAIVE, BRUTE FORCE, TERRIBAD APPROACH
//-----------------------------------------------------------------------------|

First determine whether a compression action is beneficial.
  This may be accomplished by generating a cost-to-compress counter. To do so:
    Iterate over the string in O(N) time
    Tally the total savings or cost of compression
After this determination is made, iterate over the string again in O(N) time to:
  Count how many repeats of a char appear together
  Append the number of counts plus the char to a new string
Return the new (compressed) string.



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

1) Store the string length as an O(1) accessible field
2) Store the string as a char array, allowing O(1) access to any char position
   a) If the string is a Linked List, then any appendation runs in O(N) time
   b) With order N append actions to perform, this becomes O(N^2) time
3) Store the sequence, character, and count to an array or linked list
   a) Records all data needed for compression on first (validation) pass
   b) Prevents us from having to read the original string again
   c) Allows us to write the new string in situ over the old string

"ABBCCCABBCCC" can be stored as:

+-----------------------+
| A | B | C | A | B | C |
+-----------------------+
+-----------------------+
| 1 | 2 | 3 | 1 | 2 | 3 |
+-----------------------+

4) If the length of the string is known a priori:
    Then counting may be shortcutted if the compression savings exceed the
    (remaining characters in the string + 1)
      eg. If we have determined that we can save 5 characters and there are
      only 4 characters left, even if the remaining 4 chars are singles,
      they cannot make the final string length greater than or equal to
      the original string length.
5) Side note: This problem is an implementation of "Run-Length Encoding".
  - https://en.wikipedia.org/wiki/Run-length_encoding
6) If the frequency of a run is 1, the coding system itself may be modified
   without loss of data by omitting the 1 (ie. "A1" becomes just 'A')
7) To optimize the string concatenations, some care and investigation is needed
  - We wish to avoid reallocating the string for every concatenation
  - Doing so may be a language/compiler specific solution
  - C-style char array strings may offer one such method to achieve this
    - Appendations, changes, concatenations are performed in O(1) time



//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

O(N) - Successful completion of the task should be achievable in one or two
passes across the string.



//-----------------------------------------------------------------------------|
// PSEUDO LOGIC
//-----------------------------------------------------------------------------|

Establish two arrays the same size as the string
Iterate over the string and for every character
  If it is a repeat, increment a counter
  If it is not a repeat
    Write the counter to the array tracking count
    Add the new char to the next cell of the array
    Reset the counter to 1
Tally savings - If compression is not worthwhile
  Return the original string
If compression is worthwhile
  Read across the tally arrays, performing appropriate concatentations
  Return concatenated (new) string



//-----------------------------------------------------------------------------|
// CODE (C++)
//-----------------------------------------------------------------------------|
*/
// Compile with:
// $ g++ --std=c++11 01_06_StringCompression.cpp -o StringCompression
// Run with:
// $ ./StringCompression

#include <string>
#include <sstream>
#include <iostream>

int countSavings( int* charCount, int length );
std::string stitchStrings(char* charSequence, int* charCount, int origLength);

// (+) --------------------------------|
// #stringCompression( std::string )
// ------------------------------------|
// Desc:    Compresses a string if doing so would be beneficial, otherwise
//          returns string unaltered
// Params:  string arg1 - The string to compress
// PreCons: None
// PosCons: The string has been compressed (or nothing)
// RetVal:  string - A compressed string (or not)
std::string stringCompression( std::string theString ) {
   // No savings can be realized on a string of length 2 or less
   if( theString.length( ) < 3 ) {
      return ( theString );
   }

   // Pack the string to two arrays
   // Declare storage
   char charSequence[ theString.length( ) ];
   int  charCount[ theString.length( ) ];
   // Initialize storage
   for( int i = 0 ; i < theString.length( ) ; i++ ) {
      charSequence[ i ] = ( char )0;
      charCount[ i ] = -1;
   }
   // Begin traversing the string
   int currArrayPos = 0;

   // Fencepost problem
   char currChar = theString.at( 0 );
   int counter = 1;
   charSequence[ currArrayPos ] = currChar;

   for( int i = 1 ; i < theString.length( ) ; i++ ) {
      if( currChar == theString.at( i ) ) {
         // Repeat behavior
         counter++;
      }
      else if( currChar != theString.at( i ) ) {
         // Non-repeat behavior (new char)
         // Place the count of prior repetitions to the tracking arrays
         charCount[ currArrayPos ] = counter;
         currArrayPos++;
         // Place the new character to the tracking array
         currChar = theString.at( i );
         charSequence[ currArrayPos ] = currChar;
         // And reset the counter
         counter = 1;
      }
   } // Closing for - All chars counted
   // Append the final counter value
   charCount[ currArrayPos] = counter;

   // String traversed, determine savings

   int savings = countSavings( charCount, theString.length( ) );

   // If no savings are realized, return the original string
   if( savings < 1 ) {
      return( theString );
   }

   // Otherwise, concatenate a new string
   else {
      std::string retString = stitchStrings( charSequence, charCount, theString.length( ) );
      // Return the compressed string
      return( retString );
   }

} // Closing stringCompression( std::string )

// (+) --------------------------------|
// #countSavings( std::string )
// ------------------------------------|
// Desc:    Compresses a string if doing so would be beneficial, otherwise
//          returns string unaltered
// Params:  int[] arg1 - An loaded array of char counts
//          int arg2 - The original string length
// PreCons: None
// PosCons: None
// RetVal:  int - The anticipated savings of a compression action
int countSavings( int* charCount, int length ) {
   // For every element in the count array...
   int savings = 0;
   for( int i = 0 ; i < length ; i++ ) {
      // If we run off the end of the valid numerics...
      if( charCount[ i ] == -1 ) {
         break;
      }
      else {
         savings = savings + ( charCount[ i ] - 2 );
         // Calculate further savings reductions for multi-digit sequences
         int powersOfTen = -1;
         int temp = charCount[ i ];
         while ( temp > 0 ) {
            temp = temp / 10;
            powersOfTen++;
         }
         // Single digits == 0 ; Double digits == 1 ; Triple digits == 2
         // For every power of ten, subtract one from the savings
         savings = savings - powersOfTen;
      }
   } // Closing for, all valid numerics added correctly to "savings"
   return( savings );
} // Closing countSavings( int*, int )

// (+) --------------------------------|
// #stitchStrings( char*, int*, int )
// ------------------------------------|
// Desc:    Concatenates all compressed string segments
// Params:  char* arg1 - The sequence of characters as they appeared
//          int* arg2 - The count of the character repetitions
//          int arg3 - The original length of the string
// PreCons: None
// PosCons: None
// RetVal:  std::string - The concatenated string sequence
std::string stitchStrings(char* charSequence, int* charCount, int origLength) {
   std::stringstream tempStream;
   for( int i = 0 ; i < origLength ; i++ ) {
      // In the event of an invalid char count, stop
      if( charCount[ i ] == -1 ) {
         break;
      }
      // Otherwise, concatenate
      tempStream << charSequence[ i ] << charCount[ i ];
   } // Closing for - Valid concatenations complete
   return( tempStream.str( ) );
} // Closing stitchStrings()



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
   std::cout << "Test of stringCompression( )" << std::endl;
   std::string test1 = stringCompression( "AAABBBCCCDDD" );
   std::string test2 = stringCompression( "ABCDEFG" );
   std::string test3 = stringCompression( "AAABBCCD" );
   std::cout << "Test 1 : ( 'A3B3C3D3' expected )" << std::endl;
   std::cout << "            " << test1 << std::endl << std::endl;
   std::cout << "Test 2 : ( 'ABCDEFG' expected )" << std::endl;
   std::cout << "            " << test2 << std::endl << std::endl;
   std::cout << "Test 3 : ( 'AAABBCCD' expected )" << std::endl;
   std::cout << "            " << test3 << std::endl << std::endl;
   return( 0 );
} // Closing main( int, char* )

// End of file 01_06_StringCompression.cpp
