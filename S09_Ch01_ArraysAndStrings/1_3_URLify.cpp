//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.17
// Modified: 2018.07.17
//

/*
1.3 - URLify() - P.90
Write a method to replace all spaces in a string with "%20". You may assume that the string has sufficient space at the end to hold the additional characters, and that you are given the "true" length of the string. (Note: If implementing in Java, please use a character array so that you can perform this operation in place.)

Example:
Input:  "Mr John Smith    ", 13
Output: "Mr%20John%20Smith"

Problem Setup and Assumptions:
  A string may be represented as an array or linked list of chars.
    Many languages also support the string as a class
  The input format provides sufficient whitespace at the end to expand the string appropriately
  The input may or may not have a valid trailing whitespace ('%20')

Naive Approach:
  Generate an empty string and a counter.
  Traverse the provided string from left to right, decrementing the counter for every character.
  At every character, copy from the provided string to the new string.
  If the character to copy is a whitespace, however, copy "%20" instead.
  When the counter reaches (0), all valid characters have been handled.

Optimizations:
  1) The naive solution, while O(N) fast, requires memory overhead equal to the length of the string. A memory optimization in this regard might be realized by shuffling the original string in situ, though it bears mention that if the intended use of this method is for URL strings, the optimization here will be slight.
    - This may be achieved by traversing the original string from right (end) to left (beginning) and using two pointers; one for the current character being read and another for the current character being written.
    - The time complexity shall remain O(N)
  2) If no write operations are possible (that is, the length of the string matches the provided length argument), then the algorithm may be shortcutted
  3) If no further write operations are possible (that is, the write pointer has "caught up" to the read pointer), then the algorithm is complete. Full string processing may be only rarely expected where strings begin with whitespaces.

Pseudo Logic:
  Set the current read pointer to the last letter of the string
  Set the current write pointer to the end of the string
  Fencepost problem:
  - If the pointers are equal, return the string without modification
  Begin loop behavior:
  - Otherwise, read the character from the read pointer into the write pointer's location and advance it one to the left.
  - Unless it's a whitespace, in which case, write "%20" into the next three write positions, advancing the write pointer leftward
  - If the pointers are equal, return the string (no further whitespaces are expected in the string)

Code (C++):
*/

#include <string>

// (+) --------------------------------|
// #URLify(string, int)
// ------------------------------------|
// Desc:    Converts a string to its URL appropriate format (whitespaces replaced with '%20')
// Params:  string arg1 - The string to modify
//          int arg2 - The number of valid characters in the string
// PreCons: The string contains sufficient whitespace at its end to accomodate its alteration
// PosCons: The string has been modified
// RetVal:  void - The string is modified in situ, nothing is returned
void URLify(&string theString, int argLength) {
   // Set the current read pointer to the last letter of the string (subtract 1 for difference between size and index)
   int readPos = argLength - 1;
   // Set the current write pointer to the end of the string (subtract 1 for difference between size and index)
   int writePos = theString.length() - 1;

   // Fencepost problem:
   // - If the pointers are equal, return the string without modification
   if (readPos == writePos) {
      return;
   }

   // Begin loop behavior:
   char currChar;
   while (true) {
      currChar = theString.at(readPos);
      // - Otherwise, read the character from the read pointer into the write pointer's location and advance it one to the left.
      theString[writePos] = theString.at(readPos);
      readPos--;
      // - Unless it's a whitespace, in which case, write "%20" into the next three write positions, advancing the write pointer leftward
      // - If the pointers are equal, return the string (no further whitespaces are expected in the string)
   }
}
