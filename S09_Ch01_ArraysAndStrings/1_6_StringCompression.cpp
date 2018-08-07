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

#include <string>

// (+) --------------------------------|
// #stringCompression(string)
// ------------------------------------|
// Desc:    Compresses a string if doing so would be beneficial, otherwise
//          returns string unaltered
// Params:  string arg1 - The string to compress
// PreCons: None
// PosCons: The string has been compressed (or nothing)
// RetVal:  string - A compressed string (or not)
string stringCompression(string theString) {
   int origLength = theString.length();
   // Ascertain if a savings would be achieved
   int savings = 0;
   int numRepeats = 0;
   char lastChar = theString.at(0);
   char currChar = theString.at(1);
   for ( int i = 1 ; i < origLength ; i++ ) {
      if (currChar == lastChar) {
         numRepeats++;
      }
      else if (currChar != lastChar) {
         // For 0 repeats (single), cost of 1
         // For 1 repeat (double), saving of 0
         // For 2 repeat (triple), saving of 1
         savings = savings + (numRepeats - 1);
         // For 9 repeats (10), saving of 7 a10 (3) aaaaaaaaaa (10)
      }
   }
   
} // Closing stringCompression()
