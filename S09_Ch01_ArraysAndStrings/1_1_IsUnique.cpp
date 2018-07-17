//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.15
// Modified: 2018.07.15
//

/*
1.1 - isUnique() - P.90
Implement an algorithm to determine if a string has all unique characters.
What if you cannot use additional data structures?

Problem Setup and Assumptions:
  A string may be represented as an array or linked list of chars.
    Many languages also support the string as a class
  Chars are ASCII encoded values from 0 to 255 (inclusive)
  "Uniqueness" shall be defined as equality of the char contents, not the memory address of the char
  The string may or may not be null terminated and may or may not have an end
  The string may or may not be drawn from a buffer

Naive Approach:
  Generate a list of characters encountered ('charsEncountered')
  Iterate over the string, character by character. For every character check the input string for a matching char.
  If the string yields a match, return 'false' (this string is not wholly unique).
  If the string does not yield a match, move to the next char in the input string.

  Time complexity shall be, in the worst case, O(N^2), where N is the number of chars in the string.

Optimizations:
  1) If the string size is an O(1) accessible field, it may be checked first. Any string with a size greater than the possible chars must have a repeat.
    - The time complexity of any such comparison, then, may be limited to less than or equal to 256 operation; a constant.
    - While it is not advisable to represent the time complexity of isUnique as O(1) (as this renders comparitive discussion meaningless), it may still be accurate to do so.
  2) Rather than checking against the input string, a compilation of encountered chars may be maintained.
    - Using a linked list will result in 1 check on the second char, 2 checks on the third, 3 checks on the fourth, etc.
      - The worst case time complexity amortizes to 1 + 2 + 3 ... + N checks, or approximately (1/2N * N)
      - This simplifies to O(N^2), although N will never be larger than the number of possible chars at our disposal.
    - Using a hash table, however, can yield an O(1) lookup.
      - A boolean array of size [256] may be used to record what characters have been encountered.
      - Combined with optimization (1), the time complexity shall be O(N) where N is the number of chars in the string and is <= 256

Pseudo Logic:
  Declare hash table seenBefore
  For each character in the string
    Check seenBefore
    If no match
       Toggle cell in seenBefore table
    Else if seenBefore yields a match
       Return false
  No matches were found
    Therefore return true

Code (C++):
*/

#include <string>

// (+) --------------------------------|
// #isUnique(string)
// ------------------------------------|
// Desc:    Determines whether a string contains a repeat or not
// Params:  string arg1 - The string received
// PreCons: None
// PosCons: None
// RetVal:  bool true - All chars in the string are unique
//          bool false - There is at least one repeated char in the string
bool isUnique(string theString) {
   // Initial length check
   if ( theString.length( ) >= 256 ) {
      return( false );
   }
   // Declare and initialize the check array
   bool hasBeenSeen[256];
   for (int i = 0 ; i < 256 ; i++) {
      hasBeenSeen[i] = false;
   }

   // Now iterate over all the letters
   char currChar;
   int checkIndex;
   for (int i = 0 ; i < theString.length( ) ; i++) {
      currChar = theString.at(i);
      // "Hash" the current char
      checkIndex = (int)currChar;
      if (hasBeenSeen[checkIndex] == true) {
         return(false);
      }
      else { // This is a new character
         hasBeenSeen[checkIndex] = true;
      }
   }
   // All characters have been checked without encountering a repeat
   return(true);
}